#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 12345

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
	
	ofxUICanvas *gui;
	void guiEvent(ofxUIEventArgs &e);
	
	ofxOscSender sender;
	
	void sendOSC(string address, int val);
		
};
