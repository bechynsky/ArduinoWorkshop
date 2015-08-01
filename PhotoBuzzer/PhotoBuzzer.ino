#define BUZZER 6

int pause = 1;

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
    pause = analogRead(A1);
    digitalWrite(BUZZER, HIGH);   // Přitáhneme membránu reproduktoru
    delayMicroseconds(pause);     // počkáme
    digitalWrite(BUZZER, LOW);    // pustíme membránu
    delayMicroseconds(pause);     // zase počkáme
                                  //a jedeme dokola...
}

