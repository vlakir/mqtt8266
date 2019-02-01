// 
// 
// 

#include "mqtt_utils.h"

PubSubClient getPsClient(char* server, unsigned int port, std::function<void(char*, uint8_t*, unsigned int)> callback) {
	WiFiClient wifiClient;
	PubSubClient psClient(wifiClient);
	psClient.setServer(server, port);
	psClient.setCallback(callback);	
	return psClient;
}


void connectMqtt(PubSubClient psClient, char* clientId, char* clientPassword) {
	// Loop until we're reconnected
	while (!psClient.connected()) {
		Serial.print("Attempting MQTT connection...");

		// Attempt to connect
		if (psClient.connect("arduinoClient", clientId, clientPassword)) {
			Serial.println("connected");
		}
		else {
			Serial.print("failed, rc=");
			Serial.print(psClient.state());
			Serial.println(" try again in 5 seconds");
			// Wait 5 seconds before retrying
			delay(5000);
		}
	}
}

void mqttLoop(PubSubClient &psClient) {
	if (!psClient.connected()) {
		connectMqtt(psClient, MQTT_CLIENT_ID, MQTT_CLIENT_PASSWORD);
		psClient.subscribe("inTopic");
	}
	psClient.loop();
}