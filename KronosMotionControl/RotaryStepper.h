#ifndef __KronosMotionControlSimulator__RotaryStepper__
#define __KronosMotionControlSimulator__RotaryStepper__

#ifdef _SIMULATOR
	#include <string>
	#include <iostream>
	#include <ctime>
	using namespace std;
#else
	#include "Arduino.h"
#endif

class RotaryStepper{
public:
	
    RotaryStepper(int number_of_steps_per_rotation, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);
	
	int getAbsoluteStep();
	int getRelativeStep();
	int getHomePos();
	bool homeSet();
	
	void setHome(int step);
	void setAtHome();
	void setSpeed(long speedRPM);
	
	void oneStepForward();
	void oneStepBackward();
	
	void driveHome();
	void driveByRelative(int nsteps);
	void driveToAbsoluteTarget(int abs_target);
	
	float stepToDegrees(int step);
	float stepToRotations(int step);

#ifdef _SIMULATOR
	void report(string s);
	// void report(string varname, int i);
	long millis();
#endif
	
protected:
	
private:
	
	int abs_step;
	int home_offset_steps;
	long last_step_time;
	int nextStep;
	int pin_1,pin_2,pin_3,pin_4;
	int steps_per_rotation;
	bool home_is_set;
	unsigned long step_delay;    // delay between steps, in ms, based on speed
	
	
	void initPins();
	void stepMotor();
};

#endif