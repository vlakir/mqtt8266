#pragma once


#include "settings.h"
#include <Timer.h>
#include "EEPROM_utils.h"


void vInitSerial(void);
void vSerialLoop(void);

static void _vGetMessage(void* context);
