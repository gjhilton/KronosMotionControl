#ifndef __KronosMotionControlSimulator__RotaryStepper__
#define __KronosMotionControlSimulator__RotaryStepper__

class RotaryStepper{
public:
	
    RotaryStepper(int number_of_steps_per_rotation, int motor_pin_1, int motor_pin_2, int motor_pin_3, int motor_pin_4);

	int getAbsoluteStep();
	int getRelativeStep();
	int getHomePos();
	bool homeSet();
	
	void setHome(int step);
	void setAtHome();

	void goHome();
	void goRelative(int nsteps);
	
	float stepToDegrees(int step);
	float stepToRotations(int step);
	
protected:
	
private:
	
	int abs_step;
	int home_offset_steps;
	int steps_per_rotation;
	bool home_is_set;
	
	void drive(int target);
	
};

#endif