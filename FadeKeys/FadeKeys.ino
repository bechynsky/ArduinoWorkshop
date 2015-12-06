#define KEY_UP		10
#define KEY_DOWN	9
// nutna podpora PWM na pinu
#define LED       5

int duty = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(KEY_UP, INPUT_PULLUP);
  pinMode(KEY_DOWN, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  if(digitalRead(KEY_UP) == LOW)
  {
    Serial.println("UP 1");
    delay(20);
    if(digitalRead(KEY_UP) == LOW)
    {
       Serial.println("UP 2");
      duty = duty + 10;
      if (duty > 255) duty = 255;
    }
  }
  
  if(digitalRead(KEY_DOWN) == LOW)
  {
    delay(20);
    if(digitalRead(KEY_DOWN) == LOW)
    {
      duty = duty - 10;
      if (duty < 0) duty = 0;
    }
  }
  Serial.println(duty);
  analogWrite(LED, duty);
  delay(50);
}
