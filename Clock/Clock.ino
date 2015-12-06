#include <Wire.h>
#include <Time.h>
#include <DS1307RTC.h>
#include <TM1636.h>

TM1636 tm1636(7,8);

void setup() {
  tm1636.init();
}

void loop() {
  tmElements_t tm;
  int8_t t[4];

  if (RTC.read(tm)) {
    int h = tm.Hour;
    int m = tm.Minute;
    int s = tm.Second;
    
    
    if (h >= 0 && h < 10) {
      t[0] = 0;
      t[1] = h;
    } else {
      t[0] = h / 10;
      t[1] = h % 10;
    }
    
    if (m >= 0 && m < 10) {
      t[2] = 0;
      t[3] = m;
    } else {
      t[2] = m / 10;
      t[3] = m % 10;
    }
    
    if((s % 2) == 0) {
      tm1636.point(POINT_ON);
    } else {
      tm1636.point(POINT_OFF);
    }
    
    tm1636.display(t);
    delay(1000);
  }
}
