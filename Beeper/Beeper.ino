#define BUZZER 6
#define LED 2

int tune = 100;
int volume = 20;
long vosec = 0;
int ledx = 0;
long toneLength = 300000;

/*
 * 
___________________________________________________  
|   | |  | |   |   | |  | |  | |   |   | |  | |   | 
|   | |  | |   |   | |  | |  | |   |   | |  | |   | 
|   | |  | |   |   | |  | |  | |   |   | |  | |   | 
|   |_|  |_|   |   |_|  |_|  |_|   |   |_|  |_|   | 
|    |    |    |    |    |    |    |    |    |    | 
|    |    |    |    |    |    |    |    |    |    | 
|____|____|____|____|____|____|____|____|____|____|  

  1  2 3  4  5    6 7 8  9 10 11 12  13 14 15
 * 
 */


int tunes[] = {1, 3, 5, 6, 8, 0, 8, 0, //kocka leze dirou
              10, 0, 10, 0, 8, 8, 8, 8, //pes oknem
              10, 0, 10, 0, 8, 8, 8, 8, //pes oknem
              6, 0, 6, 0, 5, 0, 5, 0,  // nebude-li prset
              3, 0, 3, 0, 8, 8, 8, 8, //nezmokneeem
              6, 0, 6, 0, 5, 0, 5, 0,  // nebude-li prset
              3, 0, 3, 0, 1, 1, 0, 0, //nezmoknem
              -1};

int tones[] = { 0,
//  C    C#    D     D#     E     F    F#    G     G#    A    A#     H
//  1    2     3      4     5     6    7     8     9    10    11    12
  2834, 2675, 2525, 2383, 2249, 2123, 2004, 1891, 1785, 1685, 1590, 1501, 
  1417, 1337, 1262, 1191, 1124, 1061, 1002,  945,  892,  842,  795,  750
};


int pos = 0;
void setup() {
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);
  tune = tones[tunes[pos++]];
  digitalWrite(LED, HIGH);
  ledx = 1;
}

void loop() {
    if (tune>0) {
    digitalWrite(BUZZER, HIGH);   // Přitáhneme membránu reproduktoru
    delayMicroseconds(volume);     // počkáme
    digitalWrite(BUZZER, LOW);    // pustíme membránu
    delayMicroseconds(tune-volume);     // zase počkáme
    vosec+=tune+volume;
    } else {
      delayMicroseconds(2000); 
      vosec+=2000;
    }

    if (vosec>=toneLength) {
      vosec-=toneLength;

      if (tunes[pos]==-1) {
        pos = 0;
      }
      tune = tones[tunes[pos++]];

      // svetelny metronom   
      if (ledx == 0 ) {
        digitalWrite(LED, HIGH);
      } else {
        digitalWrite(LED, LOW);
      }
      ledx++;
      if (ledx==4) {ledx=0;}
    }
}

