#pragma once

#include <PubSubClient.h>
#include "constants.h"
#include "wifi_utils.h"

PubSubClient getPsClient(char* server, unsigned int port, std::function<void(char*, uint8_t*, unsigned int)> callback);
void connectMqtt(PubSubClient psClient, char* clientId, char* clientPassword);
void mqttLoop(PubSubClient &psClient);

