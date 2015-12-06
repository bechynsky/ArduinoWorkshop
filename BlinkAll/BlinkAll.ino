// 1 sekunda
#define PAUSE 1000
#define MASK 0b00111100

void setup() {
  // porty 2,3,4,5 jako vystup
  // DDRD = DDRD | 0b00111100;
  DDRD |= MASK; //0b00111100;
  PORTD |= MASK; //0b00111100;
}

void loop() {
  //  preklopeni hodnot
  //  PORTD ^= MASK; //0b00111100;
  //  delay(PAUSE);
  PORTD |= MASK; //0b00111100;
  delay(PAUSE);
  PORTD &= !MASK; //0b00111100;
  delay(PAUSE);
}
