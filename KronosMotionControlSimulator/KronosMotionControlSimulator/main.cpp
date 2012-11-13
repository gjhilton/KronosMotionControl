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

void testDrive(){
	status();
	// motor.setSpeed();
	motor.drive(200);
	status();
}

int main(int argc, const char * argv[]) {
	testDrive();
    return 0;
}