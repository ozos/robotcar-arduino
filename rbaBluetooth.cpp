/*
This class uses SoftwareSerial to communicate arduino board with other devices over bluetooth.
*/
#include "rbaBluetooth.h"

//rba_rxPin and rba_txPin are bt pins.
rbaBluetooth::rbaBluetooth(uint8_t rba_rxPin, uint8_t rba_txPin) :btSerial(rba_txPin, rba_rxPin), noState(1) // bt rx pin ---> arduino tx pin.
{                                                                                                  // bt tx pin <--- arduino rx pin.
	rba_txPin = rba_txPin;
	rba_txPin = rba_txPin;
}
//rba_rxPin and rba_txPin are conected to rx and tx pins of bluetooth, respectively.
rbaBluetooth::rbaBluetooth(uint8_t rba_rxPin, uint8_t rba_txPin, uint8_t rba_state) :btSerial(rba_txPin, rba_rxPin), noState(0) // bt tx pin ---> arduino rx pin.
{                                                                                                                     // bt rx pin <--- arduino tx pin.
	rba_txPin = rba_txPin;
	rba_txPin = rba_txPin;
	rba_btStatePin = rba_state;
}

//Pins initialization. Pins are cofigured as inputs or ouputs.
void rbaBluetooth::begin()
{
	pinMode(rba_txPin, INPUT); // Arduino reads from bluetooth tx pin. 
	pinMode(rba_rxPin, OUTPUT); // Arduino writes to bluetooth rx pin.

	if (noState == 0){ //If there is state pin.
		pinMode(rba_btStatePin, INPUT); // Arduino reads from bluetooth state(int) pin.
		bt_state = 0; //No connected state.
	}
	else{
		bt_state = 1; // To bypass connection checking when there is not state pin in bluetooth.
	}
	btSerial.begin(9600);

}

int rbaBluetooth::atCommand(String at_command, String bt_data = ""){ // Modify settings of bluetooth using AT Commands(baud rate, name, version, etc).
	int isSuccess = 0;
	String recvBuf;
	char recvChar;


	String cmd("AT+"); //Concatenate strings to build AT Command;
	cmd += at_command;
	cmd += bt_data;
	cmd += '\r';
	cmd += '\n';
	
	int cmdLen = cmd.length();
	
	for (int i = 0; i < cmdLen; i++){ //Write data to the buffer.
		btSerial.write(cmd[i]);
	}
	delay(200);
	int len = 0; // Store the size of data in the buffer.

	if (len = available()){ // If there is data in the buffer. The data is read.
		for (int i = 0; i < len; i++){
			recvChar = read();
			Serial.print(recvChar);
			recvBuf += recvChar;
		}
		if (recvBuf.indexOf(at_command) != -1){ //Check if the data read is the expected one. Verify transmission of AT commands.
			if (bt_data != ""){ //Some AT commands require an extra parameter.
				if (recvBuf.indexOf(bt_data) != -1){
					isSuccess = 1;
				}
			}
			else{
				isSuccess = 1;
			}

		}
	}
	return isSuccess;
}

int rbaBluetooth::print(uint8_t byte) //Write to the bluetooth buffer (tx).
{
	return (btSerial.write(byte));
}

int rbaBluetooth::read() //Read from the bluetooth buffer (rx).
{
	return (btSerial.read());
}

int rbaBluetooth::available() //Get the number of bytes available for reading from buffer.
{
	return (btSerial.available());
}

int rbaBluetooth::connected() //Verify if bluetooth is connected to arduino using the state pin. Read the state from state pin.
{
	if (noState == 0){ //Check if there is state pin.
		int readState = digitalRead(rba_btStatePin);
		if (readState != bt_state){
			bt_state = readState;
			delay(1);
			btSerial.flush();
		}
	}
	return bt_state;
}

rbaBluetooth::~rbaBluetooth()
{

}
