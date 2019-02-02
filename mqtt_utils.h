#pragma once

#include <PubSubClient.h>
#include "constants.h"
#include "wifi_utils.h"

PubSubClient xGetPsClient(char* server, unsigned int port, std::function<void(char*, uint8_t*, unsigned int)> callback);
void vConnectMqtt(PubSubClient psClient, char* clientId, char* clientPassword);
void vMqttLoop(PubSubClient &psClient);

