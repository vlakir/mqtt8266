
#include "mqtt_utils.h"

PubSubClient xGetPsClient(std::function<void(char*, uint8_t*, unsigned int)> vRecieveCallback) {
	WiFiClient xWifiClient;
	PubSubClient xPsClient(xWifiClient);
	xPsClient.setServer(xGlobalSettings.acMQTTserver, xGlobalSettings.uiMQTTport);
	xPsClient.setCallback(vRecieveCallback);	
	return xPsClient;
}


void vConnectMqtt(PubSubClient xPsClient) {
	// Loop until we're reconnected
	while (!xPsClient.connected()) {
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
	}
}

void vMqttLoop(PubSubClient &xPsClient) {
	

	if (!xPsClient.connected()) {
		vConnectMqtt(xPsClient);
		char acTopic[80];
		sprintf(acTopic, "%s%s", xGlobalSettings.acDeviceID, "/management/#");
		xPsClient.subscribe(acTopic);	
	}
	xPsClient.loop();
}