/*
This class make use of motordriver, bluetooth and ultrasonicsensor classes to control a robot car over bluetooth.
*/

#ifndef _ARDUINOCAR_H_
#define _ARDUINOCAR_H_
#include "rbaBluetooth.h"
#include "rbaLineFinder.h"
#include "rbaUltrasonicSensor.h"
#include "rbaMotorDriver.h"


class arduinoCar
{
public:
	arduinoCar();
	~arduinoCar();
	void begin();

	void readKey();
	void processKey();
	void joystickMode(int speed, char direction); //This method controls the car using bluetooth.
	void linetrackingMode(int speed); //This method tracks black lines.
	void ultrasonicMode(int speed); //This method detects objects and avoid collisions.

private:
	char carMode;
	char carDirection;
	char carSpeed;
	int speedPWM;
	
};

#endif