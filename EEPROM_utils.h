#pragma once


#include "settings.h"
#include <ArduinoJson.h>
#include <ESP_EEPROM.h>

void vRestoreDefaultSettings();
int iGetSettingsFromJson(char* input);
void vSaveCurrentSettingsToEEPROM();
void vGetSettingsFromEEPROM();
void vGetGlobalSettings();