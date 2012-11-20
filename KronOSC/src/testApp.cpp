#include "testApp.h"

#define WIDGETNAME_HARD_STOP "HARD STOP"
#define WIDGETNAME_REWIND "REWIND TO HOME"
#define WIDGETNAME_SET_01 "SET N STEPS FROM 0->1"
#define WIDGETNAME_SET_12 "SET N STEPS FROM 1->2"
#define WIDGETNAME_SET_23 "SET N STEPS FROM 2->3"
#define WIDGETNAME_FWD "FORWARD 50"
#define WIDGETNAME_BACK "REVERSE 50"
#define WIDGETNAME_DEPLOY "DEPLOY"
#define WIDGETNAME_UNDEPLOY "UNDEPLOY"

#define OSC_ADDR_HARD_STOP "/hardstop"
#define OSC_ADDR_REWIND "/rewind"
#define OSC_ADDR_SET_01 "/set1"
#define OSC_ADDR_SET_12 "/set2"
#define OSC_ADDR_SET_23 "/set3"
#define OSC_ADDR_FWD "/fwd"
#define OSC_ADDR_BACK "/rev"
#define OSC_ADDR_DEPLOY "/deploy"
#define OSC_ADDR_UNDEPLOY "/undeploy"

void testApp::setup(){
	
	sender.setup(HOST, PORT);
	
	ofSetVerticalSync(true);
	ofEnableSmoothing();
    	
	float dim = 32;
	float xInit = OFX_UI_GLOBAL_WIDGET_SPACING;
    float length = 320-xInit;
    
    gui = new ofxUICanvas(0,0,length+xInit,ofGetHeight());
	gui->setFont("GUI/Inconsolata.ttf", false, true, false, 300);
    gui->setFontSize(OFX_UI_FONT_LARGE, 10);
	gui->setFontSize(OFX_UI_FONT_MEDIUM, 8);
    gui->setFontSize(OFX_UI_FONT_SMALL, 6);
	
	gui->addWidgetDown(new ofxUILabelButton(WIDGETNAME_HARD_STOP, false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	
	gui->addWidgetDown(new ofxUILabelButton(WIDGETNAME_REWIND, false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	
	gui->addWidgetDown(new ofxUILabelButton(WIDGETNAME_SET_01, false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	gui->addWidgetDown(new ofxUILabelButton(WIDGETNAME_SET_12, false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	gui->addWidgetDown(new ofxUILabelButton(WIDGETNAME_SET_23, false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));

	gui->addWidgetDown(new ofxUILabelButton("FORWARD 50", false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	gui->addWidgetDown(new ofxUILabelButton("REVERSE 50", false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	
	gui->addWidgetDown(new ofxUILabelButton("DEPLOY", false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	gui->addWidgetDown(new ofxUILabelButton("UNDEPLOY", false, 0, dim, 0, 0, OFX_UI_FONT_SMALL));
	
	ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
}

void testApp::update(){

}

void testApp::draw(){
	string buf;
	buf = "sending osc to " + string(HOST) + ":" + ofToString(PORT);
	ofDrawBitmapString(buf, 5, 490);
}

void testApp::sendOSC(string address, int val=0){
	ofxOscMessage m;
	m.setAddress(address);
	m.addIntArg(val);
	sender.sendMessage(m);
	cout << "Send -> " << address << ":" << val << endl;
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();

	if(name == WIDGETNAME_HARD_STOP){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Requesting hard stop" << endl;
			sendOSC(OSC_ADDR_HARD_STOP,0);
		}
    }
    
	if(name == WIDGETNAME_REWIND){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Rewind" << endl;
			sendOSC(OSC_ADDR_REWIND,0);
		}
    }
	
	if(name == WIDGETNAME_SET_01){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Setting steps from 0-1" << endl;
			sendOSC(OSC_ADDR_SET_01,4);
		}
    }
	
	if(name == WIDGETNAME_SET_12){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Setting steps from 1-2" << endl;
			sendOSC(OSC_ADDR_SET_12,8);
		}
    }
	
	if(name == WIDGETNAME_SET_23){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Setting steps from 2-3" << endl;
			sendOSC(OSC_ADDR_SET_23,12);
		}
    }
	
	if(name == WIDGETNAME_FWD){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Going forward 50 steps" << endl;
			sendOSC(OSC_ADDR_FWD,50);
		}
    }
	
	if(name == WIDGETNAME_BACK){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Going back 50 steps" << endl;
			sendOSC(OSC_ADDR_BACK,50);
		}
    }
	
	if(name == WIDGETNAME_DEPLOY){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "DEPLOY!" << endl;
			sendOSC(OSC_ADDR_DEPLOY,0);
		}
    }
	
	if(name == WIDGETNAME_UNDEPLOY){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "UNDEPLOY!" << endl;
			sendOSC(OSC_ADDR_UNDEPLOY,0);
		}
    }
	
}