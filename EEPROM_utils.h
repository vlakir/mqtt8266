#pragma once


#include "settings.h"
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP_EEPROM.h>

SettingsStruct xRestoreDefaultSettings();
SettingsStruct xGetSettingsFromJson(char* input);
void vSaveCurrentSettingsToEEPROM();
SettingsStruct xGetSettingsFromEEPROM();