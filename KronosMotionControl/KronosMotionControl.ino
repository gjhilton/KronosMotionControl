#define _USE_SERIAL
#define MANUAL_DRIVE_NSTEPS 10
#define STEPS_PER_ROTATION 200

#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>
#include "RotaryStepper.h"

/*	---------------------------------------------------- 
	CONFIGURATION
	---------------------------------------------------- */

byte myMac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED };
byte myIp[]  = {192,168,0,177};
int  serverPort  = 10000;

/*	---------------------------------------------------- 
	GLOBALS
	---------------------------------------------------- */

RotaryStepper motor(STEPS_PER_ROTATION,8,9,10,11);
OSCServer server;

/*	---------------------------------------------------- 
	ARDUINO LIFECYCLE
	---------------------------------------------------- */

void setup() {
	oscBegin();
#if defined _USE_SERIAL
	serialBegin();
#endif
}

void loop(){
#if defined _USE_SERIAL
	serialLoop();
#endif
}

/*	---------------------------------------------------- 
	OSC
	---------------------------------------------------- */

void oscBegin(){
	Ethernet.begin(myMac ,myIp);
	server.begin(serverPort);
	server.addCallback("/ard/fwd",&onOSCForward);
}

void onOSCForward(OSCMessage *_mes){
	onForward();
}

/*	---------------------------------------------------- 
	COMMAND HANDLERS
	---------------------------------------------------- */

void onForward(){
	motor.goRelative(MANUAL_DRIVE_NSTEPS);
#if defined _USE_SERIAL
	Serial.print("Going forward by ");
	printmanualincrement();
#endif
}

void onRewind(){
	motor.goRelative(-MANUAL_DRIVE_NSTEPS);
#if defined _USE_SERIAL
	Serial.print("Going backward by ");
	printmanualincrement();
#endif
}

void onSetAtHome(){
	motor.setAtHome();
#if defined _USE_SERIAL
	Serial.println("Setting home to current step");
	onSerialStatus();
#endif	
}

void onGoHome(){
	motor.goHome();
#if defined _USE_SERIAL
	if (motor.homeSet()){
		Serial.println("Going home");
		onSerialStatus();
	} else {
		Serial.println("Can't go home because it hasn't been set");
	}
#endif	
}

/*	---------------------------------------------------- 
	SERIAL
	---------------------------------------------------- */

#if defined _USE_SERIAL
void serialBegin(){
	Serial.begin(9600);
	while (!Serial) {
		;
	}
	Serial.println("Send (h) for help");
	establishContact();
}

void serialLoop(){
	if (Serial.available() > 0) {
		int inByte = Serial.read();
		switch (inByte){
			case 'h':
				onSerialHelp();
				break;
			case 's':
				onSerialStatus();
				break;
			case '0':
				onGoHome();
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
}

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
	Serial.println(" z -> set current position as home");
	Serial.println(" 0 -> go to home position");
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