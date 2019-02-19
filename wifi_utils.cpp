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


