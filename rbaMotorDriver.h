/*
This class controls motor's speed using pulse signals.
*/
#
#ifndef _RBAMOTORDRIVER_H_
#define _RBAMOTORDRIVER_H_
#include <Arduino.h>
class rbaMotorDriver
{
public:
	rbaMotorDriver(uint8_t motor1_EN, uint8_t motor1_B, uint8_t motor1_A, uint8_t motor2_EN, uint8_t motor2_B, uint8_t motor2_A);
	~rbaMotorDriver();

	void begin();
	void run(int motor1Speed_PWM, int motor2Speed_PWM);
	void setMotor1_Speed(int motorSpeed_PWM);
	void setMotor2_Speed(int motorSpeed_PWM);
	void brake();

private:
	uint8_t motor1_EN_Pin;
	uint8_t motor1_A_Pin;
	uint8_t motor1_B_Pin;

	uint8_t motor2_EN_Pin;
	uint8_t motor2_A_Pin;
	uint8_t motor2_B_Pin;

};

#endif