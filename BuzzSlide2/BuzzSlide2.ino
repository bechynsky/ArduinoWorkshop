#define BUZZER 6
#define TRIGGER 10 

int pause = 1;
int play = 0;

void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(TRIGGER, INPUT_PULLUP);
}

void loop() {
  if (play==1) {
    digitalWrite(BUZZER, HIGH);   // turn the LED on (HIGH is the voltage level)
    delayMicroseconds(pause);              // wait for a second
    digitalWrite(BUZZER, LOW);    // turn the LED off by making the voltage LOW
    delayMicroseconds(pause);              // wait for a second
    pause++;
    if(pause==800) {pause=1;play=0;}
  }
  if (digitalRead(TRIGGER)==LOW) {
    play=1; pause=1;
  }
}

