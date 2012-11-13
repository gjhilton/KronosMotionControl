#include "RotaryStepper.h"

#define DEFAULT_SPEED_RPM 1

/*	---------------------------------------------------- 
	CONSTRUCTOR
	---------------------------------------------------- */

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
	setSpeed(DEFAULT_SPEED_RPM);
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

/*	---------------------------------------------------- 
	MOTOR DRIVING
	---------------------------------------------------- */

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
	
	millis();
	/*
	
	int steps_to_move = 10;
	int direction =0 ;
	int step_number = 0;
  int steps_left = abs(steps_to_move);  // how many steps to take
  
  // determine direction based on whether steps_to_mode is + or -:
  if (steps_to_move > 0) {direction = 1;}
  if (steps_to_move < 0) {direction = 0;}
    
    
  // decrement the number of steps, moving one step each time:
  while(steps_left > 0) {
  // move only if the appropriate delay has passed:
  if (millis() - last_step_time >= step_delay) {
      // get the timeStamp of when you stepped:
      last_step_time = millis();
      // increment or decrement the step number,
      // depending on direction:
      if (direction == 1) {
        step_number++;
        if (step_number == steps_per_rotation) {
          step_number = 0;
        }
      } 
      else { 
        if (step_number == 0) {
          step_number = steps_per_rotation;
        }
        step_number--;
      }
      // decrement the steps left:
      steps_left--;
      // step the motor to step number 0, 1, 2, or 3:
      stepMotor(step_number % 4);
    }
  }
	 */
}

void RotaryStepper::setSpeed(long speedRPM){
	step_delay = 60L * 1000L / steps_per_rotation / speedRPM;
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
	cout << "RotaryStepper: " << s << "\n";
}
#endif