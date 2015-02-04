/*
This class controls motor's speed using pulse signals.
*/
#include "rbaMotorDriver.h"


rbaMotorDriver::rbaMotorDriver(uint8_t motor1_EN, uint8_t motor1_B, uint8_t motor1_A, uint8_t motor2_EN, uint8_t motor2_B, uint8_t motor2_A)
{

	motor1_EN_Pin = motor1_EN;
	motor1_A_Pin = motor1_A;
	motor1_B_Pin = motor1_B;

	motor2_EN_Pin = motor2_EN;
	motor2_A_Pin = motor2_A;
	motor2_B_Pin = motor2_B;
}


rbaMotorDriver::~rbaMotorDriver()
{
}


void rbaMotorDriver::begin()
{
	//Set pins as outputs
	pinMode(motor1_EN_Pin, OUTPUT);
	pinMode(motor1_A_Pin, OUTPUT);
	pinMode(motor1_B_Pin, OUTPUT);

	pinMode(motor2_EN_Pin, OUTPUT);
	pinMode(motor2_A_Pin, OUTPUT);
	pinMode(motor2_B_Pin, OUTPUT);
	
	//Turn off motors.
	digitalWrite(motor1_EN_Pin, LOW); //Disable motor.
	digitalWrite(motor1_A_Pin, LOW); 
	digitalWrite(motor1_B_Pin, LOW); 
	digitalWrite(motor2_EN_Pin, LOW); //Disable motor.
	digitalWrite(motor2_A_Pin, LOW); 
	digitalWrite(motor2_B_Pin, LOW); 
}

void rbaMotorDriver::run(int motor1_Speed_PWM, int motor2_Speed_PWM) //Set motor speed in range -255 to 255.
{
	setMotor1_Speed(motor1_Speed_PWM);
	setMotor2_Speed(motor2_Speed_PWM);
}

// Speed_PWM should be between -255 and 255.
void rbaMotorDriver::setMotor1_Speed(int Speed_PWM)
{
	int motor1Speed = 0;
	if (Speed_PWM > 0 && Speed_PWM <= 255){ //Verify positive speed to set forward direction. 
		digitalWrite(motor1_A_Pin, HIGH); //Start motor running forward.
		digitalWrite(motor1_B_Pin, LOW); //Stop motor running back.
		motor1Speed = Speed_PWM;
	}
	else if (Speed_PWM < 0 && Speed_PWM >= -255){ //Verify negative speed to set back direction. 
		digitalWrite(motor1_A_Pin, LOW); //Stop motor running forward.
		digitalWrite(motor1_B_Pin, HIGH); //Start motor running back.
		motor1Speed = -Speed_PWM;
	}
	else{
		digitalWrite(motor1_A_Pin, LOW); //Turn off movement.
		digitalWrite(motor1_B_Pin, LOW); //Turn off movement.
	}
	analogWrite(motor1_EN_Pin, motor1Speed);
}


// Speed_PWM should be between -255 and 255.
void rbaMotorDriver::setMotor2_Speed(int Speed_PWM)
{
	int motor2Speed = 0;
	if (Speed_PWM > 0 && Speed_PWM <= 255){ //Verify positive speed to set forward direction. 
		digitalWrite(motor2_A_Pin, HIGH); //Start motor running forward.
		digitalWrite(motor2_B_Pin, LOW); //Stop motor running back.
		motor2Speed = Speed_PWM;
	}
	else if (Speed_PWM < 0 && Speed_PWM >= -255){ //Verify negative speed to set back direction. 
		digitalWrite(motor2_A_Pin, LOW); //Stop motor running forward.
		digitalWrite(motor2_B_Pin, HIGH); //Start motor running back.
		motor2Speed = -Speed_PWM;
	}
	else{
		digitalWrite(motor2_A_Pin, LOW); //Turn off movement.
		digitalWrite(motor2_B_Pin, LOW); //Turn off movement.
	}
	analogWrite(motor2_EN_Pin, motor2Speed); 
}

void rbaMotorDriver::brake()
{
	digitalWrite(motor1_EN_Pin, HIGH);//Enable motor.
	digitalWrite(motor1_A_Pin, LOW);//Stop motor running forward.
	digitalWrite(motor1_B_Pin, LOW);//Stop motor running back.

	digitalWrite(motor2_EN_Pin, HIGH);//Enable motor.
	digitalWrite(motor2_A_Pin, LOW); //Stop motor running forward.
	digitalWrite(motor2_B_Pin, LOW); //Stop motor running back.
}
