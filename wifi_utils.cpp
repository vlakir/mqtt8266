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


#include "wifi_utils.h"

void vConnectWifi(void) {
	delay(10);
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(xGlobalSettings.acWiFiSSID);
	WiFi.begin(xGlobalSettings.acWiFiSSID, xGlobalSettings.acWiFiPassword);
	for (int i = 0; i < 20; i++) { //while this cicle we can't get any command from serial port
		if (WiFi.status() == WL_CONNECTED) {
			randomSeed(micros());
			Serial.println("");
			Serial.println("WiFi connected");
			Serial.println("IP address: ");
			Serial.println(WiFi.localIP());			
			break;
		}			
		delay(500);
		Serial.print(".");
	}
}


