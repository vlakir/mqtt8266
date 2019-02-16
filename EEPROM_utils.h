#pragma once

#include "constants.h"

struct EEPROMStruct {
	char* acDeviceID;
	char* acWiFiSSID;
	char* acWiFiPassword;
	char* acMQTTserver;
	char* acMQTTclientID;
	char* acMQTTclientPassword;
	unsigned int uiMQTTport;
};


EEPROMStruct xRestoreDefaultSettings();