const int SCALE_PINS[] = { 2, 3, 4, 5};
const int SCALE_LEN = 4;

// fotorezistor - A1, termistor - A0
int senzor = A1;

void setup() {
  Serial.begin(9600);
  pinMode(senzor, INPUT);
  
  // porty 2,3,4,5 jako vystup
  for (int i = 0; i < SCALE_LEN; i++) {
    pinMode(SCALE_PINS[i], OUTPUT);
  }
}

void loop() {
  int light = analogRead(senzor);
  Serial.println(light);
  
  int scale = map(light, 300, 1000, 0, 3);

  // vse zhasnout
  for (int i = 0; i < SCALE_LEN; i++) {
    digitalWrite(SCALE_PINS[i], LOW);
  }

  // zobrazit novou hodnotu
  for (int i = 0; i < scale+1; i++) {
    digitalWrite(SCALE_PINS[i], HIGH);
  }
  
  delay(200);
}
