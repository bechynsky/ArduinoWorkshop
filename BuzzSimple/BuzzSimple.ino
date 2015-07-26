#define BUZZER 6
#define PAUSE 1000

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  digitalWrite(BUZZER, HIGH);   // turn the BUZZER on (HIGH is the voltage level)
  delay(PAUSE);              // wait for a second
  digitalWrite(BUZZER, LOW);    // turn the BUZZER off by making the voltage LOW
  delay(PAUSE);              // wait for a second
}

