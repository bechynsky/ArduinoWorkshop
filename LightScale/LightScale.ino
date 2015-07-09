const byte SCALE_VALUE[] = { B00000100, B00001100, B00011100, B00111100};

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  // porty 2,3,4,5 jako vystup
  DDRD |= B00111100;
}

void loop() {
  int light = analogRead(A1);
  Serial.println(light);
  
  int scale = map(light, 400, 800, 0, 3);
  Serial.println(scale);
  
  PORTD = B00000000;
  // PORTD |= (B00000100 << scale);
  PORTD |= SCALE_VALUE[scale];
  
  delay(200);
}
