# mqtt8622

## MQTT client for esp8266 platform

## Important notes

It was tested on Wemos D1 mini but could be easy adapted for any other esp8622 platform.

Header file settings.h includes default values of all important system settings: device name, wifi ssid and password, access rules for mqtt broker, timeouts and delays. Some of them can be load from serial terminal (see: serial_utils.cpp) or from EEPROM (see: EEPROM_utils.cpp).

The program publishes:
- current state of 9 GPIOs: separately as messages of topics DEVICE_NAME/state/GPIOxx or all together as 9-bit word as message of topic DEVICE_NAME/state/GPIOALL;
- current value of ADC input as DEVICE_NAME/state/ADC
  
The program subscribes:
- commands of GPIO control as messages of topics DEVICE NAME/management/GPIOxx

## Built With

* [PubSubClient](https://github.com/knolleary/pubsubclient)
* [ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)
* [Timer v2.1](https://github.com/JChristensen/Timer/tree/v2.1) 
* [ArduinoJson](https://github.com/bblanchon/ArduinoJson) 
* [ESP_EEPROM](https://github.com/jwrw/ESP_EEPROM) 
* [VirtualDelay](https://github.com/avandalen/VirtualDelay)

## Author

**Vladimir Kirievskiy** 

## License

This project is licensed under the MIT License

This software is furnished "as is", without technical support, and with no warranty, express or implied, as to its usefulness for any purpose.
