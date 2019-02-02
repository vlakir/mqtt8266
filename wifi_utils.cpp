// 
// 
// 

#include "wifi_utils.h"

void vConnectWifi(char* acSsid, char* acPassword) {
	delay(10);
	// We start by connecting to a WiFi network
	Serial.println();
	Serial.print("Connecting to ");
	Serial.println(acSsid);

	WiFi.begin(acSsid, acPassword);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	randomSeed(micros());

	Serial.println("");
	Serial.println("WiFi connected");
	Serial.println("IP address: ");
	Serial.println(WiFi.localIP());

}


