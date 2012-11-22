#define _USE_SERIAL_CONTROLS
#define MANUAL_DRIVE_NSTEPS 10

#include "RotaryStepper.h"

RotaryStepper motor;

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		;
	}
#if defined _USE_SERIAL_CONTROLS
	Serial.println("Send (h) for help");
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
			case 'z':
				onSetAtHome();
				break;
			case '+':
			case '=':
				onForward();
				break;
			case '-':
			case '_':
				onRewind();
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

/*	---------------------------------------------------- 
	COMMAND HANDLERS
	---------------------------------------------------- */

void onForward(){
	motor.goRelative(MANUAL_DRIVE_NSTEPS);
#if defined _USE_SERIAL_CONTROLS
	Serial.print("Going forward by ");
	printmanualincrement();
#endif
}

void onRewind(){
	motor.goRelative(-MANUAL_DRIVE_NSTEPS);
#if defined _USE_SERIAL_CONTROLS
	Serial.print("Going backward by ");
	printmanualincrement();
#endif
}

void onSetAtHome(){
	motor.setAtHome();
#if defined _USE_SERIAL_CONTROLS
	Serial.println("Setting home to current step");
	onSerialStatus();
#endif	
}

/*	---------------------------------------------------- 
	COMMAND HANDLERS (serial only)
	---------------------------------------------------- */

#if defined _USE_SERIAL_CONTROLS

void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println("ready");
    delay(1000);
  }
}

void printmanualincrement(){
	Serial.println(MANUAL_DRIVE_NSTEPS);
}

void printspacer(){
	Serial.println("");
	Serial.println("+------------------------+");
	Serial.println("");	
}

void printstep(int step){
	float d = motor.stepToDegrees(step);
	float r = motor.stepToRotations(step);
	Serial.print(step);
	Serial.print(" (");
	Serial.print(r);
	Serial.print(" rotations / ");
	Serial.print(d);
	Serial.print(" degrees)");
	Serial.println();
}

void onSerialHelp(){
	printspacer();
	Serial.println(" COMMANDS AVAILABLE:");
	Serial.println();
	Serial.println(" h -> help");
	Serial.println(" s -> show status");
	Serial.print  (" +/= -> forward by ");
	printmanualincrement();
	Serial.print  (" -/_ -> reverse by ");
	printmanualincrement();
	printspacer();
}

void onSerialStatus(){
	printspacer();
	Serial.print("STATUS at ");
	Serial.print(millis() / 1000);
	Serial.println("s.");
	Serial.println();
	
	Serial.print("Absolute: ");
	printstep(motor.getAbsoluteStep());
	Serial.print("Relative: ");
	printstep(motor.getRelativeStep());
	Serial.print("Home: ");
	if (motor.homeSet()){
		Serial.println(motor.getHomePos());
	} else{
		Serial.println("not set");
	}
	
	printspacer();
}

#endif