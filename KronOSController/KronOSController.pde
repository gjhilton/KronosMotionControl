import oscP5.*;
import netP5.*;
import controlP5.*;

ControlP5 cp5;
Textarea incomingOSC, outgoingOSC;
OscP5 oscP5;
NetAddress kronosIP;

String[] messagesReceived;
String[] messagesSent;

final String OSC_ADDR_GO = 			"kronos/go";
final String OSC_ADDR_GO_KEY = 		"kronos/key";
final String OSC_ADDR_GO_HOME = 	"kronos/home";
final String OSC_ADDR_SET_KEY = 	"kronos/set/key";
final String OSC_ADDR_SET_HOME = 	"kronos/set/home";

final int N_LINES = 20;
final int KRONOS_HEIGHT = 2000;
final int CONTROL_WIDTH = 130;
final int CONTROL_SPACING = 4;

final int COLOUR_BG = color(1,34,51);
final int COLOUR_1 = color(1,34,51); 		// drive buttons
final int COLOUR_2 = color(3,72,106); 		// go buttons
final int COLOUR_3 = color(231,197,6); 	// set buttons
final int COLOUR_4 = color(249,112,0); 		// set buttons over

void setup() {
	size(1024,700);
	frameRate(25);

	oscP5 = new OscP5(this,12000);
	kronosIP = new NetAddress("127.0.0.1",12000);

	cp5 = new ControlP5(this);
	setupTextboxes();
	setupManualDrive();
	setupAutoDrive();
}

void draw() {
	background(COLOUR_BG); 
	drawTextboxes();
}
void oscEvent(OscMessage m) {
	String s = m.addrPattern();
	if (m.typetag().equals("i")){
		s += "->" + str(m.get(0).intValue());
	}
	addReceivedMessage(s);
}

void oscSend(String address, String payload){
	OscMessage m = new OscMessage(address);
	m.add(payload);
	oscP5.send(m, kronosIP);
	addSentMessage(address, payload);
}

void oscSend(String address, int payload){
	OscMessage m = new OscMessage(address);
	m.add(payload);
	oscP5.send(m, kronosIP);
	addSentMessage(address, str(payload));
}

void oscSend(String address){
	OscMessage m = new OscMessage(address);
	oscP5.send(m, kronosIP);
	addSentMessage(address);
}

void addSentMessage(String address, String payload){
	for (int i = 0; i <N_LINES-1; i++) {
		messagesReceived[i] = messagesReceived[i+1];
		messagesSent[i] = messagesSent[i+1];
	}
	messagesSent[N_LINES-1] = hour() + ":" + minute() + ":" + second() + " SEND " + address + "->" + payload;
	messagesReceived[N_LINES-1] = "";
}

void addSentMessage(String address){
	for (int i = 0; i <N_LINES-1; i++) {
		messagesReceived[i] = messagesReceived[i+1];
		messagesSent[i] = messagesSent[i+1];
	}
	messagesSent[N_LINES-1] = hour() + ":" + minute() + ":" + second() + " SEND " + address;
	messagesReceived[N_LINES-1] = "";
}

void addReceivedMessage(String payload){
	for (int i = 0; i <N_LINES-1; i++) {
		messagesReceived[i] = messagesReceived[i+1];
		messagesSent[i] = messagesSent[i+1];
	}
	messagesSent[N_LINES-1] = "";
	messagesReceived[N_LINES-1] = hour() + ":" + minute() + ":" + second() + " " + payload;
}

void setupTextboxes(){
	outgoingOSC = cp5.addTextarea("outgoing")
                  .setPosition(12,400)
                  .setSize(500,400)
                  .setFont(createFont("arial",11))
                  .setLineHeight(14)
                  .setColor(color(152,152,152))
				  .setColorBackground(10);
	incomingOSC = cp5.addTextarea("incoming")
                  .setPosition(500,400)
                  .setSize(500,400)
                  .setFont(createFont("arial",11))
                  .setLineHeight(14)
                  .setColor(color(255,255,255))
					.setColorBackground(10);
	
	messagesReceived = new String[N_LINES];
	messagesSent = new String[N_LINES];
	for (int i = 0; i <N_LINES; i++) {
		messagesReceived[i] = "";
		messagesSent[i] = "";
	}
}

void drawTextboxes(){
	String in = "";
	String out = "";
	for (int i = 0; i <N_LINES; i++) {
		in = in + messagesReceived[i] + "\n";
		out = out + messagesSent[i] + "\n";
	}
	outgoingOSC.setText(out);
	incomingOSC.setText(in);
}

void addbutton(String f, String label, int colour, int x, int y){
	
	
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
	}
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
	
	addbutton("ghome", 		"go home", 4, col_kfg_x, y+=50);
	addbutton("shome", 		"set home here", 0, col_kfs_x, y);
	
	addbutton("gkf1", 		"go to kf 1", 3, col_kfg_x, y+=50);
	addKFControl("k1","keyframe 1",col_kfv_x,y);
	addbutton("skf1", 		"set kf 1", 0, col_kfs_x, y);
	
	addbutton("gkf2", 		"go to kf 2", 3, col_kfg_x, y+=50);
	addKFControl("k2","keyframe 2",col_kfv_x,y);
	addbutton("skf2", 		"set kf 2", 0, col_kfs_x, y);
	
	addbutton("gkf3", 		"go to kf 3", 3, col_kfg_x, y+=50);
	addKFControl("k3","keyframe 3",col_kfv_x,y);
	addbutton("skf3", 		"set kf 3", 0, col_kfs_x, y);
		
	addbutton("gkf4", 		"go to kf 4", 3, col_kfg_x, y+=50);
	addKFControl("k4","keyframe 4",col_kfv_x,y);
	addbutton("skf4", 		"set kf 4", 0, col_kfs_x, y);
	
	addbutton("gkf5", 		"go to kf 5", 3, col_kfg_x, y+=50);
	addKFControl("k5","keyframe 5",col_kfv_x,y);
	addbutton("skf5", 		"set kf 5", 0, col_kfs_x, y);
	
	addbutton("gkf6", 		"go to kf 6", 3, col_kfg_x, y+=50);
	addKFControl("k6","keyframe 6",col_kfv_x,y);
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

void setKF(int which){
	oscSend(OSC_ADDR_SET_KEY + which, int(cp5.getController("k"+which).getValue()));
	cp5.saveProperties(("keyframe.properties"));
}
