/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"



PubSubClient psClient = getPsClient(MQTT_SERVER, MQTT_PORT, callback);
Timer xPostMessage;




void callback(char* topic, byte* payload, unsigned int length) {
	Serial.print("Message arrived [");
	Serial.print(topic);
	Serial.print("] ");
	for (int i = 0; i < length; i++) {
		Serial.print((char)payload[i]);
	}
	Serial.println();

	// Switch on the LED if an 1 was received as first character
	if ((char)payload[0] == '1') {
		digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
		// but actually the LED is on; this is because
		// it is active low on the ESP-01)
	} else {
		digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
	}
}

void vPostADC() {
	unsigned int aDC = analogRead(A0);
	char message[33];
	char topic[80];
	sprintf(message, "%d", aDC);	
	sprintf(topic, "%s%s%s", DEVICE_UNIQ_ID, "/state", "/ADC");
	psClient.publish(topic, message);
}


void setup() {
	pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
	Serial.begin(SERIAL_PORT_SPEED);
	connectWifi(WIFI_SSID, WIFI_PASSWORD);

	xPostMessage.every(POST_MESSAGE_PERIOD_MS, vPostADC);
}

void loop() {

	mqttLoop(psClient);

	xPostMessage.update();
}
