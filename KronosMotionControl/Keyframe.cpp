#include "Keyframe.h"

Keyframe::Keyframe(int v, RotaryStepper* m) {
	setMotor(m);
	setRelativeToHome(value);
}

int Keyframe::getAbsolute(){
	return 1;
}
int Keyframe::getRelativeToCurrent(){
	return 1;
}
int Keyframe::getRelativeToHome(){
	return 1;
}

void Keyframe::setMotor(RotaryStepper* m){
	
}
void Keyframe::setRelativeToHome(int v){
	value = v;
}