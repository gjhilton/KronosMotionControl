//
//  main.cpp
//  KronosMotionControlSimulator

#include <iostream>
#include <sstream>
#include "RotaryStepper.h"
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
	motor.driveToAbsoluteTarget(20);
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

int main(int argc, const char * argv[]) {
	testDrive();
	testHome();
    return 0;
}