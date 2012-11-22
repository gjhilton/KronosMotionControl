#ifndef __KronosMotionControlSimulator__RotaryStepper__
#define __KronosMotionControlSimulator__RotaryStepper__

class RotaryStepper{
public:
	
    RotaryStepper();

	int getAbsoluteStep();
	int getRelativeStep();
	int getHomePos();
	bool homeSet();
	
	void setHome(int step);
	void setAtHome();

	int goRelative(int nsteps);
	
	float stepToDegrees(int step);
	float stepToRotations(int step);
	
protected:
	
private:
	
	int abs_step;
	int home_offset_steps;
	
	bool home_is_set;
	
};

#endif