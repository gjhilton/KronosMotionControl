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

void testApp::setup(){
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

}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName();

	if(name == WIDGETNAME_HARD_STOP){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Requesting hard stop" << endl;
		}
    }
    
	if(name == WIDGETNAME_REWIND){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Rewind" << endl;
		}
    }
	
	if(name == WIDGETNAME_SET_01){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Setting steps from 0-1" << endl;
		}
    }
	
	if(name == WIDGETNAME_SET_12){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Setting steps from 1-2" << endl;
		}
    }
	
	if(name == WIDGETNAME_SET_23){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Setting steps from 2-3" << endl;
		}
    }
	
	if(name == WIDGETNAME_FWD){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Going forward 50 steps" << endl;
		}
    }
	
	if(name == WIDGETNAME_BACK){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "Going back 50 steps" << endl;
		}
    }
	
	if(name == WIDGETNAME_DEPLOY){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "DEPLOY!" << endl;
		}
    }
	
	if(name == WIDGETNAME_UNDEPLOY){
		ofxUILabelButton *button = (ofxUILabelButton *) e.widget;
		if (button->getValue() == 1){
			cout << "UNDEPLOY!" << endl;
		}
    }
	
}