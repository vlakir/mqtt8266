#include "checksum.h"


long lGetCRC32ofStruct(struct SettingsStruct xStruct) {
    char acPort[6];
    itoa(xStruct.uiMQTTport, acPort, 10);
    long lStringSize   = sizeof(xStruct.acDeviceID) + sizeof(xStruct.acWiFiSSID) + sizeof(xStruct.acWiFiPassword)
                            + sizeof(xStruct.acMQTTserver) + sizeof(xStruct.acMQTTclientID) + sizeof(xStruct.acDeviceID)
                            + sizeof(acPort);
    char acString[lStringSize];
    for (unsigned long i = 0; i < lStringSize; i++) {
        acString[i] = 0;
    }
    sprintf(acString, "%s%s%s%s%s%s%s", xStruct.acDeviceID, xStruct.acWiFiSSID, xStruct.acWiFiPassword,
            xStruct.acMQTTserver, xStruct.acMQTTclientID, xStruct.acMQTTclientPassword, acPort);
    return lCalculateCRC32(acString, lStringSize);
}

long lCalculateCRC32(char * acString, long lStringSize) {
    long lResult = crc32(0L, Z_NULL, 0);
    for (unsigned long i = 0; i < lStringSize; i++) {
        lResult = crc32(lResult, (const unsigned char *) &acString + i, 1);
    }
    return lResult;
}
