// #define _NOTIFY_SERIAL
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

byte oscDestinationIP[]  = {192,168,1,4};
int oscDestinationPort = 12000;

/*	---------------------------------------------------- 
	GLOBALS
	---------------------------------------------------- */

RotaryStepper motor(STEPS_PER_ROTATION,6,7,8,9);
// SerialController serialport;
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
	// serialBegin();
}

void loop(){
	// this pointless call is all that makes the osc library work, so don't remove it
	if(server.aviableCheck()>0){}
	// serialport.loop();
	delay(50);
	//oscPrint();
	//delay(1000);
}

/*	---------------------------------------------------- 
	CONTROL
	---------------------------------------------------- */

void commandGo(int steps){
	String s = String("go -> ");
	s += steps;
	s += " steps";
	NOTIFY(s);
	motor.driveByRelative(steps);
}

void commandGoHome(){
	NOTIFY("go -> home");
	motor.driveHome();
}

void commandGoKey(int key){
	String s = String("go -> to position ");
	s += key;
	NOTIFY(s);
	motor.driveToKeyframe(key);
}

void commandSetHomeHere(){
	motor.setAtHome();
	String s = String("set -> home at ");
	s += motor.getHomePos();
	NOTIFY(s);
}

void commandSetKeyHere(int index){
	if (motor.homeSet()){
		motor.setKeyframeHere(index);
		String s = String("set -> key ");
		s += index;
		s += " at home +";
		s += motor.getKeyframeRelativeToHome(index);
		NOTIFY(s);
	} else {
		NOTIFY("couldnt set keyframe");
	}
}

void commandSetKeyValue(int index, int val){
	String s = String("set -> key ");
	s += index;
	s += " at ";
	s += (val);
	if (motor.setKeyframeRelativeToHome(index,val)){
		s+= " success";
	} else {
		s += " ERROR";
	}
	NOTIFY(s);
}

String commandGetPos(){
	String s = String("kronos position -> ");
	s += motor.getAbsoluteStep();
	s += " home";
	if (motor.homeSet()){
		s += "@";
		s += motor.getHomePos();
		s += "+";
		s += motor.getRelativeStep();
	} else {
		s += " NOT SET";
	}
	return s;
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

void onSerialSetKey1()		{commandSetKeyHere(1);}
void onSerialSetKey2()		{commandSetKeyHere(2);}
void onSerialSetKey3()		{commandSetKeyHere(3);}
void onSerialSetKey4()		{commandSetKeyHere(4);}
void onSerialSetKey5()		{commandSetKeyHere(5);}
void onSerialSetKey6()		{commandSetKeyHere(6);}

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

void onSerialGetPos()		{
	String s = commandGetPos();
	NOTIFY(s);
}

void onSerialGetKeys()		{
	String s = String("keys -> ");
	for (int k=1; k<7; k++){
		s += motor.getKeyframeRelativeToHome(k);
		s += " ";
	}
	NOTIFY(s);
}

void serialBegin(){
	/*
	serialport.begin();
	
	serialport.addCommand("0", &commandGoHome, 		"go home");
	serialport.addCommand("1", &onSerialGoKey1, 	"go to position 1");
	serialport.addCommand("2", &onSerialGoKey2, 	"go to position 2");
	serialport.addCommand("3", &onSerialGoKey3, 	"go to position 3");
	serialport.addCommand("4", &onSerialGoKey4, 	"go to position 4");
	serialport.addCommand("5", &onSerialGoKey5, 	"go to position 5");
	serialport.addCommand("6", &onSerialGoKey6, 	"go to position 6");
	
	serialport.addCommand("=", &commandSetHomeHere, "set home here");
	serialport.addCommand("!", &onSerialSetKey1, 	"set position 1 here");
	serialport.addCommand("@", &onSerialSetKey2, 	"set position 2 here");
	serialport.addCommand("£", &onSerialSetKey3, 	"set position 3 here");
	serialport.addCommand("$", &onSerialSetKey4, 	"set position 4 here");
	serialport.addCommand("%", &onSerialSetKey5, 	"set position 5 here");
	serialport.addCommand("^", &onSerialSetKey6, 	"set position 6 here");
	
	serialport.addCommand("q", &onSerialGoUp1, 		"up 1");
	serialport.addCommand("w", &onSerialGoUp10, 	"up 10");
	serialport.addCommand("e", &onSerialGoUp100, 	"up 100");
	serialport.addCommand("r", &onSerialGoUp200, 	"up 200");
	serialport.addCommand("t", &onSerialGoUp500, 	"up 500");
	
	serialport.addCommand("a", &onSerialGoDown1, 	"down 1");
	serialport.addCommand("s", &onSerialGoDown10, 	"down 10");
	serialport.addCommand("d", &onSerialGoDown100, 	"down 100");
	serialport.addCommand("f", &onSerialGoDown200, 	"down 200");
	serialport.addCommand("g", &onSerialGoDown500, 	"down 500");
	
	serialport.addCommand(" ", &onSerialGetPos, 	"get position");
	serialport.addCommand("-", &onSerialGetKeys, 	"get keyframes");
	serialport.addCommand("p", &onSerialOSCping, 	"ping osc");
	*/
}

/*	---------------------------------------------------- 
	OSC CONTROL FACADE
	---------------------------------------------------- */

void onOSCNotImplemented(OSCMessage *_mes){
	NOTIFY("OSC: unimplemented\n");
}

void onOSCgo(OSCMessage *_mes){
	int target = _mes->getArgInt32(0);
	String s = "Going by ";
	s += target;
	oscPrint(s);
	commandGo(target);
}

void onOSCkey(OSCMessage *_mes){
	int keyframe = _mes->getArgInt32(0);
	String s = "Received go to keyframe";
	s += _mes->getArgInt32(0);
	oscPrint(s);
	commandGoKey(keyframe);
}

void onOSChome(OSCMessage *_mes){
	String s = "Going to home";
	oscPrint(s);
	commandGoHome();
}

void onOSCsetHome(OSCMessage *_mes){
	commandSetHomeHere();
	String s = "Set home";
	oscPrint(s);
}

void onOSCrequestStatus(OSCMessage *_mes){
	String s = commandGetPos();
	oscPrint(s);
}

void onOSCset1(OSCMessage *_mes){commandSetKeyValue(1,_mes->getArgInt32(0));}
void onOSCset2(OSCMessage *_mes){commandSetKeyValue(2,_mes->getArgInt32(0));}
void onOSCset3(OSCMessage *_mes){commandSetKeyValue(3,_mes->getArgInt32(0));}
void onOSCset4(OSCMessage *_mes){commandSetKeyValue(4,_mes->getArgInt32(0));}
void onOSCset5(OSCMessage *_mes){commandSetKeyValue(5,_mes->getArgInt32(0));}
void onOSCset6(OSCMessage *_mes){commandSetKeyValue(6,_mes->getArgInt32(0));}

void oscBegin(){
	Ethernet.begin(myMac ,myIp);
	server.begin(oscListenPort);
	
	server.addCallback(OSC_ADDR_GO, &onOSCgo);
	server.addCallback(OSC_ADDR_GO_KEY, 	&onOSCkey);
	server.addCallback(OSC_ADDR_GO_HOME, 	&onOSChome);
	server.addCallback(OSC_ADDR_SET_KEY1, 	&onOSCset1);
	server.addCallback(OSC_ADDR_SET_KEY2, 	&onOSCset2);
	server.addCallback(OSC_ADDR_SET_KEY3, 	&onOSCset3);
	server.addCallback(OSC_ADDR_SET_KEY4, 	&onOSCset4);
	server.addCallback(OSC_ADDR_SET_KEY5, 	&onOSCset5);
	server.addCallback(OSC_ADDR_SET_KEY6, 	&onOSCset6);
	server.addCallback(OSC_ADDR_SET_HOME, 	&onOSCsetHome);
	server.addCallback(OSC_ADDR_REQUEST, 	&onOSCrequestStatus);

}

void oscPrint(String s){
  OSCMessage global_mes;
  global_mes.setAddress(oscDestinationIP,oscDestinationPort);
  global_mes.beginMessage(OSC_ADDR_REQUEST);
	char c[s.length()+1];
	s.toCharArray(c, s.length()+1);
  global_mes.addArgString(c);
  client.send(&global_mes);
}
