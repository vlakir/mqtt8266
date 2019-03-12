/*
Vladimir Kirievskiy (C) 2019
********************************************************************************************
* @brief MQTT client software for esp8266 platform (tested on Wemos D1 mini)
* @license MIT
* SDK:	Arduino IDE 1.8.5 with plugin for esp8266
*
********************************************************************************************
* @author V. Kirievskiy aka vlakir
* vladimir@kirievskiy.ru
* https://github.com/vlakir
* This software is furnished "as is", without technical support, and with no
* warranty, express or implied, as to its usefulness for any purpose.
*/


#include "mqtt8266.h"

// logins and passwords for wifi and mqtt-broker, etc.
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
