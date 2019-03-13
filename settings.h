#pragma once


#include <Arduino.h>


#define DEFAULT_DEVICE_UNIQ_ID "D1_001"
#define DEFAULT_WIFI_SSID "T**"
#define DEFAULT_WIFI_PASSWORD "b**********"
#define DEFAULT_MQTT_SERVER "m**.cloudmqtt.com"
#define DEFAULT_MQTT_CLIENT_ID "j*******"
#define DEFAULT_MQTT_CLIENT_PASSWORD "Z************"
#define DEFAULT_MQTT_PORT 19456
#define DEFAULT_CRC 4285178124UL                    
#define SERIAL_PORT_SPEED 115200
#define ADC_CHECK_PERIOD_MS 1000
#define FORCE_ADC_PUBLISH_PERIOD_MS 10000
#define GPIO_CHECK_PERIOD_MS 2000
#define FORCE_GPIO_PUBLISH_PERIOD_MS 20000
#define SERIAL_PORT_CHECKING_PERIOD_MS 1000
#define WAIT_FOR_NEXT_MQTT_CONNECTION_MS 2000
#define MODE_PIN_0 OUTPUT
#define MODE_PIN_2 OUTPUT
#define MODE_PIN_4 OUTPUT
#define MODE_PIN_5 OUTPUT
#define MODE_PIN_12 INPUT
#define MODE_PIN_13 INPUT
#define MODE_PIN_14 INPUT
#define MODE_PIN_15 INPUT
#define MODE_PIN_16 INPUT





struct SettingsStruct {
	char acDeviceID[20];
	char acWiFiSSID[20];
	char acWiFiPassword[20];
	char acMQTTserver[80];
	char acMQTTclientID[20];
	char acMQTTclientPassword[20];
	unsigned int uiMQTTport;
	unsigned long ulCheckSum;
};


extern SettingsStruct xGlobalSettings;
