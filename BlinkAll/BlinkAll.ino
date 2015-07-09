// 1 sekunda
#define PAUSE 1000

void setup() {
  // porty 2,3,4,5 jako vystup
  DDRD |= B00111100;
}

void loop() {
  // preklopeni hodnot
  PORTD ^= B00111100;
  delay(PAUSE);
}
