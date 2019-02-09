// 
// 
// 

#include "periphery.h"


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

	Serial.println(acToken);
	Serial.println((char*)abPayload);

	if (strcmp(acToken, "GPIO1") == 0) {
		if (strcmp((char*)abPayload, "1") == 0) {
			digitalWrite(BUILTIN_LED, HIGH);
		} else if (strcmp((char*)abPayload, "0") == 0) {
			digitalWrite(BUILTIN_LED, LOW);
		}
	}


	
	

	/*
	Serial.print("Message arrived [");
	Serial.print(acTopic);
	Serial.print("] ");
	for (int i = 0; i < uiLength; i++) {
		Serial.print((char)abPayload[i]);
	}
	Serial.println();

	// Switch on the LED if an 1 was received as first character
	if ((char)abPayload[0] == '1') {
		digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
		// but actually the LED is on; this is because
		// it is active low on the ESP-01)
	}
	else {
		digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
	}

	*/
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