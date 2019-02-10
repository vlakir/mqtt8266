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
	pinMode(12, OUTPUT);
	pinMode(13, OUTPUT);
	pinMode(14, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
}


void vPostADC(void* vContext) {
	static unsigned int uiOld;
	VirtualDelay singleDelay;
	PubSubClient *pxPsClient = (PubSubClient *)vContext;
	
	DO_ONCE(
		uiOld = 1025; // initial unreal value for 10-bit ADC
	);

	singleDelay.start(FORCE_PUBLISH_PERIOD_MS);
	if (singleDelay.elapsed()) {
		uiOld = 1025; // to remind of itself even if nothing has changed
	}

	unsigned int uiADC = analogRead(A0);
	
	if (uiADC != uiOld) {
		uiOld = uiADC;
		char acMessage[33];
		char acTopic[80];
		sprintf(acMessage, "%d", uiADC);
		sprintf(acTopic, "%s%s%s", DEVICE_UNIQ_ID, "/state", "/ADC");

		(*pxPsClient).publish(acTopic, acMessage);
	}
}


void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength) {	
	char acToken[20];
	strcpy(acToken, acGetToken(acTopic, 2));
	if (strcmp(acToken, "GPIO0") == 0) {
		setOut(abPayload, 0);
	} else if (strcmp(acToken, "GPIO2") == 0) {
		setOut(abPayload, 2);
	} else if (strcmp(acToken, "GPIO4") == 0) {
		setOut(abPayload, 4); // BUILTIN_LED for WEMOS D1 mini
	} else if (strcmp(acToken, "GPIO5") == 0) {
		setOut(abPayload, 5);
	} else if (strcmp(acToken, "GPIO12") == 0) {
		setOut(abPayload, 12);
	} else if (strcmp(acToken, "GPIO13") == 0) {
		setOut(abPayload, 13);
	} else if (strcmp(acToken, "GPIO14") == 0) {
		setOut(abPayload, 14);
	} else if (strcmp(acToken, "GPIO15") == 0) {
		setOut(abPayload, 15);
	} else if (strcmp(acToken, "GPIO16") == 0) {
		setOut(abPayload, 16);
	} else if (strcmp(acToken, "GPIOALL") == 0) {
		setOut(abPayload, 0);
		setOut(abPayload, 2);
		setOut(abPayload, 4);
		setOut(abPayload, 5);
		setOut(abPayload, 12);
		setOut(abPayload, 13);
		setOut(abPayload, 14);
		setOut(abPayload, 15);
		setOut(abPayload, 16);
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


void setOut(byte* abPayload, byte bNumber) {
	if (strcmp((char*)abPayload, "1") == 0) {
		digitalWrite(bNumber, HIGH);
	}
	else if (strcmp((char*)abPayload, "0") == 0) {
		digitalWrite(bNumber, LOW);
	}
}