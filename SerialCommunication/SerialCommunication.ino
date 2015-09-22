void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // cekani na seriovy port
  }

  Serial.print("Napiste sve jmeno: ");
}

void loop() {
    if (Serial.available() > 0) {    
      String text = Serial.readString();

      Serial.println(text);
    }
}
