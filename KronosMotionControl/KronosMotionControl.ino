#define _USE_SERIAL
#define MANUAL_DRIVE_NSTEPS 50
#define STEPS_PER_ROTATION 200

#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>

#include "RotaryStepper.h"
#include "configOSC.h"

/*	---------------------------------------------------- 
	OSC CONFIGURATION
	---------------------------------------------------- */

byte myMac[] = {0xDE,0xAD,0xBE,0xEF,0xFE,0xED };
byte myIp[]  = {192,168,1,177};
int  serverPort  = 10000;

/*	---------------------------------------------------- 
	GLOBALS
	---------------------------------------------------- */

RotaryStepper motor(STEPS_PER_ROTATION,6,7,8,9);
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
	server.addCallback(OSC_ADDR_FORWARD,&onOSCForward);
	server.addCallback(OSC_ADDR_REWIND,&onOSCRewind);
	server.addCallback(OSC_ADDR_SET_HOME,&onOSCSetHome);
	server.addCallback(OSC_ADDR_HOME,&onOSCHome);
}

void onOSCForward(OSCMessage *_mes){
	onForward();
}

void onOSCRewind(OSCMessage *_mes){
	onRewind();
}

void onOSCSetHome(OSCMessage *_mes){
	onSetAtHome();
}

void onOSCHome(OSCMessage *_mes){
	onGoHome();
}

/*	---------------------------------------------------- 
	COMMAND HANDLERS
	---------------------------------------------------- */

void onForwardOne(){
#if defined _USE_SERIAL
	Serial.print("Going forward by 1");
#endif
	motor.oneStepForward();
}

void onBackwardOne(){
#if defined _USE_SERIAL
	Serial.print("Going BACKWARD by 1");
#endif
	motor.oneStepBackward();
}

void onForward(){
#if defined _USE_SERIAL
	Serial.print("Going forward by ");
	printmanualincrement();
#endif
	motor.driveByRelative(MANUAL_DRIVE_NSTEPS);
}

void onRewind(){
#if defined _USE_SERIAL
	Serial.print("Going BACKWARD by ");
	printmanualincrement();
#endif
	motor.driveByRelative(-MANUAL_DRIVE_NSTEPS);
}

void onSetAtHome(){
	motor.setAtHome();
#if defined _USE_SERIAL
	Serial.println("Set home to current step");
	onSerialStatus();
#endif	
}

void onGoHome(){
#if defined _USE_SERIAL
	if (motor.homeSet()){
		Serial.println("Going home");
		onSerialStatus();
	} else {
		Serial.println("Can't go home because it hasn't been set");
	}
#endif	
	motor.driveHome();
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
			case '[':
				onBackwardOne();
				break;
			case ']':
				onForwardOne();
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
	Serial.println  (" ] -> forward by 1");
	Serial.println  (" [ -> backward by 1");
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