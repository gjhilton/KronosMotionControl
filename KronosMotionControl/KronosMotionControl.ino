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
	NOTIFY("go -> ");
	NOTIFY(steps);
	NOTIFY(" steps\n");
	// motor.driveByRelative(steps);
}

void commandGoHome(){
	NOTIFY("go -> home");
	// motor.driveHome();
}

void commandGoKey(int key){
	NOTIFY("go -> to position ");
	NOTIFY(key);
	NOTIFY("\n");
	// motor.driveToKeyframe(key);
}

void commandSetHomeHere(){
	motor.setAtHome();
	NOTIFY("set -> home at ");
	NOTIFY(motor.getHomePos());
	NOTIFY("\n");
}

/*	---------------------------------------------------- 
	SERIAL CONTROL FACADE
	---------------------------------------------------- */

void onSerialGoKey1()		{commandGoKey(1);}
void onSerialGoKey2()		{commandGoKey(2);}
void onSerialGoKey3()		{commandGoKey(3);}
void onSerialGoKey4()		{commandGoKey(4);}
void onSerialGoKey5()		{commandGoKey(5);}
void onSerialGoKey6()		{commandGoKey(6);}

void onSerialGoUp1()		{commandGo(-1);}
void onSerialGoUp10()		{commandGo(-10);}
void onSerialGoUp100()		{commandGo(-100);}
void onSerialGoUp200()		{commandGo(-200);}
void onSerialGoUp500()		{commandGo(-500);}

void onSerialGoDown1()		{commandGo(1);}
void onSerialGoDown10()		{commandGo(10);}
void onSerialGoDown100()	{commandGo(100);}
void onSerialGoDown200()	{commandGo(200);}
void onSerialGoDown500()	{commandGo(500);}

void onSerialStatus()		{
	NOTIFY("/n");
	// TODO
}

void serialBegin(){
	serialport.begin();

	serialport.addCommand("1", &onSerialGoKey1, 	"go to position 1");
	serialport.addCommand("2", &onSerialGoKey2, 	"go to position 2");
	serialport.addCommand("3", &onSerialGoKey3, 	"go to position 3");
	serialport.addCommand("4", &onSerialGoKey4, 	"go to position 4");
	serialport.addCommand("5", &onSerialGoKey5, 	"go to position 5");
	serialport.addCommand("6", &onSerialGoKey6, 	"go to position 6");
	
	serialport.addCommand("q", &onSerialGoDown1, 	"up 1");
	serialport.addCommand("w", &onSerialGoDown10, 	"up 10");
	serialport.addCommand("e", &onSerialGoDown100, 	"up 100");
	serialport.addCommand("r", &onSerialGoDown200, 	"up 200");
	serialport.addCommand("t", &onSerialGoDown500, 	"up 500");
	
	serialport.addCommand("a", &onSerialGoDown1, 	"down 1");
	serialport.addCommand("s", &onSerialGoDown10, 	"down 10");
	serialport.addCommand("d", &onSerialGoDown100, 	"down 100");
	serialport.addCommand("f", &onSerialGoDown200, 	"down 200");
	serialport.addCommand("g", &onSerialGoDown500, 	"down 500");
	
	serialport.addCommand("0", &commandGoHome, 		"go home");
	serialport.addCommand("=", &commandSetHomeHere, "set home here");
	
	serialport.addCommand(" ", &onSerialStatus, 	"get status");
}

/*	---------------------------------------------------- 
	OSC CONTROL FACADE
	---------------------------------------------------- */

void onOSCNotImplemented(OSCMessage *_mes){
	NOTIFY("OSC: unimplemented\n");
}

void onOSCgo(OSCMessage *_mes){
	commandGo(_mes->getArgInt32(0));
}

void onOSCkey(OSCMessage *_mes){
	commandGoKey(_mes->getArgInt32(0));
}

void onOSChome(OSCMessage *_mes){
	commandGoHome();
}

void onOSCsetHome(OSCMessage *_mes){
	commandSetHomeHere();
}

void oscBegin(){
	Ethernet.begin(myMac ,myIp);
	server.begin(oscListenPort);
	server.addCallback(OSC_ADDR_GO, &onOSCgo);
	server.addCallback(OSC_ADDR_GO_KEY, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_GO_HOME, 	&onOSCkey);
	server.addCallback(OSC_ADDR_SET_KEY1, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY2, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY3, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY4, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY5, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_KEY6, 	&onOSCNotImplemented);
	server.addCallback(OSC_ADDR_SET_HOME, 	&onOSCsetHome);
}


