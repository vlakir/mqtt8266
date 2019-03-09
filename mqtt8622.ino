/*
 Name:		mqtt8622.ino
 Created:	1/25/2019 11:41:47 PM
 Author:	Vladimir
*/

#include "mqtt8622.h"

//SettingsStruct xGlobalSettings = xRestoreDefaultSettings();

SettingsStruct xGlobalSettings;

Timer xRecieveCOM;


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


void vGetMessage(void* context) {
	String input = "";
	while (Serial.available()) {
		input = Serial.readString();
	}
	if (input != "") {				
		char acInput [input.length() + 1];
		input.toCharArray(acInput, input.length() + 1);	
		Serial.println(acInput);
		Serial.println(input.length());
		xGlobalSettings = xGetSettingsFromJson(acInput);
		xGlobalSettings.lCheckSum = DEFAULT_CRC;
		vSaveCurrentSettingsToEEPROM();
		Serial.println("Success load settings!");
	}
}



void setup() {	
	Serial.begin(SERIAL_PORT_SPEED);		
	
	delay(1000);

	Serial.println("\n\n\nTry to get settings from EEPROM...");
	vGetSettingsFromEEPROM();

	Serial.println(xGlobalSettings.lCheckSum);
	Serial.println(xGlobalSettings.acWiFiSSID);

	if (xGlobalSettings.lCheckSum != DEFAULT_CRC) { //no settings in EEPROM
		Serial.println("No saved settings, use default.");
		xGlobalSettings = xRestoreDefaultSettings();


		Serial.println(xGlobalSettings.lCheckSum);



		vSaveCurrentSettingsToEEPROM();
	}
	else {
		Serial.println("Success!");
	}
	

	initPeripheral();

	vConnectWifi();

	xRecieveCOM.every(1000, vGetMessage, (void*)0);


}


void loop() {	

	vMqttLoop();


	xRecieveCOM.update();




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
