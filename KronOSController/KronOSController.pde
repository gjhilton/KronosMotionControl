/* ----------------------------------------------------------------------------
 *
 * KronOSController
 *
 * @author		gjhilton
 * @modified	26/12/2012
 * @version		2.0.2
 *
 * --------------------------------------------------------------------------- */

import oscP5.*;
import netP5.*;
import controlP5.*;

/* ----------------------------------------------------------------------------
 *
 * CONFIGURATION: OSC
 *
 * --------------------------------------------------------------------------- */

//final kronosIP = new NetAddress("192.168.1.123",10000);
NetAddress kronosIP = new NetAddress("127.0.0.1",12000);
final int OSC_RX_PORT = 12000;

final String OSC_ADDR_GO = 					"kronos/go";
final String OSC_ADDR_GO_KEY = 				"kronos/key";
final String OSC_ADDR_GO_KEY_EASED = 		"kronos/key/eased";
final String OSC_ADDR_GO_HOME = 			"kronos/home";
final String OSC_ADDR_SET_KEY = 			"kronos/set/key";
final String OSC_ADDR_SET_HOME = 			"kronos/set/home";
final String OSC_ADDR_REQUEST_STATUS =		"kronos/request/status";
final String OSC_ADDR_REQUEST_KEYS =		"kronos/request/keys";

/* ----------------------------------------------------------------------------
 *
 * CONFIGURATION
 *
 * --------------------------------------------------------------------------- */

final int CONTROL_WIDTH = 130;
final int CONTROL_SPACING = 4;
final String EMPTY = "";
final int FRAMERATE = 25;
final int KRONOS_HEIGHT = 5000;
final int N_LINES = 20;
final int N_POSITIONS = 7;
final int POSITION_CONTROL_WIDTH = 70;

/* ----------------------------------------------------------------------------
 *
 * CONFIGURATION: COLOURS
 *
 * --------------------------------------------------------------------------- */

final int WHITE = color(255,255,255);
final int GREY = color(52,52,52);
final int DARK = color(35,35,35);

/* ----------------------------------------------------------------------------
 *
 * GLOBAL DECLARATION
 *
 * --------------------------------------------------------------------------- */

ControlP5 cp5;
OscP5 oscP5;
MessagePool messagepool;
Toggle[] easeToggles = new Toggle[N_POSITIONS];

/* ----------------------------------------------------------------------------
 *
 * P5 LIFECYCLE
 *
 * --------------------------------------------------------------------------- */

void setup() {
	size(1200,700);
	frameRate(FRAMERATE);
	oscP5 = new OscP5(this,OSC_RX_PORT);
	messagepool = new MessagePool(this,N_LINES);
	cp5 = new ControlP5(this);
	setupGUI();
}

void draw() {
	background(0); 
	messagepool.draw(10,400);
}

/* ----------------------------------------------------------------------------
 *
 * IMPLEMENTATION: OSC
 *
 * --------------------------------------------------------------------------- */

void oscEvent(OscMessage m) {
	String s = m.addrPattern().toUpperCase();
	if (m.typetag().equals("i")){
		s += " -> " + str(m.get(0).intValue());
	}
	if (m.typetag().equals("s")){
		s += " -> " + m.get(0).stringValue();
	}
	messagepool.add(s,true);
}

void oscSend(String address, int payload){
	OscMessage m = new OscMessage(address);
	m.add(payload);
	oscP5.send(m, kronosIP);
	messagepool.add(address.toUpperCase() + " -> " + payload,false);
}

void oscSend(String address){
	OscMessage m = new OscMessage(address);
	oscP5.send(m, kronosIP);
	messagepool.add(address.toUpperCase(),false);
}

/* ----------------------------------------------------------------------------
 *
 * IMPLEMENTATION: GUI HANDLERS
 *
 * --------------------------------------------------------------------------- */

void down1(int v)		{oscSend(OSC_ADDR_GO,1);}
void down5(int v)		{oscSend(OSC_ADDR_GO,5);}
void down10(int v)		{oscSend(OSC_ADDR_GO,10);}
void down50(int v)		{oscSend(OSC_ADDR_GO,50);}
void down100(int v)		{oscSend(OSC_ADDR_GO,100);}
void down500(int v)		{oscSend(OSC_ADDR_GO,500);}
void down1000(int v)	{oscSend(OSC_ADDR_GO,1000);}

void up1(int v)			{oscSend(OSC_ADDR_GO,-1);}
void up5(int v)			{oscSend(OSC_ADDR_GO,-5);}
void up10(int v)		{oscSend(OSC_ADDR_GO,-10);}
void up50(int v)		{oscSend(OSC_ADDR_GO,-50);}
void up100(int v)		{oscSend(OSC_ADDR_GO,-100);}
void up500(int v)		{oscSend(OSC_ADDR_GO,-500);}
void up1000(int v)		{oscSend(OSC_ADDR_GO,-1000);}

void position1go(int v)	{goPosition(1);}
void position2go(int v)	{goPosition(2);}
void position3go(int v)	{goPosition(3);}
void position4go(int v)	{goPosition(4);}
void position5go(int v)	{goPosition(5);}
void position6go(int v)	{goPosition(6);}

void goPosition(int pos) {
	String address = OSC_ADDR_GO_KEY;
	if (easeToggles[pos].getState()){
		address = OSC_ADDR_GO_KEY_EASED;
	}
	oscSend(address,pos);
}

/* ----------------------------------------------------------------------------
 *
 * IMPLEMENTATION: GUI INITIALISATION
 *
 * --------------------------------------------------------------------------- */

void setupGUI(){
	int x = 600;
	int y = 40;
	int spacing = 80;
	
	// Home buttons
	addHome(x,y);
	x += spacing;
	
	// Key positions
	for (int i=1; i<N_POSITIONS;i++){
		addPosition(i, (x+spacing*(i-1)),y);
	}

	// Drive buttons
	x = 500;
	y = 8;
	int vspacing=32;
	addDriveButton("up1000", "1000 UP",x,y+=vspacing, false);
	addDriveButton("up500", "500 UP",x,y+=vspacing, false);
	addDriveButton("up100", "100 UP",x,y+=vspacing, false);
	addDriveButton("up50", "50 UP",x,y+=vspacing, false);
	addDriveButton("up10", "10 UP",x,y+=vspacing, false);
	addDriveButton("up5", "5 UP",x,y+=vspacing, false);
	addDriveButton("up1", "1 UP",x,y+=vspacing, false);
	y+=52;
	addDriveButton("down1", "DOWN 1",x,y+=vspacing, true);
	addDriveButton("down5", "DOWN 5",x,y+=vspacing, true);
	addDriveButton("down10", "DOWN 10",x,y+=vspacing, true);
	addDriveButton("down50", "DOWN 50",x,y+=vspacing, true);
	addDriveButton("down100", "DOWN 100",x,y+=vspacing, true);
	addDriveButton("down500", "DOWN 500",x,y+=vspacing, true);
	addDriveButton("down1000", "DOWN 1000",x,y+=vspacing, true);
}

void addDriveButton(String name, String label, int x, int y, Boolean rhs){
	cp5.addButton(name)
		.setPosition(x,y)
		.setLabel(label)
		.setSize(POSITION_CONTROL_WIDTH,30)
		.setColorForeground(color(120))
		.setColorActive(color(255))
		.setColorLabel(color(255))
	;
	if (rhs) cp5.getController(name).getCaptionLabel().align(ControlP5.RIGHT, ControlP5.CENTER);
}

void addGoButton(String name, String label, int x, int y){
	cp5.addButton(name)
		.setPosition(x,y)
		.setLabel(label)
		.setSize(POSITION_CONTROL_WIDTH,40)
		.setColorForeground(color(120))
		.setColorActive(color(255))
		.setColorLabel(color(255))
	;
	cp5.getController(name).getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER);
}

void addHome(int x, int y){
	cp5.addButton("sethome")
		.setPosition(x,y)
		.setLabel("SET HOME HERE")
		.setSize(POSITION_CONTROL_WIDTH,40)
		.setColorForeground(GREY)
		.setColorBackground(GREY)
		.setColorActive(WHITE)
		.setColorLabel(WHITE)
	;
	addGoButton("gohome","GO HOME",x,y+550);
}

void addPosition(int idx, int x, int y){
	
	cp5.addSlider("position"+idx)
		.setPosition(x,y)
		.setSize(POSITION_CONTROL_WIDTH,500)
		.setRange(5000,0)
		.setNumberOfTickMarks(6)
		.snapToTickMarks(false)
		.setLabelVisible(false)
		.setColorTickMark(GREY)
		.setColorBackground(WHITE)
		.setColorForeground(DARK)
		.setColorActive(GREY) 
	;
	
	y+= 550;
	addGoButton("position" + idx + "go", "position " + idx,x,y);

	y+= 50;
	Toggle t = cp5.addToggle(getEasingCheckboxName(idx))
		.setPosition(x,y)
		.setColorForeground(GREY)
		.setColorBackground(GREY)
		.setColorActive(WHITE)
		.setColorLabel(WHITE)
		.setSize(10, 10)
		.setLabel("use easing")
	;
	t.getCaptionLabel().align(ControlP5.LEFT, ControlP5.CENTER).setPaddingX(15);
	easeToggles[idx] = t;
}

String getEasingCheckboxName(int idx){
	return "position" + idx + "easing";
}

/* ----------------------------------------------------------------------------
 *
 * OLD VERSION
 *
 * --------------------------------------------------------------------------- */


void addbutton(String f, String label, int colour, int x, int y){
	/*
	
	Button b = cp5.addButton(f)
	.setCaptionLabel(label)
	.setPosition(x,y)
	.setSize(CONTROL_WIDTH,24);
	
	
	if (colour>0){
		int c = color(0, 0, 0) ;
	switch (colour){
		case 1: c = COLOUR_1; break;
		case 2: c = COLOUR_2; break;
		case 3: c = COLOUR_3; break;
		case 4: c = COLOUR_4; break;
	}
		b.setColorBackground(c);
	}
	
	if (colour==3){
		b.setColorForeground(COLOUR_4);
		b.setColorLabel(0);
	}
	
	if (colour==4){
		b.setColorForeground(COLOUR_3);
		b.setColorLabel(0);
	}*/
}

void addKFControl(String f, String label, int x, int y){
cp5.addNumberbox(f)
	.setCaptionLabel(label)
     .setRange(0, KRONOS_HEIGHT)
     .setPosition(x, y)
     .setSize(CONTROL_WIDTH, 24)
     .setScrollSensitivity(1.1);
}

void setupAutoDrive(){
	
	int y = 0;
	int col_kfg_x = 60;
	int col_kfv_x = col_kfg_x + CONTROL_WIDTH;
	int col_kfs_x = col_kfv_x + CONTROL_WIDTH + CONTROL_SPACING;
	
    addbutton("status",     "status", 4, 500, y+50);
	addbutton("skeys",  	"show keys", 4, 500, y+100);

	addbutton("ghome", 		"go home", 4, col_kfg_x, y+=50);
	addbutton("shome", 		"set home here", 0, col_kfs_x, y);
	
	addbutton("gkf1", 		"go to kf 1", 3, col_kfg_x, y+=50);
	addKFControl("k1",		"keyframe 1",col_kfv_x,y);
	addbutton("skf1", 		"set kf 1", 0, col_kfs_x, y);
	
	addbutton("gkf2", 		"go to kf 2", 3, col_kfg_x, y+=50);
	addKFControl("k2",		"keyframe 2",col_kfv_x,y);
	addbutton("skf2", 		"set kf 2", 0, col_kfs_x, y);
	
	addbutton("gkf3", 		"go to kf 3", 3, col_kfg_x, y+=50);
	addKFControl("k3",		"keyframe 3",col_kfv_x,y);
	addbutton("skf3", 		"set kf 3", 0, col_kfs_x, y);
		
	addbutton("gkf4", 		"go to kf 4", 3, col_kfg_x, y+=50);
	addKFControl("k4",		"keyframe 4",col_kfv_x,y);
	addbutton("skf4", 		"set kf 4", 0, col_kfs_x, y);
	
	addbutton("gkf5", 		"go to kf 5", 3, col_kfg_x, y+=50);
	addKFControl("k5",		"keyframe 5",col_kfv_x,y);
	addbutton("skf5", 		"set kf 5", 0, col_kfs_x, y);
	
	addbutton("gkf6", 		"go to kf 6", 3, col_kfg_x, y+=50);
	addKFControl("k6",		"keyframe 6",col_kfv_x,y);
	addbutton("skf6", 		"set kf 6", 0, col_kfs_x, y);
	
	cp5.loadProperties(("keyframe.properties"));
}

void setupManualDrive(){
	int y = 25;
	
	int col_up_x = 700;
	addbutton("rwd500", 	"up 500", 	1, col_up_x, y+=25);
	addbutton("rwd200", 	"up 200", 	1, col_up_x, y+=25);
	addbutton("rwd100", 	"up 100", 	1, col_up_x, y+=25);
	addbutton("rwd50", 		"up 50", 	1, col_up_x, y+=25);
	addbutton("rwd10", 		"up 10", 	1, col_up_x, y+=25);
	addbutton("rwd1", 		"up 1", 	1, col_up_x, y+=25);
	
	int col_down_x =  col_up_x + CONTROL_WIDTH + CONTROL_SPACING;
	addbutton("fwd1", 		"down 1", 	1, col_down_x, y+=25);
	addbutton("fwd10", 		"down 10", 	1, col_down_x, y+=25);
	addbutton("fwd50", 		"down 50", 	1, col_down_x, y+=25);
	addbutton("fwd100", 	"down 100", 1, col_down_x, y+=25);
	addbutton("fwd200", 	"down 200", 1, col_down_x, y+=25);
	addbutton("fwd500", 	"down 500", 1, col_down_x, y+=25);
}

void fwd1(int v)	{oscSend(OSC_ADDR_GO,1);}
void fwd10(int v)	{oscSend(OSC_ADDR_GO,10);}
void fwd50(int v)	{oscSend(OSC_ADDR_GO,50);}
void fwd100(int v)	{oscSend(OSC_ADDR_GO,100);}
void fwd200(int v)	{oscSend(OSC_ADDR_GO,200);}
void fwd500(int v)	{oscSend(OSC_ADDR_GO,500);}
void rwd1(int v)	{oscSend(OSC_ADDR_GO,-1);}
void rwd10(int v)	{oscSend(OSC_ADDR_GO,-10);}
void rwd50(int v)	{oscSend(OSC_ADDR_GO,-50);}
void rwd100(int v)	{oscSend(OSC_ADDR_GO,-100);}
void rwd200(int v)	{oscSend(OSC_ADDR_GO,-200);}
void rwd500(int v)	{oscSend(OSC_ADDR_GO,-500);}
void skf1(int v)	{setKF(1);}
void skf2(int v)	{setKF(2);}
void skf3(int v)	{setKF(3);}
void skf4(int v)	{setKF(4);}
void skf5(int v)	{setKF(5);}
void skf6(int v)	{setKF(6);}
void gkf1(int v)	{oscSend(OSC_ADDR_GO_KEY,1);}
void gkf2(int v)	{oscSend(OSC_ADDR_GO_KEY,2);}
void gkf3(int v)	{oscSend(OSC_ADDR_GO_KEY,3);}
void gkf4(int v)	{oscSend(OSC_ADDR_GO_KEY,4);}
void gkf5(int v)	{oscSend(OSC_ADDR_GO_KEY,5);}
void gkf6(int v)	{oscSend(OSC_ADDR_GO_KEY,6);}
void ghome(int v)	{oscSend(OSC_ADDR_GO_HOME);}
void shome(int v)	{oscSend(OSC_ADDR_SET_HOME);}
void status(int v)	{oscSend(OSC_ADDR_REQUEST_STATUS);}
void skeys(int v)	{oscSend(OSC_ADDR_REQUEST_KEYS);}

void setKF(int which){
	oscSend(OSC_ADDR_SET_KEY + which, int(cp5.getController("k"+which).getValue()));
	cp5.saveProperties(("keyframe.properties"));
}

/* ----------------------------------------------------------------------------
 *
 * MESSAGEPOOL
 *
 * --------------------------------------------------------------------------- */

public class MessagePool {
	private Message[] messages;
	private int size;
	private PApplet applet;
	private final int SENT_COLOUR = color(100,100,255);
	private final int RECEIVED_COLOUR = color(200,200,200);
	private final int LINEHEIGHT = 14;
	MessagePool (PApplet _applet, int _size) {
		applet = _applet;
		size = _size;
		messages = new Message[size];
		for (int i = 0; i <size; i++) {
			messages[i] = new Message("",false);
		}
	}
	public void add(String thetext, Boolean isincoming){
		for (int i = 0; i <size-1; i++) {
			messages[i] = messages[i+1];
		}
		messages[size-1] = new Message(thetext,isincoming);
	}
	public void draw(int left, int top){
		for (int i = 0; i <size; i++) {
			if (!messages[i].text.equals(EMPTY)){
				String str;
				if (messages[i].incoming){
					str = "RX ";
					fill(RECEIVED_COLOUR);
				} else {
					str = "TX ";
					fill(SENT_COLOUR);
				}
				applet.text(str + messages[i].timestamp + ": " + messages[i].text,left,top);
			}
			top += LINEHEIGHT;
		}
	}
}

class Message { 
	String timestamp, text;
	Boolean incoming;
	Message (String _text, Boolean _incoming) {  
		timestamp = hour() + ":" + minute() + ":" + second(); 
		text = _text;
		incoming = _incoming;
	} 
} 