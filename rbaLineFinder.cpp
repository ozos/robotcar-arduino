/*
This class allows to track a line using two line sensors.
*/
#include "rbaLineFinder.h"
#include <Arduino.h>

rbaLineFinder::rbaLineFinder(uint8_t lineSensor1, uint8_t lineSensor2)
{
	sensor1Pin = lineSensor1;
	sensor2Pin = lineSensor2;
}
void rbaLineFinder::begin(){
	pinMode(sensor1Pin, INPUT);
	pinMode(sensor2Pin, INPUT);
}

int rbaLineFinder::lsensor1(){   // Read sensor 1.
	return digitalRead(sensor1Pin);
}
int rbaLineFinder::lsensor2(){ // Read sensor 2.
	return digitalRead(sensor2Pin);
}

rbaLineFinder::~rbaLineFinder()
{
}
