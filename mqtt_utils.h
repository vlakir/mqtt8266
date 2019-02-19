#pragma once


#include "settings.h"
#include <PubSubClient.h>
#include "wifi_utils.h"


PubSubClient xGetPsClient(std::function<void(char*, uint8_t*, unsigned int)> callback);
void vConnectMqtt(PubSubClient psClient);
void vMqttLoop(PubSubClient &xPsClient);
