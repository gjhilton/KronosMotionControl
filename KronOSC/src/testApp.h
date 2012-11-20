#pragma once

#include "ofMain.h"
#include "ofxUI.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
	
	ofxUICanvas *gui;
	void guiEvent(ofxUIEventArgs &e);
		
};
