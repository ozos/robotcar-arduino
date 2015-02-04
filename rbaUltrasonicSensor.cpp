/*
This class uses an ultrasonic sensor to detect the distance of the closest object in front of it.
*/
#include "rbaUltrasonicSensor.h"


rbaUltrasonicSensor::rbaUltrasonicSensor(uint8_t trigger, uint8_t echo)
{
	triggerPin = trigger;
	echoPin = echo;
}

void rbaUltrasonicSensor::begin(){
	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);

}

long rbaUltrasonicSensor::distance(){ // Return distance to an object in cm.
	long distance = 0;
	long duration = 0;
	// Give a short LOW pulse beforehand to ensure a clean HIGH pulse.
	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	// The sensor is triggered by a HIGH pulse of 10 or more microseconds.
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);

	digitalWrite(triggerPin, LOW);

	// Read the signal from the sensor: a HIGH pulse whose
	// duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object.
	// Read the signal from the sensor: a HIGH pulse whose.

	duration = pulseIn(echoPin, HIGH);

	// Convert the time into a distance
	// inches  distance = duration/ 74 / 2;
	distance = duration /29/2; // cm.
	return distance;
}
rbaUltrasonicSensor::~rbaUltrasonicSensor()
{
}
