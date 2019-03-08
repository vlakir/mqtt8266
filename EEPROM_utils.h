#pragma once


#include "settings.h"
#include <ArduinoJson.h>
#include <ESP_EEPROM.h>

SettingsStruct xRestoreDefaultSettings();
SettingsStruct xGetSettingsFromJson(char* input);
void vSaveCurrentSettingsToEEPROM();
void vGetSettingsFromEEPROM();