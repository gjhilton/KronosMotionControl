//
//  main.cpp
//  KronosMotionControlSimulator

#include <iostream>
#include "RotaryStepper.h"

#define STEPS_PER_ROTATION 200

RotaryStepper motor(STEPS_PER_ROTATION,8,9,10,11);

void testDrive(){
	std::cout
	<< "Testing drive\n"
	<< motor.getAbsoluteStep() << ","
	<< motor.getRelativeStep()
	;
}

int main(int argc, const char * argv[]) {

	testDrive();
    return 0;
}