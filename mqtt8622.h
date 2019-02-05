#pragma once

#include <Timer.h>
#include "constants.h"
#include "mqtt_utils.h"
#include <avdweb_VirtualDelay.h>

void vRecieveCallback(char* topic, byte* payload, unsigned int length);
void vPostADC(void* context);