#include <SoftwareSerial.h>
#include <rbaLineFinder.h>


//Connect Line Finder Sensor1 D14(A0), Sensor2 to D15(A1)
rbaLineFinder myLineFinder(14, 15);

void setup()
{
	myLineFinder.begin();
	Serial.begin(9600);
}

void loop()
{
	Serial.print("Sensor1:");
	Serial.println(myLineFinder.lsensor1());
	Serial.print("Sensor2:");
	Serial.println(myLineFinder.lsensor2());
	Serial.println();

	delay(1000);
}