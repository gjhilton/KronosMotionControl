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
	
	cout << "QUART_OUT\n";
	interp(SINE_OUT);
	
}

int main(int argc, const char * argv[]) {
	//testDrive();
	//testHome();
    testInterpolation();
	
	
	return 0;
}