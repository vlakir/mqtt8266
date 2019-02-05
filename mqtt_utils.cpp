
#include "mqtt_utils.h"

PubSubClient xGetPsClient(char* acServer, unsigned int uiPort, std::function<void(char*, uint8_t*, unsigned int)> vRecieveCallback) {
	WiFiClient xWifiClient;
	PubSubClient xPsClient(xWifiClient);
	xPsClient.setServer(acServer, uiPort);
	xPsClient.setCallback(vRecieveCallback);	
	return xPsClient;
}


void vConnectMqtt(PubSubClient xPsClient, char* acClientId, char* acClientPassword) {
	// Loop until we're reconnected
	while (!xPsClient.connected()) {
		Serial.print("Attempting MQTT connection...");

		// Attempt to connect
		if (xPsClient.connect("arduinoClient", acClientId, acClientPassword)) {
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
		vConnectMqtt(xPsClient, MQTT_CLIENT_ID, MQTT_CLIENT_PASSWORD);
		xPsClient.subscribe("inTopic");
	}
	xPsClient.loop();
}