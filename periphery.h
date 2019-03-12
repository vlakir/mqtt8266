#pragma once


#include "settings.h"
#include <PubSubClient.h>
#include <avdweb_VirtualDelay.h>
#include <string.h>


void initPeripheral(void);
void vPostADC(void* context);
void vPostGPIO(void* vContext);
void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength);
char* acGetToken(char* acTopicStr, unsigned int uiNumber);
void vSetOut(char * cMessage, byte bNumber);
void vStateBit(unsigned int uiValue, char* acId, PubSubClient *pxPsClient);
char * acPayload2string(byte* abPayload, unsigned int uiLength);
