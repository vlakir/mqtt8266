#pragma once

#include <Timer.h>
#include <PubSubClient.h>
#include "constants.h"
#include "mqtt_utils.h"
#include "periphery.h"
#include "EEPROM_utils.h"
#include <avdweb_VirtualDelay.h>

void vRecieveCallback(char* topic, byte* payload, unsigned int length);
void vPostADC(void* vContext);