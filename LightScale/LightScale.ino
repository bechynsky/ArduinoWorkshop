const byte SCALE_VALUE[] = { 0b00000100, 0b00001100, 0b00011100, 0b00111100};

// fotorezistor - A1, termistor - A0
int senzor = A1;

void setup() {
  Serial.begin(9600);
  pinMode(senzor, INPUT);
  // porty 2,3,4,5 jako vystup
  DDRD |= 0b00111100;
}

void loop() {
  int light = analogRead(senzor);
  Serial.println(light);
  
  int scale = map(light, 300, 1000, 0, 3);
  Serial.println(scale);
  
  PORTD &= !0b00111100; // nastaveni vychoziho stavu - zhasnuto
  PORTD |= (0b00000100 << scale);
  // PORTD |= SCALE_VALUE[scale];
  
  delay(200);
}
