#ifndef __KronosMotionControlSimulator__Keyframe__
#define __KronosMotionControlSimulator__Keyframe__

#include "RotaryStepper.h"

class RotaryStepper; // forward declaration

class Keyframe{
public:
	
    Keyframe(int v, RotaryStepper* m);
	
	int getAbsolute();
	int getRelativeToCurrent();
	int getRelativeToHome();
	
	void setMotor(RotaryStepper* m);
	void setRelativeToHome(int v);
	
protected:
	
private:
	
	RotaryStepper* motor;
	int value; // value is relative to home

};

#endif
