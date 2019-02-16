/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"


EEPROMStruct xSettings = xRestoreDefaultSettings();
PubSubClient xPsClient = xGetPsClient(xSettings.acMQTTserver, xSettings.uiMQTTport, vRecieveCallback);
Timer xPostStateADC, xPostStateGPIO;



void setup() {	
	Serial.begin(SERIAL_PORT_SPEED);		
	initPeripheral();
	vConnectWifi(xSettings.acWiFiSSID, xSettings.acWiFiPassword);
	xPostStateADC.every(ADC_CHECK_PERIOD_MS, vPostADC, (void *) &xPsClient);
	xPostStateGPIO.every(GPIO_CHECK_PERIOD_MS, vPostGPIO, (void *)&xPsClient);	
}


void loop() {
	vMqttLoop(xPsClient, xSettings.acMQTTclientID, xSettings.acMQTTclientPassword);
	xPostStateADC.update();
	xPostStateGPIO.update();

	/*
	String inString;
	while (Serial.available()) {
		char inChar = Serial.read(); 
		if (inChar != 13) {
			inString += inChar;      
		} else {
			Serial.flush();
			//2do: get settings string
		}
	}
	*/

}
