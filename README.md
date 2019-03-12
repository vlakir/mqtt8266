# mqtt8622

MQTT client software for esp8266 platform

It was tested on Wemos D1 mini, but could be adapted to any another esp8622 platform with minamal code changes.

Header file settings.h includes default values of all important system settings: wifi ssid and password, access rules for mqtt broker, timeouts and delays. Some of them can be load from serial terminal (see: serial_utils.cpp) or from EEPROM (see: EEPROM_utils.cpp).

The program publishes to the broker:
- current state of 9 GPIOs: separately as messages of topics <DEVICE NAME>/state/GPIOxx or all together as 9-bit word as message of topic <DEVICE NAME>/state/GPIOALL;
- current value of ADC input as 
  
The program subscribes on the broker:
- commands of GPIO control as messages of topics <DEVICE NAME>/management/GPIOxx

