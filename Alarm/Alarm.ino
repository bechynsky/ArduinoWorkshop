#include <EEPROM.h>
#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <TM1636.h>


// tlacitka
const int KEY_DOWN = 9;
const int KEY_UP = 10;
const int KEY_MENU = 11;

const int ALARM_BUZZER = 6;

TM1636 tm1636(7,8);

// struktura pro cas
tmElements_t tm;
// obsah pro displej
const int T_ADDRESS = 0;
int8_t t[] = {0, 0, 0, 0};

// pozice pro nastaveni cisla
int menuPosition = -1; 
// hodiny, minuty
int h, m = 0;

void setup() {
  Serial.begin(9600);
  tm1636.init();
  pinMode(KEY_DOWN, INPUT_PULLUP);
  pinMode(KEY_UP, INPUT_PULLUP);
  pinMode(KEY_MENU, INPUT_PULLUP);
  pinMode(ALARM_BUZZER, OUTPUT);

  // Pozor u starsich verzi Arduino IDE http://forum.arduino.cc/index.php?topic=312645
  EEPROM.get(T_ADDRESS, t);
  tm1636.point(POINT_ON);
  tm1636.display(t);
  
  alarm();
}

void loop() {
  if(digitalRead(KEY_MENU) == LOW)
  {
    delay(20);
    if(digitalRead(KEY_MENU) == LOW)
    {
      menuPosition++;
      if (menuPosition > 3) {
        menuPosition = -1;
      }
      EEPROM.put(T_ADDRESS, t);
    }
  }

  if (menuPosition > -1) {
    if(digitalRead(KEY_UP) == LOW)
    {
      delay(30);
      if(digitalRead(KEY_UP) == LOW)
      {
        t[menuPosition]++;
        if (t[menuPosition] > 9) {
          t[menuPosition] = 0;
        }
      }
    }
    
    if(digitalRead(KEY_DOWN) == LOW)
    {
      delay(30);
      if(digitalRead(KEY_DOWN) == LOW)
      {
        t[menuPosition]--;
        if (t[menuPosition] < 0) {
          t[menuPosition] = 9;
        }
      }
    }
    
    validateAlarmTime();
  }
  
  if (RTC.read(tm)) {
    h = tm.Hour;
    m = tm.Minute;
    
    if (h == ((t[0] * 10) + t[1]) && (m == ((t[2] * 10) + t[3]))) {
      alarm();
    } else {
      alarmStop();
    }
  }
  
  tm1636.point(POINT_ON);
  tm1636.display(t);
  delay(100);
}

void validateAlarmTime() {
  if (t[0] > 2) {
    t[0] = 2;
  }
  
  if (((t[0] * 10) + t[1]) > 23) {
    t[0] = 2;
    t[1] = 3;
  }

  if (t[2] > 5) {
    t[2] = 5;
  }
  
  if (((t[2] * 10) + t[3]) > 59) {
    t[2] = 5;
    t[3] = 9;
  }
}

void alarm() {
    digitalWrite(ALARM_BUZZER, HIGH);
}

void alarmStop() {
    digitalWrite(ALARM_BUZZER, LOW);
}
