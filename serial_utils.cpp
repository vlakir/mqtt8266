/*
Vladimir Kirievskiy (C) 2019
********************************************************************************************
* @brief MQTT client software for esp8266 platform (tested on Wemos D1 mini)
* @license MIT
* SDK:	Arduino IDE 1.8.5 with plugin for esp8266
*
********************************************************************************************
* @author V. Kirievskiy aka vlakir
* vladimir@kirievskiy.ru
* https://github.com/vlakir
* This software is furnished "as is", without technical support, and with no
* warranty, express or implied, as to its usefulness for any purpose.
*/


#include "serial_utils.h"


Timer xRecieveStringTimer;





/*
 * @brief
 * Serial port initialization routine
 *
 */
void vInitSerial(void) {
	Serial.begin(SERIAL_PORT_SPEED);
	delay(1000);
	xRecieveStringTimer.every(SERIAL_PORT_CHECKING_PERIOD_MS, _vGetMessage, (void*)0);
}


/*
 * @brief
 * Serial scan procedure for placement in the main loop
 *
 */
void vSerialLoop(void) {
	xRecieveStringTimer.update();
}


/*
 * @brief
 * Get JSON string from serial port, parse it and save it to xGlobalSettings and EEPROM.
 * See /doc/settings_example.txt
 * If word "reset" comes then set xGlobalSettings to defaults (see settings.h)
 *
 * @param context - dummy variable need for compatibility with Timer v2.1 only
 */
static void _vGetMessage(void* context) {
	String input = "";
	while (Serial.available()) {
		input = Serial.readString();
	}
	if (input != "") {
		if (input == "reset") { //reset to defaults			
			vRestoreDefaultSettings();
			vSaveCurrentSettingsToEEPROM();
			Serial.println("Return to default setting. REBOOT THE DEVICE!");
		}
		else { //json comes
			char* acInput = new char[input.length() + 1];
			input.toCharArray(acInput, input.length() + 1);
			Serial.println("New settings:");
			Serial.println(acInput);
			int iResult = iGetSettingsFromJson(acInput);
			if (iResult == 0) {
				xGlobalSettings.ulCheckSum = DEFAULT_CRC;
				vSaveCurrentSettingsToEEPROM();
				Serial.println("Success load new settings. REBOOT THE DEVICE!");
			}
			else { // -1
				Serial.println("Incorrect setting string!");
			}
		}
	}
}