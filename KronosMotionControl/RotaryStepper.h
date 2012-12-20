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

#include "interpolation.h"

#define MAX_N_KEYFRAMES 7
#define EASE_TIME 18000
#define DEFAULT_SPEED_RPM 1

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
	void driveToAbsoluteTargetEased(int abs_target, int total_additional_ms=0, Interpolation kind = LINEAR);
	void driveToKeyframe(int index);
	void driveToKeyframeEased(int index);
	
	float stepToDegrees(int step);
	float stepToRotations(int step);
	
	bool setKeyframeRelativeToHome(int index, int value);
	bool setKeyframeHere(int index);
	int getKeyframeAbsolute(int index);
	int getKeyframeRelativeToHome(int index);
	
#ifdef _SIMULATOR
	void report(string s);
	void report(string varname, int i);
	long millis();
#endif
	
protected:
	
	void initPins();
	void stepMotor();
	
private:
	
	int abs_step;
	int home_offset_steps;
	long last_step_time;
	int nextStep;
	int motor_pin_1;
	int motor_pin_2;
	int motor_pin_3;
	int motor_pin_4;
	int steps_per_rotation;
	bool home_is_set;
	unsigned long step_delay;    // delay between steps, in ms, based on speed
	
	int keyframes[MAX_N_KEYFRAMES];
	bool keyframes_set[MAX_N_KEYFRAMES];

};

#endif