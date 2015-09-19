const byte SCALE_VALUE[] = { 0b00000100, 0b00001100, 0b00011100, 0b00111100};

void setup() {
  Serial.begin(9600);
  pinMode(A1, INPUT);
  // porty 2,3,4,5 jako vystup
  DDRD |= 0b00111100;
}

void loop() {
  int light = analogRead(A1);
  Serial.println(light);
  
  int scale = map(light, 400, 800, 0, 3);
  Serial.println(scale);
  
  PORTD = 0b00000000;
  PORTD |= (0b00000100 << scale);
  // PORTD |= SCALE_VALUE[scale];
  
  delay(200);
}
