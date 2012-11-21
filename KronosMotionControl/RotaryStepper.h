#ifndef __KronosMotionControlSimulator__RotaryStepper__
#define __KronosMotionControlSimulator__RotaryStepper__

class RotaryStepper{
public:
	
    RotaryStepper();

	float getCurrentAbsoluteDegrees();
	int getCurrentAbsoluteStep();
	int getCurrentRotation();
	int getCurrentStep();
	
protected:
	
	float stepToDegrees(int step);
	
private:
	
	int current_step;
	int steps_per_rotation;
	
};

#endif