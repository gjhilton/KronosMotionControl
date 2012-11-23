//
//  main.cpp
//  KronosMotionControlSimulator

#include <iostream>
#include "RotaryStepper.h"
using namespace std;

#define STEPS_PER_ROTATION 200

RotaryStepper motor(STEPS_PER_ROTATION,8,9,10,11);

void testDrive(){
	cout
	<< "Testing drive\n"
	<< motor.getAbsoluteStep() << ","
	<< motor.getRelativeStep()
	;
	
	motor.drive(1);
}

int main(int argc, const char * argv[]) {

	testDrive();
    return 0;
}