#pragma once


#include "settings.h"

#include <avdweb_VirtualDelay.h>

#include "periphery.h"
#include "mqtt_utils.h"
#include "EEPROM_utils.h"


void vRecieveCallback(char* topic, byte* payload, unsigned int length);
void vPostADC(void* vContext);
