//
//  main.cpp
//  KronosMotionControlSimulator

#include <iostream>
#include <sstream>
#include "RotaryStepper.h"
using namespace std;

#define STEPS_PER_ROTATION 200

RotaryStepper motor(STEPS_PER_ROTATION,8,9,10,11);

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
	cout << "STATUS -> " << home() << " Absolute: " << motor.getAbsoluteStep() << " Relative: " << motor.getRelativeStep() << "\n";
}

void testDrive(){
	status();
	cout << "Testing drive\n";
	motor.drive(1);
}

int main(int argc, const char * argv[]) {

	testDrive();
    return 0;
}