#pragma once


#include "settings.h"
#include <PubSubClient.h>
#include "wifi_utils.h"


PubSubClient xGetPsClient(char* server, unsigned int port, std::function<void(char*, uint8_t*, unsigned int)> callback);
void vConnectMqtt(PubSubClient psClient, char* clientId, char* clientPassword);
void vMqttLoop(PubSubClient &xPsClient, char* acClientID, char* acClientPassword, char* device_id);
