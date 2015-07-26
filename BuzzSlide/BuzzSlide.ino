#define BUZZER 6

int pause = 1;

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(BUZZER, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(pause);              // wait for a second
  digitalWrite(BUZZER, LOW);    // turn the LED off by making the voltage LOW
  delay(pause);              // wait for a second
  pause++;
  if(pause==20) {pause=1;}
}

