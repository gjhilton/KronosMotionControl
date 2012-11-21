#ifndef _SIMULATOR
#include "Arduino.h"
#endif

#include "RotaryStepper.h"

RotaryStepper::RotaryStepper() {
	current_step = 401;
	steps_per_rotation = 200;
}

/* GETTERS */

int RotaryStepper::getCurrentAbsoluteStep() {
	return current_step;
}

float RotaryStepper::getCurrentAbsoluteDegrees() {
	return stepToDegrees(current_step);
}

int RotaryStepper::getCurrentStep() {
	return current_step % steps_per_rotation;
}

int RotaryStepper::getCurrentRotation() {
	return current_step / steps_per_rotation;
}

/* UTILITIES */

float RotaryStepper::stepToDegrees(int step){
	return current_step * (360.0/steps_per_rotation);
}
