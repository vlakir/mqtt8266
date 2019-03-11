#pragma once


#include "settings.h"
#include "periphery.h"
#include "mqtt_utils.h"
#include "serial_utils.h"

void vRecieveCallback(char* topic, byte* payload, unsigned int length);
void vPostADC(void* vContext);

void vGetMessage(void* context);
