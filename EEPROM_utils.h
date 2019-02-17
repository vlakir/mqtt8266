#pragma once


#include "settings.h"
#include <ArduinoJson.h>
#include <Arduino.h>


SettingsStruct xRestoreDefaultSettings();
SettingsStruct xGetSettingsFromJson(char* input);

