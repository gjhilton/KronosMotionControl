#include "RotaryStepper.h"

/*	---------------------------------------------------- 
	CONSTRUCTOR
	---------------------------------------------------- */

RotaryStepper::RotaryStepper(int number_of_steps_per_rotation, int pin_1, int pin_2, int pin_3, int pin_4) {
	abs_step = 0;
	home_is_set = false;
	home_offset_steps = 0;
	last_step_time = millis();
	nextStep = 0;
	
	steps_per_rotation = number_of_steps_per_rotation;
	motor_pin_1 = pin_1;
	motor_pin_2 = pin_2;
	motor_pin_3 = pin_3;
	motor_pin_4 = pin_4;
	
	initPins();

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
	KEYFRAMES
	---------------------------------------------------- */

bool RotaryStepper::setKeyframeRelativeToHome(int index, int value){
	if (index < MAX_N_KEYFRAMES){
		keyframes[index] = value;
		keyframes_set[index] = true;
		return true;
	}
	return false;
}

bool RotaryStepper::setKeyframeHere(int index){
	return homeSet() && setKeyframeRelativeToHome(index, getRelativeStep());
}

int RotaryStepper::getKeyframeAbsolute(int index){
	if (home_is_set) {
		return getKeyframeRelativeToHome(index) + home_offset_steps;
	}
	return 0; // hard to know a good value for an invalid keyframe
}

int RotaryStepper::getKeyframeRelativeToHome(int index){
	if ((index < MAX_N_KEYFRAMES) && (keyframes_set[index])){
		return keyframes[index];
	}
	return 0; // hard to know a good value for an invalid keyframe
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

void RotaryStepper::driveToKeyframe(int index){
	if ((home_is_set) && (index < MAX_N_KEYFRAMES) && (keyframes_set[index])){
		driveToAbsoluteTarget(getKeyframeAbsolute(index));
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

void RotaryStepper::driveToAbsoluteTargetEased(int abs_target, int total_additional_ms, Interpolation kind){
	long nextStepTime = 0;
	float nsteps = float(abs(abs_step - abs_target));
	float step = 1;
	float additional_ms = float(total_additional_ms);
	int lastextra=0;
	while(abs_step != abs_target) {
		if (millis() >= nextStepTime) {
			abs_step < abs_target ? oneStepForward() : oneStepBackward();
			int t = 0;
			if (total_additional_ms > 0){
				int extratime = interpolate(step, 0.0, additional_ms, nsteps, kind);
				t = extratime - lastextra;
				lastextra = extratime;
			}
			nextStepTime = last_step_time + step_delay + t;
			// cout << nextStepTime << "(" << t << ")\n";
			step++;
		}
	}
}

/*	---------------------------------------------------- 
	HARDWARE INTERFACE
	---------------------------------------------------- */

void RotaryStepper::initPins(){
#ifndef _SIMULATOR
	pinMode(motor_pin_1, OUTPUT);
	pinMode(motor_pin_2, OUTPUT);
	pinMode(motor_pin_3, OUTPUT);
	pinMode(motor_pin_4, OUTPUT);
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
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, LOW);
      break;
      case 1:    // 0110
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, HIGH);
      digitalWrite(motor_pin_4, LOW);
      break;
      case 2:    //0101
      digitalWrite(motor_pin_1, LOW);
      digitalWrite(motor_pin_2, HIGH);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, HIGH);
      break;
      case 3:    //1001
      digitalWrite(motor_pin_1, HIGH);
      digitalWrite(motor_pin_2, LOW);
      digitalWrite(motor_pin_3, LOW);
      digitalWrite(motor_pin_4, HIGH);
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
