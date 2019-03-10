// 
// 
// 

#include "serial_utils.h"

Timer xRecieveStringTimer;


void vGetMessage(void* context) {
	String input = "";
	while (Serial.available()) {
		input = Serial.readString();
	}
	if (input != "") {
		if (input == "reset") { //reset to defaults			
			vRestoreDefaultSettings();
			vSaveCurrentSettingsToEEPROM();
			Serial.println("Return to default setting. REBOOT THE DEVICE!");
		} else { //json comes
			char* acInput = new char[input.length() + 1];
			input.toCharArray(acInput, input.length() + 1);
			Serial.println("New settings:");
			Serial.println(acInput);
			int iResult = iGetSettingsFromJson(acInput);
			if (iResult == 0) {
				xGlobalSettings.ulCheckSum = DEFAULT_CRC;
				vSaveCurrentSettingsToEEPROM();
				Serial.println("Success load new settings. REBOOT THE DEVICE!");
			} else { // -1
				Serial.println("Incorrect setting string!");

			}
		}
	}
}


void vInitSerial() {
	Serial.begin(SERIAL_PORT_SPEED);
	delay(1000);
	xRecieveStringTimer.every(SERIAL_PORT_CHECKING_PERIOD_MS, vGetMessage, (void*)0);
}


void vSerialLoop() {
	xRecieveStringTimer.update();
}
