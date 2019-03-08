#pragma once

#include <Arduino.h>

#define DEFAULT_DEVICE_UNIQ_ID "D1_001"
#define DEFAULT_WIFI_SSID "T_27"
#define DEFAULT_WIFI_PASSWORD "begemot2013"
#define DEFAULT_MQTT_SERVER "m24.cloudmqtt.com"
#define DEFAULT_MQTT_CLIENT_ID "jyrpzrzt"
#define DEFAULT_MQTT_CLIENT_PASSWORD "Z0X_d-YpixmZ"
#define DEFAULT_MQTT_PORT 19456
#define DEFAULT_CRC 67868689UL

#define SERIAL_PORT_SPEED 115200
#define ADC_CHECK_PERIOD_MS 1000
#define FORCE_ADC_PUBLISH_PERIOD_MS 10000
#define GPIO_CHECK_PERIOD_MS 2000
#define FORCE_GPIO_PUBLISH_PERIOD_MS 20000

struct SettingsStruct {
	char acDeviceID[20];
	char acWiFiSSID[20];
	char acWiFiPassword[20];
	char acMQTTserver[80];
	char acMQTTclientID[20];
	char acMQTTclientPassword[20];
	unsigned int uiMQTTport;
	unsigned long lCheckSum;
};

extern SettingsStruct xGlobalSettings;
