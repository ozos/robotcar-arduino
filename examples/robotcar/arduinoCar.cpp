/*
This class make use of motordriver, bluetooth and ultrasonicsensor classes to control a robot car over bluetooth.
*/
#include "arduinoCar.h"

//Macros for direction
#define FORWARD			'U'
#define BACKWARD		'D'
#define LEFT			'L'
#define RIGHT			'R'
#define LEFT_FORWARD	'X'
#define RIGHT_FORWARD	'Y'
#define LEFT_BACK		'W'
#define RIGHT_BACK		'Z'

//Macros for mode
#define	_MODE_HEAD		"ABC"
#define _JOYSTICK_HEAD	"ULDRWXYZ"

#define JOYSTICK_MODE	'A'
#define LINEFINDER_MODE	'B'
#define ULTRASONIC_MODE	'C'

//Speed difference to turn left or right while moving forward or back.
#define SPEED_DIF 50

const int speed_pwm[] = { 0, 120, 154, 187, 221, 255 };

//MotorDriver Pins (M1_EN,M1_IN2,M1_IN1, M2_EN,M2_IN2,M2_IN1)
rbaMotorDriver motorDriver(5, 12, 13, 6, 7, 8);

//Bluetooth Pins (TX, RX, INT)
rbaBluetooth bluetooth(11, 10, 9);

//Ultrasonic Pins(Trig,Echo)
rbaUltrasonicSensor ultrasonicSensor(16, 17);

//LineFinder Pins(Sensor1, Sensor2)
rbaLineFinder lineFinder(14, 15);

//Define string variables for mode and joystic head
extern String modeHead(_MODE_HEAD);
extern String joystickHead(_JOYSTICK_HEAD);

arduinoCar::arduinoCar() :carSpeed('0')
{
}

arduinoCar::~arduinoCar()
{
}

void arduinoCar::begin()
{
	//Initialize mode,direction and speed of car.
	carMode = JOYSTICK_MODE;
	carDirection = FORWARD;
	carSpeed = '0';

	//Initialize motorDirver
	motorDriver.begin();

	//Initialize bluetooth
	bluetooth.begin();

	//Initialize ultrasonicSensor
	ultrasonicSensor.begin();

	//Initiallize lineFinder
	lineFinder.begin();

	//Get the random seed for ultrasonic mode
	randomSeed(analogRead(0));
}

void arduinoCar::readKey(){
	char dat;

	if (bluetooth.available()){
		dat = bluetooth.read();

		Serial.print(dat);
		if (modeHead.indexOf(dat) != -1){//Receive mode command.
			carMode = dat;
			dat = bluetooth.read();
			if (dat >= '0' && dat <= '5'){
				carSpeed = dat;
			}
		}
		else if (joystickHead.indexOf(dat) != -1){//Receive joystic command.
			carDirection = dat;
			dat = bluetooth.read();
			if (dat >= '0' && dat <= '5'){
				carSpeed = dat;
			}
		}
	}
}

void arduinoCar::processKey()
{
	speedPWM = speed_pwm[carSpeed - '0'];

	switch (carMode){
	case JOYSTICK_MODE:joystickMode(speedPWM, carDirection ); break;
	case LINEFINDER_MODE:linetrackingMode(speedPWM); break;
	case ULTRASONIC_MODE:ultrasonicMode(speedPWM); break;
	default:break;
	}
}

void arduinoCar::joystickMode(int speed,char direction)
{
	int differentialSpeed = 0;

	if (speed >= SPEED_DIF){
		differentialSpeed = speed - SPEED_DIF;
	}

	switch (direction){
	case FORWARD:motorDriver.run(speed, speed); break; //Forward
	case BACKWARD:motorDriver.run(-speed, -speed); break; //Backward
	case LEFT:motorDriver.run(-speed, speed); break; //Left
	case RIGHT:motorDriver.run(speed, -speed); break; //Right
	case LEFT_FORWARD:motorDriver.run(differentialSpeed, speed); break; //Leftforward
	case RIGHT_FORWARD:motorDriver.run(speed, differentialSpeed); break; //Rightforward
	case LEFT_BACK:motorDriver.run(-differentialSpeed, -speed); break; //Leftback
	case RIGHT_BACK:motorDriver.run(-speed, -differentialSpeed); break; //Rightback
	default:break;

	}
}

void arduinoCar::linetrackingMode(int speed)
{
	//Get the speed for two motors.
	int differentialSpeed = 0;

	if (speed >= SPEED_DIF){
		differentialSpeed = speed - SPEED_DIF;
	}

	//Try to make the car run along with the black line.
	static char lastDirection = FORWARD;
	int sensor1 = lineFinder.lsensor1();
	int sensor2 = lineFinder.lsensor2();

	if (0 == sensor1 && 0 == sensor2){ //Move forward.
		motorDriver.run(speed, speed);
		lastDirection = FORWARD;
	}
	else if (1 == sensor1 && 0 == sensor2){ //Turn left.
		motorDriver.run(-speed, speed);
		lastDirection = LEFT;
	}
	else if (0 == sensor1 && 1 == sensor2){ //Turn right.
		motorDriver.run(speed, -speed);
		lastDirection = RIGHT;
	}
	else if (1 == sensor1 && 1 == sensor2){ //Get back to the line.
		if (LEFT == lastDirection){ //Turn left forward.
			motorDriver.run(50, 100);
		}
		else if (RIGHT == lastDirection){ //Turn right forward.
			motorDriver.run(100, 50);
		}
	}

}

void arduinoCar::ultrasonicMode(int speed)
{
	static int randomFlag = 1;
	static int randomDirection = 0;
	if (1 == randomFlag){
		randomDirection = random(0, 2);
	}
	int distance = ultrasonicSensor.distance();

	if (distance > 40){
		motorDriver.run(speed, speed);
		randomFlag = 1;
	}
	else{
		if (randomDirection == 0){ //Turn left.
			motorDriver.run(-speed, speed);
			randomFlag = 0;
		}
		else{ //Turn right.
			motorDriver.run(speed, -speed);
			randomFlag = 0;
		}
	}

}

