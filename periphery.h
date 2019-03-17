#pragma once


#include "settings.h"
#include <PubSubClient.h>
#include <avdweb_VirtualDelay.h>
#include <string.h>


void initPeripheral(void);
void vPostADC(void* context);
void vPostGPIO(void* vContext);
void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength);

static char* _acGetToken(char* acTopicStr, unsigned int uiNumber);
static void _vSetOut(char * cMessage, byte bNumber);
static void _vStateBit(unsigned int uiValue, char* acId, PubSubClient *pxPsClient);
static char* _acPayload2string(byte* abPayload, unsigned int uiLength);
