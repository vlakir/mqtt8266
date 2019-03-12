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


#include "EEPROM_utils.h"

/*
 * @brief
 * Restore xGlobalSettings from defines in settings.h
 *
 */
void vRestoreDefaultSettings(void) {	
	strcpy(xGlobalSettings.acDeviceID, DEFAULT_DEVICE_UNIQ_ID);
	strcpy(xGlobalSettings.acWiFiSSID, DEFAULT_WIFI_SSID);
	strcpy(xGlobalSettings.acWiFiPassword, DEFAULT_WIFI_PASSWORD);
	strcpy(xGlobalSettings.acMQTTserver, DEFAULT_MQTT_SERVER);
	strcpy(xGlobalSettings.acMQTTclientID, DEFAULT_MQTT_CLIENT_ID);
	strcpy(xGlobalSettings.acMQTTclientPassword, DEFAULT_MQTT_CLIENT_PASSWORD);
	xGlobalSettings.uiMQTTport = DEFAULT_MQTT_PORT;
	xGlobalSettings.ulCheckSum = DEFAULT_CRC;
}

/*
 * @brief
 * Convert JSON string (see: /doc/settings_example.txt) to xGlobalSettings.
 *
 * @param acInput - JSON string
 * @return 0 if conversion ok, -1 in case of some error
 */
int iGetSettingsFromJson(char* acInput) {
	const int capacity = JSON_OBJECT_SIZE(7);
	StaticJsonBuffer<capacity> xJsonBuffer;
	JsonObject& xJsonObject = xJsonBuffer.parseObject(acInput);
	if (xJsonObject.success()) {
		strcpy(xGlobalSettings.acDeviceID, xJsonObject["device_id"]);
		strcpy(xGlobalSettings.acWiFiSSID, xJsonObject["wifi_ssid"]);
		strcpy(xGlobalSettings.acWiFiPassword, xJsonObject["wifi_password"]);
		strcpy(xGlobalSettings.acMQTTserver, xJsonObject["mqtt_server"]);
		strcpy(xGlobalSettings.acMQTTclientID, xJsonObject["mqtt_client_id"]);
		strcpy(xGlobalSettings.acMQTTclientPassword, xJsonObject["mqtt_client_password"]);
		xGlobalSettings.uiMQTTport = atoi(xJsonObject["mqtt_port"]);
		xGlobalSettings.ulCheckSum = DEFAULT_CRC;
		return 0;
	}
	else { //JSON parse fault
		return -1;
	}
}

/*
 * @brief
 * Save xGlobalSettings to EEPROM
 *
 */
void vSaveCurrentSettingsToEEPROM(void) {
	EEPROM.begin(sizeof(SettingsStruct));
	EEPROM.put(0, xGlobalSettings);
	boolean ok1 = EEPROM.commitReset();
	Serial.println((ok1) ? "Commit EEPROM OK" : "Commit EEPROM failed");	
}


/*
 * @brief
 * Restore xGlobalSettings from EEPROM
 *
 */
void vGetSettingsFromEEPROM(void) {
	EEPROM.begin(sizeof(SettingsStruct));
	EEPROM.get(0, xGlobalSettings);
}


/*
 * @brief
 * Restore xGlobalSettings from EEPROM if they are stored there or from defines in settings.h
 *
 */
void vGetGlobalSettings(void) {
	Serial.println("\n\n\nTry to get settings from EEPROM...");
	vGetSettingsFromEEPROM();
	if (xGlobalSettings.ulCheckSum != DEFAULT_CRC) { //no settings in EEPROM
		Serial.println("No saved settings, use default.");
		vRestoreDefaultSettings();
		Serial.println(xGlobalSettings.ulCheckSum);
		vSaveCurrentSettingsToEEPROM();
	}
	else {
		Serial.println("Success!");
	}
}