#ifndef _SIMULATOR
#include "Arduino.h"
#endif
#include "RotaryStepper.h"

/* CONFIGURATION */

#define STEPS_PER_ROTATION 200

/* CONSTRUCTOR */

RotaryStepper::RotaryStepper() {
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

int RotaryStepper::goRelative(int nsteps) {
	// TODO
	abs_step += nsteps; // we won't do this here when the motor actually works
}

/* UTILITIES */

float RotaryStepper::stepToDegrees(int step){
	return step * (360.0/STEPS_PER_ROTATION);
}

float RotaryStepper::stepToRotations(int step){
	return float(step)/STEPS_PER_ROTATION;
}
