#include "RotaryStepper.h"

/* CONSTRUCTOR */

RotaryStepper::RotaryStepper(int number_of_steps_per_rotation, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4) {
	abs_step = 0;
	home_is_set = false;
	home_offset_steps = 0;
	
	steps_per_rotation = number_of_steps_per_rotation;
	pin_1 = motor_pin_1;
	pin_2 = motor_pin_2;
	pin_3 = motor_pin_3;
	pin_4 = motor_pin_4;
	
	initPins();
}

/* GETTERS */

int RotaryStepper::getAbsoluteStep() {
	return abs_step; // steps relative to motor position when powered up
}

int RotaryStepper::getRelativeStep() {
	return abs_step - home_offset_steps; // steps relative to home position
}

int RotaryStepper::getHomePos() {
	return home_offset_steps; // steps relative to home position
}

bool RotaryStepper::homeSet() {
	return home_is_set;
}

/* SETTERS */

void RotaryStepper::setHome(int step){
	home_offset_steps = step;
	home_is_set = true;
}

void RotaryStepper::setAtHome(){
	setHome(abs_step);
}

/* MOTOR DRIVING */

void RotaryStepper::goRelative(int nsteps) {
	// TODO
	abs_step += nsteps; // we won't do this here when the motor actually works
}

void RotaryStepper::goHome() {
	// TODO
	if (home_is_set){
		abs_step = home_offset_steps; // we won't do this here when the motor actually works
	}
}

void RotaryStepper::drive(int target){
	stepMotor(0);
	stepMotor(1);
	stepMotor(2);
	stepMotor(3);
}

/* HARDWARE INTERFACE */

void RotaryStepper::initPins(){
#ifndef _SIMULATOR
	pinMode(pin_1, OUTPUT);
	pinMode(pin_2, OUTPUT);
	pinMode(pin_3, OUTPUT);
	pinMode(pin_4, OUTPUT);
#endif
}

void RotaryStepper::stepMotor(int thisStep){
#ifndef _SIMULATOR
	switch (thisStep) {
		case 0:    // 1010
			digitalWrite(pin_1, HIGH);
			digitalWrite(pin_2, LOW);
			digitalWrite(pin_3, HIGH);
			digitalWrite(pin_4, LOW);
			break;
		case 1:    // 0110
			digitalWrite(pin_1, LOW);
			digitalWrite(pin_2, HIGH);
			digitalWrite(pin_3, HIGH);
			digitalWrite(pin_4, LOW);
			break;
		case 2:    //0101
			digitalWrite(pin_1, LOW);
			digitalWrite(pin_2, HIGH);
			digitalWrite(pin_3, LOW);
			digitalWrite(pin_4, HIGH);
			break;
		case 3:    //1001
			digitalWrite(pin_1, HIGH);
			digitalWrite(pin_2, LOW);
			digitalWrite(pin_3, LOW);
			digitalWrite(pin_4, HIGH);
			break;
	}
#else
	switch (thisStep) {
		case 0:
			report("step 0");
			break;
		case 1:
			report("step 1");
			break;
		case 2:
			report("step 2");
			break;
		case 3:
			report("step 3");
			break;
	}
#endif
}


/* UTILITIES */

float RotaryStepper::stepToDegrees(int step){
	return step * (360.0/steps_per_rotation);
}

float RotaryStepper::stepToRotations(int step){
	return float(step)/steps_per_rotation;
}

#ifdef _SIMULATOR
void RotaryStepper::report(string s){
	cout << "RotaryStepper: " << s << "\n";
}
#endif