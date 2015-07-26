#define BUZZER 6
#define PAUSE 2

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(BUZZER, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(PAUSE);              // wait for a second
  digitalWrite(BUZZER, LOW);    // turn the LED off by making the voltage LOW
  delay(PAUSE);              // wait for a second
}

