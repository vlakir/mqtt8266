/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"

PubSubClient xPsClient = xGetPsClient(DEFAULT_MQTT_SERVER, DEFAULT_MQTT_PORT, vRecieveCallback);
Timer xPostStateADC, xPostStateGPIO;

void setup() {
	pinMode(BUILTIN_LED, OUTPUT); 
	initPeripheral();
	Serial.begin(SERIAL_PORT_SPEED);
	vConnectWifi(DEFAULT_WIFI_SSID, DEFAULT_WIFI_PASSWORD);
	xPostStateADC.every(ADC_CHECK_PERIOD_MS, vPostADC, (void *) &xPsClient);
	xPostStateGPIO.every(GPIO_CHECK_PERIOD_MS, vPostGPIO, (void *)&xPsClient);
	
}


void loop() {
	vMqttLoop(xPsClient, DEFAULT_MQTT_CLIENT_ID, DEFAULT_MQTT_CLIENT_PASSWORD);
	xPostStateADC.update();
	xPostStateGPIO.update();

	String inString;
	while (Serial.available()) {
		char inChar = Serial.read(); 
		if (inChar != 13) {
			inString += inChar;      
		} else {
			Serial.flush();
			//2do: get settings string
		}
	}



}
