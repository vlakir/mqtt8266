/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"

PubSubClient xPsClient = xGetPsClient(MQTT_SERVER, MQTT_PORT, vRecieveCallback);
Timer xPostStateADC;


void vPostADC() {
	static unsigned int uiOld;
	
	DO_ONCE(
		uiOld = 1025; // unreal value for 10-bit ADC
	);

	unsigned int uiADC = analogRead(A0);

	if (uiADC != uiOld) {
		uiOld = uiADC;
		char acMessage[33];
		char acTopic[80];
		sprintf(acMessage, "%d", uiADC);
		sprintf(acTopic, "%s%s%s", DEVICE_UNIQ_ID, "/state", "/ADC");
		xPsClient.publish(acTopic, acMessage);
	}
}


void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength) {
	Serial.print("Message arrived [");
	Serial.print(acTopic);
	Serial.print("] ");
	for (int i = 0; i < uiLength; i++) {
		Serial.print((char)abPayload[i]);
	}
	Serial.println();

	// Switch on the LED if an 1 was received as first character
	if ((char)abPayload[0] == '1') {
		digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
		// but actually the LED is on; this is because
		// it is active low on the ESP-01)
	}
	else {
		digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
	}
}


void setup() {
	pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
	Serial.begin(SERIAL_PORT_SPEED);
	vConnectWifi(WIFI_SSID, WIFI_PASSWORD);
	xPostStateADC.every(CHECK_PERIPHERAL_PERIOD_MS, vPostADC);
}


void loop() {
	vMqttLoop(xPsClient);
	xPostStateADC.update();
}
