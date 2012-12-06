#define _USE_SERIAL
#define _NOTIFY_SERIAL
#define MANUAL_DRIVE_NSTEPS 25
#define STEPS_PER_ROTATION 200

#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>

#include "RotaryStepper.h"
#include "configOSC.h"

/*	---------------------------------------------------- 
	OSC CONFIGURATION
	---------------------------------------------------- */

byte myMac[] = {0xDE,0xAD,0xBE,0xEE,0xAE,0xEB };
byte myIp[]  = {192,168,1,123};
int  serverPort  = 10000;

/*	---------------------------------------------------- 
	GLOBALS
	---------------------------------------------------- */

RotaryStepper motor(STEPS_PER_ROTATION,6,7,8,9);
OSCClient client;
OSCServer server;

/*	---------------------------------------------------- 
	COMMUNICATION MACRO
	---------------------------------------------------- */

#ifdef _NOTIFY_SERIAL
	#define NOTIFY(MSG) Serial.print(MSG);
#else
	#define NOTIFY(MSG) // noop
#endif

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
	if(server.aviableCheck()>0){
		// this pointless call is the only thing that makes the skanky osc library work, so don't remove it
	}
#if defined _USE_SERIAL
	serialLoop();
#endif
}

/*	---------------------------------------------------- 
	OSC
	---------------------------------------------------- */

void onOSCNotImplemented(OSCMessage *_mes = 0){
	NOTIFY("OSC: unimplemented");
}

void oscBegin(){
	Ethernet.begin(myMac ,myIp);
	serialSetcallback(&onOSCNotImplemented);
	server.begin(serverPort);
	server.addCallback(OSCADDR_FORWARD_STEP, 	&onOSCNotImplemented);
	server.addCallback(OSCADDR_REWIND_STEP, 	&onOSCNotImplemented);
	server.addCallback(OSCADDR_GO, 				&onOSCNotImplemented);	
	server.addCallback(OSCADDR_RESET, 			&onOSCNotImplemented);
	server.addCallback(OSCADDR_DEPLOY, 			&onOSCNotImplemented);
	server.addCallback(OSCADDR_UNDEPLOY, 		&onOSCNotImplemented);
	server.addCallback(OSCADDR_STUNT, 			&onOSCNotImplemented);
	server.addCallback(OSCADDR_GO_HOME, 		&onOSCNotImplemented);
	server.addCallback(OSCADDR_SET_HERE_HOME, 	&onOSCNotImplemented);
	server.addCallback(OSCADDR_GO_HOME_PLUS, 	&onOSCNotImplemented);
	server.addCallback(OSCADDR_GO_KF, 			&onOSCNotImplemented);
	server.addCallback(OSCADDR_SET_HERE_KF, 	&onOSCNotImplemented);
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
	serialPrintManualIncrement();
#endif
	motor.driveByRelative(MANUAL_DRIVE_NSTEPS);
}

void onRewind(){
#if defined _USE_SERIAL
	Serial.print("Going BACKWARD by ");
	serialPrintManualIncrement();
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

void serialSetcallback(void* func){
	
}


void serialBegin(){
	Serial.begin(9600);
	while (!Serial) {
		;
	}
	Serial.println("Send (h) for help");
	serialEstablishContact();
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

void serialEstablishContact() {
  while (Serial.available() <= 0) {
    Serial.println("ready");
    delay(1000);
  }
}

void serialPrintManualIncrement(){
	Serial.println(MANUAL_DRIVE_NSTEPS);
}

void serialPrintSpacer(){
	Serial.println("");
	Serial.println("+------------------------+");
	Serial.println("");	
}

void serialPrintStep(int step){
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
	serialPrintSpacer();
	Serial.println(" COMMANDS AVAILABLE:");
	Serial.println();
	Serial.println(" h -> help");
	Serial.println(" s -> show status");
	Serial.println(" z -> set current position as home");
	Serial.println(" 0 -> go to home position");
	Serial.print  (" +/= -> forward by ");
	serialPrintManualIncrement();
	Serial.print  (" -/_ -> reverse by ");
	serialPrintManualIncrement();
	Serial.println  (" ] -> forward by 1");
	Serial.println  (" [ -> backward by 1");
	serialPrintSpacer();
}

void onSerialStatus(){
	serialPrintSpacer();
	Serial.print("STATUS at ");
	Serial.print(millis() / 1000);
	Serial.println("s.");
	Serial.println();
	
	Serial.print("Absolute: ");
	serialPrintStep(motor.getAbsoluteStep());
	Serial.print("Relative: ");
	serialPrintStep(motor.getRelativeStep());
	Serial.print("Home: ");
	if (motor.homeSet()){
		Serial.println(motor.getHomePos());
	} else{
		Serial.println("not set");
	}
	
	serialPrintSpacer();
}

#endif