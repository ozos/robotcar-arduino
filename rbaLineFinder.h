/*
This class allows to track a line using two line sensors. 
*/
#ifndef _RBALINEFINDER_H
#define _RBALINEFINDER_H
#include <Arduino.h>

class rbaLineFinder
{
public:
	rbaLineFinder(uint8_t lineSensor1, uint8_t lineSensor2);
	~rbaLineFinder();
	void begin();
	int lsensor1();
	int lsensor2();
private:
	uint8_t sensor1Pin;
	uint8_t sensor2Pin;
};

#endif