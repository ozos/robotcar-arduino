#include <rbaBluetooth.h>
#include <SoftwareSerial.h>

//rbaBluetooth(RX,TX,INT);
rbaBluetooth myBt(11, 10, 9);
void setup()
{
	Serial.begin(9600);
	myBt.begin();
	if (myBt.atCommand("NAME", "OzosMeow")){ //Set bluetooth's name using an AT command
		Serial.println("AT command was sucessful");
	}
	else{
		Serial.println("AT command has Failed");
	}
	Serial.println("Waiting to be connected");
}


void loop()
{
	char data;
	if (myBt.connected()){ //Read from bluetooth and print in serial port.
		if (myBt.available()){
			data = myBt.read();
			Serial.print(data);
		}
		if (Serial.available()){ //Read from serial port and send to bluetooth.
			data = Serial.read();
			myBt.print(data);
		}
	}
	
}
