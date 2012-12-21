
import controlP5.*;

ControlP5 cp5;

final int WHITE = color(255,255,255);
final int GREY = color(52,52,52);
final int DARK = color(35,35,35);
final int POSITION_CONTROL_WIDTH = 70;

void setup() {
  size(1024,768);
  cp5 = new ControlP5(this);
  
	int x = 40;
	int y = 40;
	int spacing = 80;
	
	addHome(x,y);
	x += spacing;
	
	addPosition("pos1",(x+spacing*0),y);
	addPosition("pos2",(x+spacing*1),y);
	addPosition("pos3",(x+spacing*2),y);
	addPosition("pos4",(x+spacing*3),y);
	addPosition("pos5",(x+spacing*4),y);
	addPosition("pos6",(x+spacing*5),y);

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
	cp5.addButton(name + "go")
		.setPosition(x,y)
		.setLabel("Go")
		.setSize(POSITION_CONTROL_WIDTH,40)
		.setColorForeground(color(120))
		.setColorActive(color(255))
		.setColorLabel(color(255))
	;

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