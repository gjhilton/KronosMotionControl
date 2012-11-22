//
//  main.cpp
//  KronosMotionControlSimulator
//
//  Created by g j hilton on 20/11/2012.
//  Copyright (c) 2012 hltn co. All rights reserved.
//

#include <iostream>
#include "RotaryStepper.h"

RotaryStepper motor;

int main(int argc, const char * argv[])
{

	// insert code here...
	std::cout
	<< "Hello, World!\n"
	<< motor.getAbsoluteStep() << ","
	<< motor.getRelativeStep()
	;
    return 0;
}

