#pragma once

#include <PubSubClient.h>
#include <avdweb_VirtualDelay.h>
#include <string.h>
#include "constants.h"

void initPeripheral();
void vPostADC(void* context);
void vPostGPIO(void* vContext);
void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength);
char* acGetToken(char* acTopicStr, unsigned int uiNumber);
void vSetOut(byte* abPayload, byte bNumber);
void vStateBit(bool bit, char* acId, PubSubClient *pxPsClient);