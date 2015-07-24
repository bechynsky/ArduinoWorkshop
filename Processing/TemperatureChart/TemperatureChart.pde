import processing.serial.*;
  
Serial myPort;        // The serial port
int xPos = 1;         // horizontal position of the graph
  
void setup () {
  // set the window size:
  size(400, 300);        
  
  myPort = new Serial(this, "COM7", 9600);
  // don't generate a serialEvent() unless you get a newline character:
  myPort.bufferUntil('\n');
  // set inital background:
  background(0);
}

void draw () {
  // everything happens in the serialEvent()
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
  float inByte = float(trim(inString)); 
  
  inByte = map(inByte, -20, 40, 0, height);

  // draw the line:
  stroke(127,34,255);
  line(xPos, height, xPos, height - inByte);

  // at the edge of the screen, go back to the beginning:
  if (xPos >= width) {
    xPos = 0;
    background(0); 
  } else {
    // increment the horizontal position:
    xPos++;
  }
}
