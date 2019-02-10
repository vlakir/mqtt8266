/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"

PubSubClient xPsClient = xGetPsClient(MQTT_SERVER, MQTT_PORT, vRecieveCallback);
Timer xPostStateADC, xPostStateGPIO;

void setup() {
	pinMode(BUILTIN_LED, OUTPUT); 
	initPeripheral();
	Serial.begin(SERIAL_PORT_SPEED);
	vConnectWifi(WIFI_SSID, WIFI_PASSWORD);
	xPostStateADC.every(ADC_CHECK_PERIOD_MS, vPostADC, (void *) &xPsClient);
	xPostStateGPIO.every(GPIO_CHECK_PERIOD_MS, vPostGPIO, (void *)&xPsClient);
	
}


void loop() {
	vMqttLoop(xPsClient);
	xPostStateADC.update();
	xPostStateGPIO.update();
}
