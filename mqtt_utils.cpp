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


#include "mqtt_utils.h"


Timer xPostStateADCtimer, xPostStateGPIOtimer;
static WiFiClient xWifiClient;
static PubSubClient xPsClient(xWifiClient);


void vServerReconnect(void) {
	static VirtualDelay singleDelay;
	xPsClient.disconnect();
	xPsClient.setServer(xGlobalSettings.acMQTTserver, xGlobalSettings.uiMQTTport);	
	xPsClient.setCallback(vRecieveCallback);
	Serial.print("Attempting MQTT connection...");
	// Attempt to connect
	if (xPsClient.connect("arduinoClient", xGlobalSettings.acMQTTclientID, xGlobalSettings.acMQTTclientPassword)) {
		Serial.println("connected");
	}
	else {
		Serial.print("failed, rc=");
		Serial.print(xPsClient.state());
		Serial.println(" try again in 5 seconds");
		// Wait 5 seconds before retrying
		delay(5000);
	}
	char acTopic[80];
	sprintf(acTopic, "%s%s", xGlobalSettings.acDeviceID, "/management/#");
	xPsClient.subscribe(acTopic);
}


void vMqttLoop(void) {
	if (!xPsClient.connected()) {
		vServerReconnect();
		xPostStateADCtimer.every(ADC_CHECK_PERIOD_MS, vPostADC, (void *)&xPsClient);
		xPostStateGPIOtimer.every(GPIO_CHECK_PERIOD_MS, vPostGPIO, (void *)&xPsClient);
	}
	xPostStateADCtimer.update();
	xPostStateGPIOtimer.update();
	xPsClient.loop();
}