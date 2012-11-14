#include "RotaryStepper.h"

#define DEFAULT_SPEED_RPM 1

/*	---------------------------------------------------- 
	CONSTRUCTOR
	---------------------------------------------------- */

RotaryStepper::RotaryStepper(int number_of_steps_per_rotation, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4) {
	abs_step = 0;
	home_is_set = false;
	home_offset_steps = 0;
	last_step_time = millis();
	nextStep = 0;
	
	steps_per_rotation = number_of_steps_per_rotation;
	pin_1 = motor_pin_1;
	pin_2 = motor_pin_2;
	pin_3 = motor_pin_3;
	pin_4 = motor_pin_4;
	
	initPins();
	// setSpeed(DEFAULT_SPEED_RPM);
	step_delay = 5;
}

/*	---------------------------------------------------- 
	GETTERS
	---------------------------------------------------- */

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

/*	---------------------------------------------------- 
	SETTERS
	---------------------------------------------------- */

void RotaryStepper::setHome(int step){
	home_offset_steps = step;
	home_is_set = true;
}

void RotaryStepper::setAtHome(){
	setHome(abs_step);
}

void RotaryStepper::setSpeed(long speedRPM){
	// FIXME
	// step_delay = 60L * 1000L / steps_per_rotation / speedRPM;
}

/*	---------------------------------------------------- 
	MOTOR DRIVING
	---------------------------------------------------- */

void RotaryStepper::driveByRelative(int nsteps) {
	driveToAbsoluteTarget(abs_step + nsteps);
}

void RotaryStepper::driveHome() {
	if (home_is_set){
		driveToAbsoluteTarget(getHomePos());
	}
}

void RotaryStepper::driveToAbsoluteTarget(int abs_target){

	// forward
	if (abs_step < abs_target ) {
		while(abs_step < abs_target) {
			if (millis() - last_step_time >= step_delay) {
				oneStepForward();
			}
		}
	}

	// reverse
	if (abs_step > abs_target ) {
		while(abs_step > abs_target) {
			if (millis() - last_step_time >= step_delay) {
				oneStepBackward();
			}
		}
	}
}

/*	---------------------------------------------------- 
	HARDWARE INTERFACE
	---------------------------------------------------- */

void RotaryStepper::initPins(){
#ifndef _SIMULATOR
	pinMode(pin_1, OUTPUT);
	pinMode(pin_2, OUTPUT);
	pinMode(pin_3, OUTPUT);
	pinMode(pin_4, OUTPUT);
#endif
}

void RotaryStepper::oneStepForward(){
	abs_step ++;
	nextStep ++;
	stepMotor(); // i worry this is off by one on startup
}
void RotaryStepper::oneStepBackward(){
	abs_step --;
	nextStep --;
	stepMotor();
}

void RotaryStepper::stepMotor(){
	if (nextStep == 4) nextStep = 0;
	if (nextStep == -1) nextStep = 3;
	last_step_time = millis();
	
#ifndef _SIMULATOR
	switch (nextStep) {
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
	report("abs ", abs_step);
	switch (nextStep) {
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


/*	---------------------------------------------------- 
	UTILITIES
	---------------------------------------------------- */

float RotaryStepper::stepToDegrees(int step){
	return step * (360.0/steps_per_rotation);
}

float RotaryStepper::stepToRotations(int step){
	return float(step)/steps_per_rotation;
}

#ifdef _SIMULATOR
void RotaryStepper::report(string s){
	// cout << "RotaryStepper: " << s << "\n";
}

void RotaryStepper::report(string varname, int i){
	// cout << "RotaryStepper: " << varname <<":" << i << "\n";
}

long RotaryStepper::millis(){
	return clock()/(CLOCKS_PER_SEC/1000);
}

#endif