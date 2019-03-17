/*
Vladimir Kirievskiy (C) 2019
********************************************************************************************
* @brief MQTT client software for esp8266 platform (tested on Wemos D1 mini)
* @license MIT
* SDK:	Arduino IDE 1.8.5 with plugin for esp8266
*
********************************************************************************************
* @author V. Kirievskiy aka vlakir
* vladimir@kirievskiy.ru
* https://github.com/vlakir
* This software is furnished "as is", without technical support, and with no
* warranty, express or implied, as to its usefulness for any purpose.
*/


#include "periphery.h"


/*
 * @brief
 * GPIO initialization routine
 *
 */
void initPeripheral (void) {
	//set suitable mode for your device
	pinMode(0, MODE_PIN_0);
	pinMode(2, MODE_PIN_2);
	pinMode(4, MODE_PIN_4);
	pinMode(5, MODE_PIN_5);
	pinMode(12, MODE_PIN_12);
	pinMode(13, MODE_PIN_13);
	pinMode(14, MODE_PIN_14);
	pinMode(15, MODE_PIN_15);
	pinMode(16, MODE_PIN_16);
}


/*
 * @brief
 * Post current ADC value to MQTT broker.
 *
 * @param context - PubSubClient object
 */
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
		sprintf(acTopic, "%s%s%s", xGlobalSettings.acDeviceID, "/state", "/ADC");
		(*pxPsClient).publish(acTopic, acMessage);
	}
}


/*
 * @brief
 * Post current GPIO state to MQTT broker.
 *
 * @param context - PubSubClient object
 */
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
		_vStateBit(bit0, "GPIO0", pxPsClient);
		_vStateBit(bit1, "GPIO2", pxPsClient);
		_vStateBit(bit2, "GPIO4", pxPsClient);
		_vStateBit(bit3, "GPIO5", pxPsClient);
		_vStateBit(bit4, "GPIO12", pxPsClient);
		_vStateBit(bit5, "GPIO13", pxPsClient);
		_vStateBit(bit6, "GPIO14", pxPsClient);
		_vStateBit(bit7, "GPIO15", pxPsClient);
		_vStateBit(bit8, "GPIO16", pxPsClient);
		_vStateBit(uiValue, "GPIOALL", pxPsClient);
	}
}


/*
 * @brief
 * Callback function for recieving command message from MQTT broker and set GPIO
 *
 * @param acTopic - command message
 * @param abPayload - value of command message ("0" or "1")
 * @param uiLength - length of byte array
 */
void vRecieveCallback(char* acTopic, byte* abPayload, unsigned int uiLength) {	
	char acToken[20];
	strcpy(acToken, _acGetToken(acTopic, 2));
	char * acMessage = _acPayload2string(abPayload, uiLength);
	if (strcmp(acToken, "GPIO0") == 0) {
		_vSetOut(acMessage, 0);
	} else if (strcmp(acToken, "GPIO2") == 0) {
		_vSetOut(acMessage, 2); // BUILTIN_LED for WEMOS D1 mini
	} else if (strcmp(acToken, "GPIO4") == 0) {
		_vSetOut(acMessage, 4); 
	} else if (strcmp(acToken, "GPIO5") == 0) {
		_vSetOut(acMessage, 5);
	} else if (strcmp(acToken, "GPIO12") == 0) {
		_vSetOut(acMessage, 12);
	} else if (strcmp(acToken, "GPIO13") == 0) {
		_vSetOut(acMessage, 13);
	} else if (strcmp(acToken, "GPIO14") == 0) {
		_vSetOut(acMessage, 14);
	} else if (strcmp(acToken, "GPIO15") == 0) {
		_vSetOut(acMessage, 15);
	} else if (strcmp(acToken, "GPIO16") == 0) {
		_vSetOut(acMessage, 16);
	} else if (strcmp(acToken, "GPIOALL") == 0) {
		_vSetOut(acMessage, 0);
		_vSetOut(acMessage, 2); // BUILTIN_LED for WEMOS D1 mini
		_vSetOut(acMessage, 4);
		_vSetOut(acMessage, 5);
		_vSetOut(acMessage, 12);
		_vSetOut(acMessage, 13);
		_vSetOut(acMessage, 14);
		_vSetOut(acMessage, 15);
		_vSetOut(acMessage, 16);
	}
}


/*
 * @brief
 * Tokenize topic message from MQTT broker and return uiNumber member of it
 *
 * @param acTopicStr - topic message
 * @param uiNumber - number of returned member
 * @return - selected member of topic message
 */
static char* _acGetToken(char* acTopicStr, unsigned int uiNumber) {
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

/*
 * @brief
 * Set bOutNumber GPIO to state defined cMessage value
 *
 * @param cMessage - message ("0" of "1")
 * @param bOutNumber - GPIO number
 */
static void _vSetOut(char * cMessage, byte bOutNumber) {
	if (strcmp(cMessage, "1") == 0) {
		digitalWrite(bOutNumber, HIGH);
	}
	else if (strcmp(cMessage, "0") == 0) {
		digitalWrite(bOutNumber, LOW);
	}
}


/*
 * @brief
 * Prepare topic string and send it to MQTT broker
 *
 * @param uiValue - value of sending parameter 
 * @param acId - name of parameter (e.g. "ADC" or "GPIO1")
 * @param pxPsClient - PubSubClient object
 */
static void _vStateBit(unsigned int uiValue, char* acId, PubSubClient *pxPsClient) {
	char acMessage[33];
	char acTopic[80];	
	sprintf(acMessage, "%d", uiValue);
	sprintf(acTopic, "%s%s%s", xGlobalSettings.acDeviceID, "/state/", acId);
	(*pxPsClient).publish(acTopic, acMessage);
	
}


/*
 * @brief
 * Convert byte array to string
 *
 * @param abPayload - byte array
 * @param uiLength - length of byte array
 * @return - converted string
 */
static char* _acPayload2string(byte* abPayload, unsigned int uiLength) {

	char* acMessageBuffer = new char[uiLength+1];

	int i;
	for (i = 0; i < uiLength; i++) {
		acMessageBuffer[i] = abPayload[i];
	}
	acMessageBuffer[uiLength] = '\0';
	return acMessageBuffer;
}