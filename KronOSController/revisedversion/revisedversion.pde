
import controlP5.*;

ControlP5 cp5;

final int WHITE = color(255,255,255);
final int GREY = color(52,52,52);
final int DARK = color(35,35,35);
final int POSITION_CONTROL_WIDTH = 70;

void setup() {
	size(1200,700);
	cp5 = new ControlP5(this);
  
	int x = 600;
	int y = 40;
	int spacing = 80;
	
	addHome(x,y);
	x += spacing;
	
	addPosition("position 1",(x+spacing*0),y);
	addPosition("position 2",(x+spacing*1),y);
	addPosition("position 3",(x+spacing*2),y);
	addPosition("position 4",(x+spacing*3),y);
	addPosition("position 5",(x+spacing*4),y);
	addPosition("position 6",(x+spacing*5),y);

	x = 500;
	y = 8;
	int vspacing=32;
	addDrvieButton("UP 1000", "1000 UP",x,y+=vspacing, false);
	addDrvieButton("UP 500", "500 UP",x,y+=vspacing, false);
	addDrvieButton("UP 100", "100 UP",x,y+=vspacing, false);
	addDrvieButton("UP 50", "50 UP",x,y+=vspacing, false);
	addDrvieButton("UP 10", "10 UP",x,y+=vspacing, false);
	addDrvieButton("UP 5", "5 UP",x,y+=vspacing, false);
	addDrvieButton("UP 1", "1 UP",x,y+=vspacing, false);
	y+=52;
	addDrvieButton("DOWN 1", "DOWN 1",x,y+=vspacing, true);
	addDrvieButton("DOWN 5", "DOWN 5",x,y+=vspacing, true);
	addDrvieButton("DOWN 10", "DOWN 10",x,y+=vspacing, true);
	addDrvieButton("DOWN 50", "DOWN 50",x,y+=vspacing, true);
	addDrvieButton("DOWN 100", "DOWN 100",x,y+=vspacing, true);
	addDrvieButton("DOWN 500", "DOWN 500",x,y+=vspacing, true);
	addDrvieButton("DOWN 1000", "DOWN 1000",x,y+=vspacing, true);
}

void addDrvieButton(String name, String label, int x, int y, Boolean rhs){
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

void addPosition(String name, int x, int y){
	
	cp5.addSlider(name)
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
	addGoButton(name + "go",name,x,y);

	y+= 50;
	String easing_checkbox_name = name + "easing";
	cp5.addToggle(easing_checkbox_name)
		.setPosition(x,y)
		.setColorForeground(GREY)
		.setColorBackground(GREY)
		.setColorActive(WHITE)
		.setColorLabel(WHITE)
		.setSize(10, 10)
		.setLabel("use easing")
	;
	cp5.getController(easing_checkbox_name).getCaptionLabel().align(ControlP5.LEFT, ControlP5.CENTER).setPaddingX(15);

}

void draw() {
  background(0); 
}