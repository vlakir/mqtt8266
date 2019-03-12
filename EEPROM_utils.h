#pragma once


#include "settings.h"
#include <ArduinoJson.h>
#include <ESP_EEPROM.h>

void vRestoreDefaultSettings(void);
int iGetSettingsFromJson(char* input);
void vSaveCurrentSettingsToEEPROM(void);
void vGetSettingsFromEEPROM(void);
void vGetGlobalSettings(void);