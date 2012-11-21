#define _USE_SERIAL_CONTROLS

#include "RotaryStepper.h"

RotaryStepper motor;

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		;
	}
#if defined _USE_SERIAL_CONTROLS
	Serial.println("Send h for help");
	establishContact();
#endif
}

void loop(){
#if defined _USE_SERIAL_CONTROLS
	if (Serial.available() > 0) {
		int inByte = Serial.read();
		switch (inByte){
			case 'h':
				onSerialHelp();
				break;
			case 's':
				onSerialStatus();
				break;
			case 10:
			case 13:
				Serial.println("Please turn off sending line endings");
				break;
			default:
				Serial.print("Sorry, I dont understand key ");
				Serial.println(inByte);
				break;
		}
		Serial.println();
	}
#endif
}

#if defined _USE_SERIAL_CONTROLS

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("ready");
    delay(1000);
  }
}

void printspacer(){
	Serial.println("");
	Serial.println("+------------------------+");
	Serial.println("");	
}

void onSerialHelp(){
	printspacer();
	Serial.println(" COMMANDS AVAILABLE:");
	Serial.println();
	Serial.println(" h - help");
	Serial.println(" s - show status");
	printspacer();
}

void onSerialStatus(){
	printspacer();
	Serial.print("STATUS at ");
	unsigned long t = millis() / 1000;
	Serial.print(t);
	Serial.println("s.");
	Serial.println();
	Serial.print("Absolute step: ");
	int n = motor.getCurrentAbsoluteStep();
	Serial.println(n);
	printspacer();
}

#endif