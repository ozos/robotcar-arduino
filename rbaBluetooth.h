/*
This class uses SoftwareSerial to communicate arduino board with other devices over bluetooth.
*/

#ifndef _RBABLUETOOTH_H
#define _RBABLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <WString.h>

class rbaBluetooth
{
public:
	rbaBluetooth(uint8_t rba_rx, uint8_t rba_tx); // Set reception pin and transmission pin.
	rbaBluetooth(uint8_t rba_rx, uint8_t rba_tx, uint8_t rba_state); // Set an extra pin to check bluetooth state.
	~rbaBluetooth();

	void begin();
	
	int atCommand(String at_command,String bt_data);
	int print(uint8_t byte);
	int read();
	int available();
	int connected();


private:
	uint8_t rba_rxPin;
	uint8_t rba_txPin;
	uint8_t rba_btStatePin;
	int bt_state;
	int noState;
	SoftwareSerial btSerial;
};

#endif