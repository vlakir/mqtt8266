
#include "EEPROM_utils.h"


void vRestoreDefaultSettings() {	
	strcpy(xGlobalSettings.acDeviceID, DEFAULT_DEVICE_UNIQ_ID);
	strcpy(xGlobalSettings.acWiFiSSID, DEFAULT_WIFI_SSID);
	strcpy(xGlobalSettings.acWiFiPassword, DEFAULT_WIFI_PASSWORD);
	strcpy(xGlobalSettings.acMQTTserver, DEFAULT_MQTT_SERVER);
	strcpy(xGlobalSettings.acMQTTclientID, DEFAULT_MQTT_CLIENT_ID);
	strcpy(xGlobalSettings.acMQTTclientPassword, DEFAULT_MQTT_CLIENT_PASSWORD);
	xGlobalSettings.uiMQTTport = DEFAULT_MQTT_PORT;
	xGlobalSettings.ulCheckSum = DEFAULT_CRC;
}


int iGetSettingsFromJson(char* input) {
	const int capacity = JSON_OBJECT_SIZE(7);
	StaticJsonBuffer<capacity> jb;
	JsonObject& obj = jb.parseObject(input);
	if (obj.success()) {
		strcpy(xGlobalSettings.acDeviceID, obj["device_id"]);
		strcpy(xGlobalSettings.acWiFiSSID, obj["wifi_ssid"]);
		strcpy(xGlobalSettings.acWiFiPassword, obj["wifi_password"]);
		strcpy(xGlobalSettings.acMQTTserver, obj["mqtt_server"]);
		strcpy(xGlobalSettings.acMQTTclientID, obj["mqtt_client_id"]);
		strcpy(xGlobalSettings.acMQTTclientPassword, obj["mqtt_client_password"]);
		xGlobalSettings.uiMQTTport = atoi(obj["mqtt_port"]);
		xGlobalSettings.ulCheckSum = DEFAULT_CRC;
		return 0;
	}
	else { //JSON parse fault
		return -1;
	}
}


void vSaveCurrentSettingsToEEPROM() {	
	EEPROM.begin(sizeof(SettingsStruct));
	EEPROM.put(0, xGlobalSettings);
	boolean ok1 = EEPROM.commitReset();
	Serial.println((ok1) ? "Commit EEPROM OK" : "Commit EEPROM failed");	
}

void vGetSettingsFromEEPROM() {
	EEPROM.begin(sizeof(SettingsStruct));
	EEPROM.get(0, xGlobalSettings);
}

void vGetGlobalSettings() {
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