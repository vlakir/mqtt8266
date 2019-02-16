// 
// 
// 

#include "EEPROM_utils.h"

EEPROMStruct xRestoreDefaultSettings() {
	EEPROMStruct xSettings;
	xSettings.acDeviceID = DEFAULT_DEVICE_UNIQ_ID;
	xSettings.acWiFiSSID = DEFAULT_WIFI_SSID;
	xSettings.acWiFiPassword = DEFAULT_WIFI_PASSWORD;
	xSettings.acMQTTserver = DEFAULT_MQTT_SERVER;
	xSettings.acMQTTclientID = DEFAULT_MQTT_CLIENT_ID;
	xSettings.acMQTTclientPassword = DEFAULT_MQTT_CLIENT_PASSWORD;
	xSettings.uiMQTTport = DEFAULT_MQTT_PORT;
	return xSettings;
}



