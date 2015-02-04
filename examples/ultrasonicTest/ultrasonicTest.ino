

#include <SoftwareSerial.h>
#include <rbaUltrasonicSensor.h>

//Connect the Ultrasonic Sensor Trigger to A2(D16, Echo to A3(D17)
rbaUltrasonicSensor myUltrasonicSensor(16, 17);

void setup()
{
	myUltrasonicSensor.begin();
	Serial.begin(9600);
}

void loop()
{
	int distance = myUltrasonicSensor.distance();
	Serial.print("Distance cm:");
	Serial.println(distance);
	delay(1000);
}
