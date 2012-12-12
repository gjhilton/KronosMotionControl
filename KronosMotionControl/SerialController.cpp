#include "SerialController.h"
#include <string.h>

#define STR_ERROR_LINE_ENDING			"Please turn off sending line endings"
#define STR_ERROR_TOO_MANY_CALLBACKS 	"Error"
#define STR_ERROR_UNRECOGNISED			"Unrecognised command: "
#define STR_MENU						"AVAILABLE COMMANDS\n------------------\n"
#define STR_MENU_SPACER					" -> "
#define STR_READY						"Serial: ready"

SerialController::SerialController(int baud){
	baudrate = baud;
	nCallbacks = 0;
}

void SerialController::begin(){
	Serial.begin(baudrate);
	while (!Serial) {
		;
	}
	while (Serial.available() <= 0) {
		Serial.println(STR_READY);
		delay(1000); // ie 1 second
	}
}

void SerialController::loop(){
	if (Serial.available() > 0) {
		int inByte = Serial.read();
		if (inByte == 10 || inByte == 13){
			// complain if we're being sent line endings
			Serial.println(STR_ERROR_LINE_ENDING);
			return;
		}
		for (int i=0; i <=nCallbacks; i++){
			//if (strcmp(inByte, callbackTriggerKeys[i]) == 1){
			//	callbackFuncs[i]();
			//	return;
			//}
		}
		Serial.print(STR_ERROR_UNRECOGNISED);
		Serial.println(char(inByte));
	}
}

void SerialController::addCommand(char *key,  CallbackFunc _func, char *docstring){
	if (nCallbacks > MAX_SERIAL_CALLBACKS -1){
		Serial.println(STR_ERROR_TOO_MANY_CALLBACKS);
		return;
	}
	// TODO - build array of commands
	nCallbacks ++;
}

void SerialController::showCommands(){
	Serial.println(STR_MENU);
	for (int i=0; i <=nCallbacks; i++){
		Serial.print(callbackTriggerKeys[i]);
		Serial.print(STR_MENU_SPACER);
		Serial.println(callbackDocstrings[i]);
	}
	Serial.println();
}