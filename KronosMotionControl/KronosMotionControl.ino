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
	serialBegin();
}

void loop(){
	// this pointless call is all that makes the osc library work, so don't remove it
	if(server.aviableCheck()>0){}
	serialport.loop();
	delay(50);
}

/*	---------------------------------------------------- 
	CONTROL
	---------------------------------------------------- */

void commandGo(int steps){
	NOTIFY("Go -> ");
	NOTIFY(steps);
	NOTIFY("\n");
	// motor.driveByRelative(steps);
}

/*	---------------------------------------------------- 
	SERIAL CONTROL
	---------------------------------------------------- */

void onSerialNotImplemented(){
	NOTIFY("Not implemented");
}

void serialBegin(){
	serialport.begin();
	serialport.addCommand("b", &onSerialNotImplemented, "test function");
}

/*	---------------------------------------------------- 
	OSC CONTROL
	---------------------------------------------------- */

void onOSCNotImplemented(OSCMessage *_mes){
	NOTIFY("OSC: unimplemented\n");
}

void onOSCgo(OSCMessage *_mes){
	commandGo(_mes->getArgInt32(0));
}

void oscBegin(){
	Ethernet.begin(myMac ,myIp);
	server.begin(oscListenPort);
	server.addCallback(OSC_ADDR_GO, &onOSCgo);
	server.addCallback(OSC_ADDR_GO_KEY, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_GO_HOME, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY1, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY2, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY3, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY4, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY5, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY6, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_HOME, 	&onOSCNotImplemented);
}


