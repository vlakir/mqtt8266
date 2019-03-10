// 
// 
// 

#include "wifi_utils.h"

void vConnectWifi() {
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


	/*
	while (WiFi.status() != WL_CONNECTED) {	
		delay(500);		
		Serial.print(".");
	}
	*/



}


