// 
// 
// 

#include "EEPROM_utils.h"


SettingsStruct xRestoreDefaultSettings() {	
	SettingsStruct xSettings;	
	strcpy(xSettings.acDeviceID, DEFAULT_DEVICE_UNIQ_ID);
	strcpy(xSettings.acWiFiSSID, DEFAULT_WIFI_SSID);
	strcpy(xSettings.acWiFiPassword, DEFAULT_WIFI_PASSWORD);
	strcpy(xSettings.acMQTTserver, DEFAULT_MQTT_SERVER);
	strcpy(xSettings.acMQTTclientID, DEFAULT_MQTT_CLIENT_ID);
	strcpy(xSettings.acMQTTclientPassword, DEFAULT_MQTT_CLIENT_PASSWORD);
	xSettings.uiMQTTport = DEFAULT_MQTT_PORT;
	return xSettings;
}


SettingsStruct xGetSettingsFromJson(char* input) {
	SettingsStruct xSettings;
	const int capacity = JSON_OBJECT_SIZE(7);
	StaticJsonBuffer<capacity> jb;
	JsonObject& obj = jb.parseObject(input);
	if (obj.success()) {
		strcpy(xSettings.acDeviceID, obj["device_id"]);
		strcpy(xSettings.acWiFiSSID, obj["wifi_ssid"]);
		strcpy(xSettings.acWiFiPassword, obj["wifi_password"]);
		strcpy(xSettings.acMQTTserver, obj["mqtt_server"]);
		strcpy(xSettings.acMQTTclientID, obj["mqtt_client_id"]);
		strcpy(xSettings.acMQTTclientPassword, obj["mqtt_client_password"]);
		xSettings.uiMQTTport = atoi(obj["mqtt_port"]);
		return xSettings;
	}
	else {
		Serial.println("JSON parse fault. Return to default settings");
		return xRestoreDefaultSettings();
	}
}

void vSaveCurrentSettingsToEEPROM() {	
	EEPROM.begin(sizeof(SettingsStruct));
	EEPROM.put(0, xGlobalSettings);
	boolean ok1 = EEPROM.commitReset();
	Serial.println((ok1) ? "Commit EEPROM OK" : "Commit EEPROM failed");	
}

