#define _NOTIFY_SERIAL
#define MANUAL_DRIVE_NSTEPS 25
#define STEPS_PER_ROTATION 200

#include <SPI.h>
#include <Ethernet.h>
#include <ArdOSC.h>

#include "SerialController.h"
#include "RotaryStepper.h"
#include "configOSC.h"

/*	---------------------------------------------------- 
	OSC CONFIGURATION
	---------------------------------------------------- */

byte myMac[] = {0xDE,0xAD,0xBE,0xEE,0xAE,0xEB };
byte myIp[]  = {192,168,1,123};
int  oscListenPort  = 10000;

byte oscDestinationIP[]  = {192,168,1,124};
int oscDestinationPort = 12000;

/*	---------------------------------------------------- 
	GLOBALS
	---------------------------------------------------- */

RotaryStepper motor(STEPS_PER_ROTATION,6,7,8,9);
SerialController serialport;
OSCClient client;
OSCServer server;

/*	---------------------------------------------------- 
	COMMUNICATION MACRO
	---------------------------------------------------- */

#ifdef _NOTIFY_SERIAL
	#define NOTIFY(MSG) Serial.println(MSG);
#else
	#define NOTIFY(MSG) // noop
#endif

/*	---------------------------------------------------- 
	ARDUINO LIFECYCLE
	---------------------------------------------------- */

void setup() {
	oscBegin();
	serialBegin();
}

void loop(){
	// this pointless call is all that makes the osc library work, so don't remove it
	if(server.aviableCheck()>0){}
	serialport.loop();
	delay(50);
}

/*	---------------------------------------------------- 
	OSC
	---------------------------------------------------- */

void onOSCNotImplemented(OSCMessage *_mes = 0){
	NOTIFY("OSC: unimplemented");
}

void oscBegin(){
	Ethernet.begin(myMac ,myIp);
	server.begin(oscListenPort);
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
	NOTIFY("Going forward by 1");
	motor.oneStepForward();
}

void onBackwardOne(){
	NOTIFY("Going BACKWARD by 1");
	motor.oneStepBackward();
}

void onForward(){
	NOTIFY("Going forward");
	motor.driveByRelative(MANUAL_DRIVE_NSTEPS);
}

void onRewind(){
	NOTIFY("Going BACKWARD");
	motor.driveByRelative(-MANUAL_DRIVE_NSTEPS);
}

void onSetAtHome(){
	motor.setAtHome();

	NOTIFY("Set home to current step");
}

void onGoHome(){
	if (motor.homeSet()){
		NOTIFY("Going home");
		motor.driveHome();
	} else {
		NOTIFY("Can't go home because it hasn't been set");
	}
}

/*	---------------------------------------------------- 
	SERIAL
	---------------------------------------------------- */

void onSerialNotImplemented(){
	NOTIFY("Not implemented");
}

void serialBegin(){
	serialport.begin();
	serialport.addCommand("b", &onSerialNotImplemented, "test function");
}


