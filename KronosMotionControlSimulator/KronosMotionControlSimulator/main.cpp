//
//  main.cpp
//  KronosMotionControlSimulator

#include <iostream>
#include <sstream>
#include "RotaryStepper.h"
#include "interpolation.h"

using namespace std;

RotaryStepper motor(200,8,9,10,11);

string home(){
	stringstream sstr;
	sstr << "Home: ";
	if (motor.homeSet()){
		sstr << motor.getHomePos();
	} else{
		sstr << "(not set)";
	}
	return sstr.str();
}

void status(){
	cout << "STATUS @" << motor.millis() << "ms -> " << home() << " Absolute: " << motor.getAbsoluteStep() << " Relative: " << motor.getRelativeStep() << "\n";
}

void testHome(){
	cout << "\n\n***** TESTING GO HOME ****\n\n";
	status();
	motor.driveHome();
	motor.driveToAbsoluteTarget(0);
	motor.setAtHome();
	motor.driveHome();
	motor.driveToAbsoluteTarget(20);
	motor.setAtHome();
	motor.driveHome();
	motor.driveToAbsoluteTarget(-100);
	motor.setAtHome();
	motor.driveByRelative(321);
	motor.driveHome();
	status();
	if (motor.getRelativeStep() == 0 && motor.getAbsoluteStep() == -100 && motor.getHomePos() == -100){
		cout << "\n\ntest passed.\n";
	} else {
		cout << "\n\n!!!! ERROR !!!!\n";
	}
}
	
void testDrive(){
	cout << "\n\n**** TESTING DRIVE *****\n\n";
	status();
	motor.driveToAbsoluteTarget(200);
	motor.driveToAbsoluteTarget(-200);
	motor.driveByRelative(300);
	motor.driveByRelative(-100);
	status();
	if (motor.getRelativeStep() == 0 && motor.getAbsoluteStep() == 0){
		cout << "\n\ntest passed.\n";
	} else {
		cout << "\n\n!!!! ERROR !!!!\n";
	}
}

void interp(Interpolation kind = LINEAR){
	float b = 0;	// the initial value of the animation property
	float c = 10;	// the total change in the animation property
	float d = 10;	// the duration of the motion
	for (float t = 0; t<= d; t++){
		cout << t << "/" << d  << ": \t" << interpolate(t,b,c,d,kind) << "\n";
	}
	cout << "\n";
}

void testInterpolation(){
	
	cout << "Testing interpolation\n\nLINEAR\n";
	interp();
	
	cout << "QUAD\n";
	interp(QUAD);
	
	cout << "QUAD_IN\n";
	interp(QUAD_IN);
	
	cout << "QUAD_OUT\n";
	interp(QUAD_OUT);
	
	cout << "CIRCULAR\n";
	interp(CIRCULAR);
	
	cout << "CIRCULAR_IN\n";
	interp(CIRCULAR_IN);
	
	cout << "CIRCULAR_OUT\n";
	interp(CIRCULAR_OUT);
	
	cout << "QUART\n";
	interp(QUART);
	
	cout << "QUART_IN\n";
	interp(QUART_IN);
	
	cout << "QUART_OUT\n";
	interp(QUART_OUT);
	
	cout << "SINE\n";
	interp(SINE);
	
	cout << "SINE_IN\n";
	interp(SINE_IN);
	
	cout << "SINE_OUT\n";
	interp(SINE_OUT);
	
	cout << "EXPO\n";
	interp(EXPO);
	
	cout << "EXPO_IN\n";
	interp(EXPO_IN);
	
	cout << "EXPO_OUT\n";
	interp(EXPO_OUT);
	
}

void testKeyframes(){
	cout << "\n\n***** TESTING Keyframes ****\n\n";
	
	cout << "> keyframe shouldn't be set if home isn't set \n";
	bool expectedtofail = motor.setKeyframeHere(0);
	cout << "0 " << expectedtofail << "\n";
	cout << "\n";
	
	cout << "> set home at abs 200 \n";
	motor.driveToAbsoluteTarget(0);
	cout << "0 " << motor.getAbsoluteStep() << "\n";
	motor.driveToAbsoluteTarget(200);
	cout << "200 " << motor.getAbsoluteStep() << "\n";
	motor.setAtHome();
	cout << "0 " << motor.getRelativeStep() << "\n";
	cout << "\n";
	
	cout << "> go to abs 300 / home +100  and set keyframe 0  \n";
	motor.driveByRelative(100);
	cout << "300 " << motor.getAbsoluteStep() << "\n";
	motor.setKeyframeHere(0);
	cout << "100 " << motor.getKeyframeRelativeToHome(0) << "\n";
	cout << "300 " << motor.getKeyframeAbsolute(0) << "\n";
	cout << "\n";
	
	cout << "> go to abs 1 then try to return to keyframe  \n";
	motor.driveByRelative(-299);
	cout << "1 " << motor.getAbsoluteStep() << "\n";
	motor.driveToKeyframe(0);
	cout << "300 " << motor.getAbsoluteStep() << "\n";
	cout << "\n";
	
	cout << "> attempt to set invalid keyframe  \n";
	expectedtofail = motor.setKeyframeHere(1000);
	cout << "0 " << expectedtofail << "\n";
	cout << "\n";
	
	cout << "> attempt to set numeric keyframe, then go to it  \n";
	motor.setKeyframeRelativeToHome(1, 400);
	motor.driveToKeyframe(1);
	cout << "600 " << motor.getAbsoluteStep() << "\n";
	cout << "\n";
}

void testInterpolatedGo(){
	cout << "Testing interpolated go...\n";
	motor.driveToAbsoluteTargetEased(200);
	cout << "-> 200 = " << motor.getAbsoluteStep() << "\n";
	motor.driveToAbsoluteTargetEased(-137,337);
	cout << "-> -137 = " << motor.getAbsoluteStep() << "\n";
	motor.driveToAbsoluteTargetEased(-137,0);
	cout << "-> -137 = " << motor.getAbsoluteStep() << "\n";
	motor.driveToAbsoluteTargetEased(-138,1);
	cout << "-> -138 = " << motor.getAbsoluteStep() << "\n";
	motor.driveToAbsoluteTargetEased(0,0);
	cout << "-> 0 = " << motor.getAbsoluteStep() << "\n";
	cout << "------------------------- \n";
	cout << "(7 second wait) \n";
	motor.driveToAbsoluteTargetEased(1000,2000,SINE_IN);
	cout << "-> 1000 = " << motor.getAbsoluteStep() << "\n";
	motor.driveToAbsoluteTargetEased(100,1,SINE_IN);
	cout << "-> 100 = " << motor.getAbsoluteStep() << "\n";
	motor.driveToAbsoluteTargetEased(100,10000000000,SINE_IN);
	motor.driveToAbsoluteTargetEased(101,1,SINE_IN);
	cout << "-> 101 = " << motor.getAbsoluteStep() << "\n";
	cout << "...complete\n";
}

int main(int argc, const char * argv[]) {
	// testKeyframes();
	//testDrive(); // this will fail if testKFs is called first
	//testHome();
    // testInterpolation();
	testInterpolatedGo();
	
	return 0;
}