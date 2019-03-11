/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8266.h"

SettingsStruct xGlobalSettings;

void setup() {	
	vInitSerial();
	vGetGlobalSettings();
	initPeripheral();
	vConnectWifi();
}

void loop() {	
	vMqttLoop();
	vSerialLoop();	
}
