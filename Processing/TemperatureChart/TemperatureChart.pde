import processing.serial.*;
  
Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float yHeight = 0;
int minTemperature = -20;
int maxTemperature = 40;

void setup () {
  // set the window size:
  size(400, 300);
  noLoop();
  
  myPort = new Serial(this, "COM13", 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
  drawAxis();
  stroke(255);
}

int last=0;
void draw () {
  // everything happens in the serialEvent()
  //point(xPos, height - yHeight);
  line (xPos-1,last,xPos,height-yHeight);
  last =floor(height-yHeight);
}

void drawAxis() {
  stroke(127);
  strokeWeight(4); 
  line(0, height - mapValue(0), width, height - mapValue(0)); 
  strokeWeight(1); 
  for (int i = minTemperature; i < maxTemperature; i = i + 10) {
    line(0, mapValue(i), width, mapValue(i));
  }
}

float mapValue(float value) {
  return map(value, minTemperature, maxTemperature, 0, height);
}
  
void serialEvent (Serial myPort) {
  
  // get the ASCII string:
  String inString = myPort.readStringUntil('\n');
  
  if (inString == null) {
    return;
  }
  
  // trim off any whitespace:
  inString = trim(inString);
  println(inString);
  // convert to an int and map to the screen height:
  yHeight = float(trim(inString)); 
  
  yHeight = mapValue(yHeight);

  // draw the line:
  redraw(); 

  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 1;
    background(0);
    drawAxis();
  } else {
    // increment the horizontal position:
    xPos++;
  }
}