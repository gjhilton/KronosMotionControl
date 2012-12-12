#include "SerialController.h"
#include <string.h>

#define STR_ERROR_LINE_ENDING			"Please turn off sending line endings"
#define STR_ERROR_TOO_MANY_CALLBACKS 	"Error"
#define STR_ERROR_UNRECOGNISED			"Unrecognised command: "
#define STR_MENU						"\nAVAILABLE COMMANDS\n------------------\n"
#define STR_MENU_SPACER					" -> "
#define STR_READY						"Send h for help"
#define STR_WAIT						"..."

SerialController::SerialController(int baud){
	baudrate = baud;
	nCallbacks = 0;
}

void SerialController::begin(){
	Serial.begin(baudrate);
	while (!Serial) {
		;
	}
	Serial.println(STR_READY);
	while (Serial.available() <= 0) {
		Serial.println(STR_WAIT);
		delay(1000); // ie 1 second
	}
}

void SerialController::loop(){
	if (Serial.available() > 0) {
		int inByte = Serial.read();
		
		// complain if we're being sent line endings
		if (inByte == 10 || inByte == 13){
			Serial.println(STR_ERROR_LINE_ENDING);
			return;
		}
		
		// show help table
		if (inByte == 104 || inByte == 72){ // ie "h" or "H" )
			showCommands();
			return;
		}
		
		// execute command
		for (int i=0; i <=nCallbacks; i++){
			if (inByte == int(callbackTriggerKeys[i])){
				callbackFuncs[i]();
				return;
			}
		}
		
		// fail
		Serial.print(STR_ERROR_UNRECOGNISED);
		Serial.print(char(inByte));
		Serial.print(" [");
		Serial.print(inByte);
		Serial.println("]");
	}
}

void SerialController::addCommand(char *key,  CallbackFunc _func, char *docstring){
	if (nCallbacks > MAX_SERIAL_CALLBACKS -1){
		Serial.println(STR_ERROR_TOO_MANY_CALLBACKS);
		return;
	}
	callbackTriggerKeys[nCallbacks] = *key;
	callbackFuncs[nCallbacks] = _func;
	callbackDocstrings[nCallbacks] = docstring;
	nCallbacks ++;
}

void SerialController::showCommands(){
	Serial.println(STR_MENU);
	for (int i=0; i < nCallbacks; i++){
		Serial.print(callbackTriggerKeys[i]);
		Serial.print(STR_MENU_SPACER);
		Serial.println(callbackDocstrings[i]);
	}
	Serial.println();
}