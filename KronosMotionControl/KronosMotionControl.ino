#define _USE_SERIAL
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
	// serialport.loop();
#endif
	serialport.loop();
	delay(100);
}

/*	---------------------------------------------------- 
	OSC
	---------------------------------------------------- */

void OSCNotify(){
	OSCMessage m;
	m.setAddress(oscDestinationIP,oscDestinationPort);
	m.beginMessage("/kronos/notify/absolute");
	m.addArgInt32(motor.getAbsoluteStep());
	client.send(&m);
	m.flush();
}

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
	// serialPrintManualIncrement();
#endif
	motor.driveByRelative(MANUAL_DRIVE_NSTEPS);
}

void onRewind(){
#if defined _USE_SERIAL
	Serial.print("Going BACKWARD by ");
	// serialPrintManualIncrement();
#endif
	motor.driveByRelative(-MANUAL_DRIVE_NSTEPS);
}

void onSetAtHome(){
	motor.setAtHome();
#if defined _USE_SERIAL
	Serial.println("Set home to current step");
	// onSerialStatus();
#endif	
}

void onGoHome(){
#if defined _USE_SERIAL
	if (motor.homeSet()){
		Serial.println("Going home");
		// onSerialStatus();
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

void onSerialNotImplemented(){
	Serial.println("Not implemented");
}

void serialBegin(){
	serialport.begin();
	serialport.addCommand("b", &onSerialNotImplemented, "test function");
}

#endif
