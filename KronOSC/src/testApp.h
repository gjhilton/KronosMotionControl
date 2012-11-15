#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxOsc.h"

// #define HOST "localhost"
#define HOST "192.168.1.177"
#define PORT 10000

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
