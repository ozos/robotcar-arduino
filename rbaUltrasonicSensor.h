/*
This class detects objects and returns the dinstance in cm.
*/
#ifndef _RBAULTRASONICSENSOR_H
#define _RBAULTRASONICSENSOR_H
#include <Arduino.h>
class rbaUltrasonicSensor
{
public:
	rbaUltrasonicSensor(uint8_t trigger, uint8_t echo);
	~rbaUltrasonicSensor();
	void begin();

	long distance();
private:
	uint8_t triggerPin;
	uint8_t echoPin;
};

#endif