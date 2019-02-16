// 
// 
// 

#include "periphery.h"


void initPeripheral () {
	//set suitable for your device
	pinMode(0, OUTPUT);
	pinMode(2, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(12, INPUT);
	pinMode(13, INPUT);
	pinMode(14, INPUT);
	pinMode(15, INPUT);
	pinMode(16, INPUT);
}


void vPostADC(void* vContext) {
	static unsigned int uiOld;
	static VirtualDelay singleDelay;
	PubSubClient *pxPsClient = (PubSubClient *)vContext;
	
	DO_ONCE(
		uiOld = 1025; // initial unreal value for 10-bit ADC
	);

	singleDelay.start(FORCE_ADC_PUBLISH_PERIOD_MS);
	if (singleDelay.elapsed()) {
		uiOld = 1025; // to remind of itself even if nothing has changed
	}

	unsigned int uiADC = analogRead(A0);
	
	if (uiADC != uiOld) {
		uiOld = uiADC;
		char acMessage[33];
		char acTopic[80];
		sprintf(acMessage, "%d", uiADC);
		sprintf(acTopic, "%s%s%s", DEFAULT_DEVICE_UNIQ_ID, "/state", "/ADC");

		(*pxPsClient).publish(acTopic, acMessage);
	}
}


void vPostGPIO(void* vContext) {
	static unsigned int uiOld;
	static VirtualDelay singleDelay;
	PubSubClient *pxPsClient = (PubSubClient *)vContext;

	DO_ONCE(
		uiOld = 513; // initial unreal value
	);

	singleDelay.start(FORCE_GPIO_PUBLISH_PERIOD_MS);
	if (singleDelay.elapsed()) {
		uiOld = 513; // to remind of itself even if nothing has changed
	}

	bool bit0 = digitalRead(0);
	bool bit1 = digitalRead(2);
	bool bit2 = digitalRead(4);
	bool bit3 = digitalRead(5);
	bool bit4 = digitalRead(12);
	bool bit5 = digitalRead(13);
	bool bit6 = digitalRead(14);
	bool bit7 = digitalRead(15);
	bool bit8 = digitalRead(16);

	unsigned int uiValue = bit0 + 2 * bit1 + 4 * bit2 + 8 * bit3 + 16 * bit4 + 
		                   32 * bit5 + 64 * bit6 + 128 * bit7 + 256 * bit8;

	if (uiValue != uiOld) {
		uiOld = uiValue;		
		vStateBit(bit0, "GPIO0", pxPsClient);
		vStateBit(bit1, "GPIO2", pxPsClient);
		vStateBit(bit2, "GPIO4", pxPsClient);
		vStateBit(bit3, "GPIO5", pxPsClient);
		vStateBit(bit4, "GPIO12", pxPsClient);
		vStateBit(bit5, "GPIO13", pxPsClient);
		vStateBit(bit6, "GPIO14", pxPsClient);
		vStateBit(bit7, "GPIO15", pxPsClient);
		vStateBit(bit8, "GPIO16", pxPsClient);
		vStateBit(uiValue, "GPIOALL", pxPsClient);
	}
}


void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength) {	
	char acToken[20];
	strcpy(acToken, acGetToken(acTopic, 2));
	char * acMessage = acPayload2string(abPayload, uiLength);
	if (strcmp(acToken, "GPIO0") == 0) {
		vSetOut(acMessage, 0);
	} else if (strcmp(acToken, "GPIO2") == 0) {
		vSetOut(acMessage, 2); // BUILTIN_LED for WEMOS D1 mini
	} else if (strcmp(acToken, "GPIO4") == 0) {
		vSetOut(acMessage, 4); 
	} else if (strcmp(acToken, "GPIO5") == 0) {
		vSetOut(acMessage, 5);
	} else if (strcmp(acToken, "GPIO12") == 0) {
		vSetOut(acMessage, 12);
	} else if (strcmp(acToken, "GPIO13") == 0) {
		vSetOut(acMessage, 13);
	} else if (strcmp(acToken, "GPIO14") == 0) {
		vSetOut(acMessage, 14);
	} else if (strcmp(acToken, "GPIO15") == 0) {
		vSetOut(acMessage, 15);
	} else if (strcmp(acToken, "GPIO16") == 0) {
		vSetOut(acMessage, 16);
	} else if (strcmp(acToken, "GPIOALL") == 0) {
		vSetOut(acMessage, 0);
		vSetOut(acMessage, 2); // BUILTIN_LED for WEMOS D1 mini
		vSetOut(acMessage, 4);
		vSetOut(acMessage, 5);
		vSetOut(acMessage, 12);
		vSetOut(acMessage, 13);
		vSetOut(acMessage, 14);
		vSetOut(acMessage, 15);
		vSetOut(acMessage, 16);
	}
}


char* acGetToken(char* acTopicStr, unsigned int uiNumber) {
	char acTopic[80];
	strcpy(acTopic, acTopicStr);
	char* aacTokens[20];
	aacTokens[0] = strtok(acTopic, "/");
	int i = 0;
	while (aacTokens[i] != NULL) {
		i++;
		aacTokens[i] = strtok(NULL, "/");
	}
	return aacTokens[uiNumber];
}


void vSetOut(char * cMessage, byte bNumber) {
	if (strcmp(cMessage, "1") == 0) {
		digitalWrite(bNumber, HIGH);
	}
	else if (strcmp(cMessage, "0") == 0) {
		digitalWrite(bNumber, LOW);
	}
}


void vStateBit(unsigned int uiValue, char* acId, PubSubClient *pxPsClient) {
	char acMessage[33];
	char acTopic[80];	
	sprintf(acMessage, "%d", uiValue);
	sprintf(acTopic, "%s%s%s", DEFAULT_DEVICE_UNIQ_ID, "/state/", acId);
	(*pxPsClient).publish(acTopic, acMessage);
	
}


char * acPayload2string(byte* abPayload, unsigned int uiLength) {

	char* acMessageBuffer = new char[uiLength+1];

	int i;
	for (i = 0; i < uiLength; i++) {
		acMessageBuffer[i] = abPayload[i];
	}
	acMessageBuffer[uiLength] = '\0';
	return acMessageBuffer;
}