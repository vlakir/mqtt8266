#pragma once

#include <ArduinoJson.h>
#include <Arduino.h>
#include "constants.h"


struct EEPROMStruct {
	char acDeviceID[20];
	char acWiFiSSID[20];
	char acWiFiPassword[20];
	char acMQTTserver[80];
	char acMQTTclientID[20];
	char acMQTTclientPassword[20];
	unsigned int uiMQTTport;
};


EEPROMStruct xRestoreDefaultSettings();
EEPROMStruct xGetFromJson(char* input);