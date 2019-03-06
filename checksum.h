#pragma once

#include "settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/zlib/zlib.h"

//uLong crc32 (uLong crc, const Bytef *buf, uInt len);

long lGetCRC32ofStruct(struct SettingsStruct sStruct);
long lCalculateCRC32(char *mergedString, long mergedStringSize);


