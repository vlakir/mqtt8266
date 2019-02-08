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
}