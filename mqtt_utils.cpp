
#include "mqtt_utils.h"


Timer xPostStateADC, xPostStateGPIO;
static WiFiClient xWifiClient;
static PubSubClient xPsClient(xWifiClient);

void vSetServer() {
	xPsClient.setServer(xGlobalSettings.acMQTTserver, xGlobalSettings.uiMQTTport);
}


void vMqttLoop() {	
		
	while (!xPsClient.connected()) {
			
		vSetServer();
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

		xPostStateADC.every(ADC_CHECK_PERIOD_MS, vPostADC, (void *)&xPsClient);
		xPostStateGPIO.every(GPIO_CHECK_PERIOD_MS, vPostGPIO, (void *)&xPsClient);
	}

	xPostStateADC.update();
	xPostStateGPIO.update();
	xPsClient.loop();
}