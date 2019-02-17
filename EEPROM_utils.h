#pragma once


#include "constants.h"
#include <ArduinoJson.h>
#include <Arduino.h>


SettingsStruct xRestoreDefaultSettings();
SettingsStruct xGetSettingsFromJson(char* input);

