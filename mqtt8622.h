#pragma once

#include <Timer.h>
#include "constants.h"
#include "mqtt_utils.h"

void callback(char* topic, byte* payload, unsigned int length);
void vPostMessage();