#pragma once

#include <PubSubClient.h>
#include <avdweb_VirtualDelay.h>
#include "constants.h"

void vPostADC(void* context);
void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength);

