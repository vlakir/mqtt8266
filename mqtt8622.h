#pragma once


#include "settings.h"
#include <Timer.h>
#include <PubSubClient.h>
#include <avdweb_VirtualDelay.h>

#include "mqtt_utils.h"
#include "periphery.h"
#include "EEPROM_utils.h"


void vRecieveCallback(char* topic, byte* payload, unsigned int length);
void vPostADC(void* vContext);
