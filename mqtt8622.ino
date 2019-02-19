/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"



//SettingsStruct xGlobalSettings = xRestoreDefaultSettings();

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


char input[] = "{\"device_id\":\"D1_002\",\"wifi_ssid\":\"T_27\",\"wifi_password\":\"begemot2013\", \
					\"mqtt_server\":\"m24.cloudmqtt.com\",\"mqtt_client_id\":\"jyrpzrzt\", \
					\"mqtt_client_password\":\"Z0X_d-YpixmZ\",\"mqtt_port\" :\"19456\"}";

SettingsStruct xGlobalSettings = xGetSettingsFromJson(input);



void setup() {	
	Serial.begin(SERIAL_PORT_SPEED);
	
	vSaveCurrentSettingsToEEPROM();

	xGlobalSettings = xGetSettingsFromEEPROM();
	
	initPeripheral();

	vConnectWifi();

}


void loop() {	

	vMqttLoop();

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
