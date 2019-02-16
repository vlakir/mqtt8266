// 
// 
// 

#include "EEPROM_utils.h"

struct EEPROMStruct {
	char acDeviceID [20];
	char acWiFiSSID[20];
	char acWiFiPassword[20];
	char acMQTTserver[50];
	char acMQTTclientID[20];
	char acMQTTclientPassword[20];
	unsigned int uiMQTTport;
}  xSettings;



