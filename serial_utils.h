#pragma once

#include "settings.h"
#include <Timer.h>
#include "EEPROM_utils.h"

void vInitSerial();
void vGetMessage(void* context);
void vSerialLoop();

