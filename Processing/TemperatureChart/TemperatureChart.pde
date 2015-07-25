import processing.serial.*;
  
Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
float yHeight = 0;

void setup () {
  // set the window size:
  size(400, 300);
  noLoop();
  
  myPort = new Serial(this, "COM7", 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
  stroke(255);
}

void draw () {
  // everything happens in the serialEvent()
  line(xPos, height, xPos, height - yHeight);
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
  
  yHeight = map(yHeight, -20, 40, 0, height);

  // draw the line:
  redraw(); 

  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    background(0); 
  } else {
    // increment the horizontal position:
    xPos++;
  }
}