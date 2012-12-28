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

/*
NetAddress kronosIP = new NetAddress("192.168.1.123",10000);
NetAddress audioIP = new NetAddress("192.168.1.4",10000);
*/

NetAddress kronosIP = new NetAddress("127.0.0.1",12000);
NetAddress audioIP = new NetAddress("127.0.0.1",12000);

final int OSC_RX_PORT = 12000;

final String OSC_ADDR_CUE = 				"audio/cue";

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

final boolean AUTOSYNC = true;
final int CONTROL_WIDTH = 130;
final int CONTROL_SPACING = 4;
final String EMPTY = "";
final int FRAMERATE = 25;
final int KRONOS_HEIGHT = 5000;
final int N_LINES = 35;
final int N_POSITIONS = 7;
final int POSITION_CONTROL_WIDTH = 70;

/* ----------------------------------------------------------------------------
 *
 * CONFIGURATION: COLOURS
 *
 * --------------------------------------------------------------------------- */

final int GREY = color(52,52,52);
final int MIDGREY = color(139,141,119);
final int WHITE = color(255,255,255);
final int BLACK = color(0,0,0);

final int BACKGROUND = color(17,21,23);

final int ORANGE_LO = color(255, 49, 0);
final int ORANGE = color(255, 102, 0);

final int YELLOW_LO = color(255, 201, 0);
final int YELLOW = color(255, 244, 0);

final int GREEN_LO = color(55, 234, 0);
final int GREEN = color(149, 249, 0);

final int PINK_LO = color(255, 0, 114);
final int PINK = color(255, 42, 177);

final int BLUE_LO = color(0, 113, 231);
final int BLUE = color(0, 176, 246);

final int PURPLE = color(133,0,233);

/* ----------------------------------------------------------------------------
 *
 * GLOBAL DECLARATION
 *
 * --------------------------------------------------------------------------- */

ControlP5 cp5;
OscP5 oscP5;
MessagePool messagepool;
PFont font = createFont("Inconsolata-dz", 18);
PFont fontsmall = createFont("Inconsolata-dz", 12);
Toggle[] cueToggles = new Toggle[N_POSITIONS];
Toggle[] easeToggles = new Toggle[N_POSITIONS];
boolean inited = false;

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
	fill(BACKGROUND);
	rect(40,40,410,500);
	messagepool.draw(50,50);
        textFont(font);
	for (int i=1; i<N_POSITIONS;i++){
		fill(YELLOW);
		textAlign(CENTER);
		int v = int (cp5.getController(getPositionSliderName(i)).getValue());
		text(v,635+(i*80),30);
	}
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

void oscSendAudioCue(int payload){
	String address = OSC_ADDR_CUE;
	messagepool.add(address.toUpperCase() + " -> " + payload,false);
	OscMessage m = new OscMessage(address);
	m.add(payload);
	oscP5.send(m, audioIP);
}

void oscSendKronos(String address, int payload){
	messagepool.add(address.toUpperCase() + " -> " + payload,false);
	OscMessage m = new OscMessage(address);
	m.add(payload);
	oscP5.send(m, kronosIP);
}

void oscSendKronos(String address){
	messagepool.add(address.toUpperCase(),false);
	OscMessage m = new OscMessage(address);
	oscP5.send(m, kronosIP);
}

/* ----------------------------------------------------------------------------
 *
 * IMPLEMENTATION: GUI HANDLERS
 *
 * --------------------------------------------------------------------------- */

void down1(int v)		{oscSendKronos(OSC_ADDR_GO,1);}
void down5(int v)		{oscSendKronos(OSC_ADDR_GO,5);}
void down10(int v)		{oscSendKronos(OSC_ADDR_GO,10);}
void down50(int v)		{oscSendKronos(OSC_ADDR_GO,50);}
void down100(int v)		{oscSendKronos(OSC_ADDR_GO,100);}
void down500(int v)		{oscSendKronos(OSC_ADDR_GO,500);}
void down1000(int v)	{oscSendKronos(OSC_ADDR_GO,1000);}

void up1(int v)			{oscSendKronos(OSC_ADDR_GO,-1);}
void up5(int v)			{oscSendKronos(OSC_ADDR_GO,-5);}
void up10(int v)		{oscSendKronos(OSC_ADDR_GO,-10);}
void up50(int v)		{oscSendKronos(OSC_ADDR_GO,-50);}
void up100(int v)		{oscSendKronos(OSC_ADDR_GO,-100);}
void up500(int v)		{oscSendKronos(OSC_ADDR_GO,-500);}
void up1000(int v)		{oscSendKronos(OSC_ADDR_GO,-1000);}

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
	oscSendKronos(address,pos);

	if (cueToggles[pos].getState()) {
		oscSendAudioCue(pos);
	}
}

void ghome(int v)	{oscSendKronos(OSC_ADDR_GO_HOME);}
void shome(int v)	{oscSendKronos(OSC_ADDR_SET_HOME);}
void status(int v)	{oscSendKronos(OSC_ADDR_REQUEST_STATUS);}
void skeys(int v)	{oscSendKronos(OSC_ADDR_REQUEST_KEYS);}

void position1set(int v)	{setKF(1);}
void position2set(int v)	{setKF(2);}
void position3set(int v)	{setKF(3);}
void position4set(int v)	{setKF(4);}
void position5set(int v)	{setKF(5);}
void position6set(int v)	{setKF(6);}

void setKF(int which){
	if (inited) {
		sendKF(which);
		saveSettings();
	}
}

void sendKF(int idx){
	oscSendKronos(OSC_ADDR_SET_KEY + idx, int(cp5.getController(getPositionSliderName(idx)).getValue()));
}

void syncKFs(){
	for (int k=1; k<N_POSITIONS; k++){
		sendKF(k);
	}
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
	cp5.loadProperties(("keyframe.properties"));

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
	
	// status buttons
	cp5.addButton("status")
		.setPosition(40,590)
		.setLabel("SHOW STATUS")
		.setSize(300,40)
		.setColorBackground(ORANGE_LO)
                .setColorForeground(ORANGE)
		.setColorActive(WHITE)
		.setColorLabel(BLACK)
		.getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
	;
	
		cp5.addButton("skeys")
		.setPosition(350,590)
		.setLabel("SHOW POSITIONS")
		.setSize(95, 40)
                .setColorBackground(ORANGE_LO)
                .setColorForeground(ORANGE)
                .setColorActive(WHITE)
                .setColorLabel(BLACK)
		.getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
	;
	
	inited = true;
	if (AUTOSYNC) syncKFs();
}

void addDriveButton(String name, String label, int x, int y, Boolean rhs){
	cp5.addButton(name)
		.setPosition(x,y)
		.setLabel(label)
		.setSize(POSITION_CONTROL_WIDTH,30)
		.setColorBackground(rhs ? PINK_LO : BLUE_LO)
                .setColorForeground(rhs ? PINK : BLUE)
                .setColorActive(WHITE)
                .setColorLabel(BLACK)
	;
	if (rhs) cp5.getController(name).getCaptionLabel().align(ControlP5.RIGHT, ControlP5.CENTER);
}

void addGoButton(String name, String label, int x, int y, boolean home){
	cp5.addButton(name)
		.setPosition(x,y)
		.setLabel(label)
		.setSize(POSITION_CONTROL_WIDTH,40)
		.setColorForeground(home ? GREEN : YELLOW)
                .setColorBackground(home ? GREEN_LO : YELLOW_LO)
		.setColorActive(WHITE)
		.setColorLabel(BLACK)
	;
	cp5.getController(name).getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER);
}

void addHome(int x, int y){
	cp5.addButton("shome")
		.setPosition(x,y)
		.setLabel("SET HOME HERE")
		.setSize(POSITION_CONTROL_WIDTH,40)
		.setColorForeground(GREEN)
                .setColorBackground(GREEN_LO)
    .setColorActive(WHITE)
    .setColorLabel(BLACK)
	;
	addGoButton("ghome","GO HOME",x,y+550,true);
}

void addPosition(int idx, int x, int y){
	
	cp5.addSlider(getPositionSliderName(idx))
		.setPosition(x,y)
		.setSize(POSITION_CONTROL_WIDTH,500)
		.setRange(5000,0)
		.setNumberOfTickMarks(6)
		.snapToTickMarks(false)
		.setLabelVisible(false)
		.setColorTickMark(GREY)
		.setColorBackground(YELLOW)
		.setColorForeground(BACKGROUND)
		.setColorActive(GREY)
		.setTriggerEvent(Slider.RELEASE)
	;
	
	y+= 550;
	addGoButton("position" + idx + "go", "position " + idx,x,y,false);

	y+= 50;
	easeToggles[idx] = makeToggle(getEasingCheckboxName(idx),idx,x,y,"use easing",false);
	
	y+= 15;
	cueToggles[idx] = makeToggle(getCueCheckboxName(idx),idx,x,y,"cue audio",true);
}

Toggle makeToggle(String name, int idx,int x, int y,String label, boolean audio){
  
        Toggle t = cp5.addToggle(name)
		.setPosition(x,y)
		.setColorForeground(BACKGROUND)
		.setColorBackground(BACKGROUND)
		.setColorActive(audio ? PURPLE: YELLOW_LO)
		.setColorLabel(audio ? PURPLE: YELLOW_LO)
		.setSize(10, 10)
		.setLabel(label)
	;
	t.addCallback(new CallbackListener() {
    	public void controlEvent(CallbackEvent theEvent) {
			if (theEvent.getAction()==ControlP5.ACTION_BROADCAST) {
				if (inited) saveSettings();
			}
		}
	});
	t.getCaptionLabel().align(ControlP5.LEFT, ControlP5.CENTER).setPaddingX(15);
	return t;
}

String getPositionSliderName(int idx){
	return "position" + idx + "set";
}

String getCueCheckboxName(int idx){
	return "position" + idx + "cue";
}

String getEasingCheckboxName(int idx){
	return "position" + idx + "easing";
}

void saveSettings(){
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
	private final int LINEHEIGHT = 14;
	private final boolean BOTTOM_UP = false;
	MessagePool (PApplet _applet, int _size) {
		applet = _applet;
		size = _size;
		messages = new Message[size];
		for (int i = 0; i <size; i++) {
			messages[i] = new Message("",false);
		}
	}
	public void add(String thetext, Boolean isincoming){
		if (BOTTOM_UP){
			for (int i = 0; i <size-1; i++) {
				messages[i] = messages[i+1];
			}
			messages[size-1] = new Message(thetext,isincoming);
		} else {
			for (int i=size-1; i > 0; i--) {
				messages[i] = messages[i-1];
			}
			messages[0] = new Message(thetext,isincoming);
		}
	}
	public void draw(int left, int top){
		textAlign(LEFT);
textFont(fontsmall);
		for (int i = 0; i <size; i++) {
			if (!messages[i].text.equals(EMPTY)){
				String str;
				if (messages[i].incoming){
					str = "RX ";
					fill(WHITE);
				} else {
					str = "TX ";
					fill(MIDGREY);
				}
				applet.text(str + messages[i].timestamp + " " + messages[i].text,left,top);
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
