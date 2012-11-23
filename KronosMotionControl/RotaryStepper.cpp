#ifndef _SIMULATOR
#include "Arduino.h"
#endif
#include "RotaryStepper.h"

/* CONSTRUCTOR */

RotaryStepper::RotaryStepper(int number_of_steps_per_rotation, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4) {
	steps_per_rotation = number_of_steps_per_rotation;
	abs_step = 0;
	home_is_set = false;
	home_offset_steps = 0;
	
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
	
}

/* UTILITIES */

float RotaryStepper::stepToDegrees(int step){
	return step * (360.0/steps_per_rotation);
}

float RotaryStepper::stepToRotations(int step){
	return float(step)/steps_per_rotation;
}
