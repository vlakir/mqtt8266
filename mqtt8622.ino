/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"

//SettingsStruct xGlobalSettings = xRestoreDefaultSettings();

SettingsStruct xGlobalSettings;


/*
{
	"device_id": "D1_001",
	"wifi_ssid": "T_27",
	"wifi_password": "begemot2013",
	"mqtt_server": "m24.cloudmqtt.com",
	"mqtt_client_id": "jyrpzrzt",
	"mqtt_client_password": "Z0X_d-YpixmZ",
	"mqtt_port": "19456"
}
*/

/*
char input[] = "{\"device_id\":\"D1_002\",\"wifi_ssid\":\"T_27\",\"wifi_password\":\"begemot2013\", \
					\"mqtt_server\":\"m24.cloudmqtt.com\",\"mqtt_client_id\":\"jyrpzrzt\", \
					\"mqtt_client_password\":\"Z0X_d-YpixmZ\",\"mqtt_port\" :\"19456\"}";
*/


void setup() {	
	Serial.begin(SERIAL_PORT_SPEED);	

	xGlobalSettings = xRestoreDefaultSettings();

	/*
	xGlobalSettings = xGetSettingsFromEEPROM();

	if (strcmp(xGlobalSettings.acDeviceID, "") == 0) { //no settings in EEPROM
		
	}
	*/

	initPeripheral();

	vConnectWifi();

	struct SettingsStruct xStruct;

	strcpy(xStruct.acDeviceID, "11134");
	strcpy(xStruct.acWiFiSSID, "22822");
	strcpy(xStruct.acWiFiPassword, "33493");
	strcpy(xStruct.acMQTTserver, "444654");
	strcpy(xStruct.acMQTTclientID, "55234554");
	strcpy(xStruct.acMQTTclientPassword, "63256666");
	xStruct.uiMQTTport = 6901;

	xStruct.lCheckSum = lGetCRC32ofStruct(xStruct);

	printf("%lx%s", xStruct.lCheckSum, "\n");

}


void loop() {	

	vMqttLoop();		
	
	/*
	String inString;
	char * acBuffer;

	while (Serial.available()) {
		char inChar = Serial.read(); 
		if (inChar != 13) {
			inString += inChar;      
		} else {
			Serial.flush();
			inString.toCharArray(acBuffer, inString.length());
			xGlobalSettings = xGetSettingsFromJson(acBuffer);
			vSaveCurrentSettingsToEEPROM();
		}
	}
	*/

}
