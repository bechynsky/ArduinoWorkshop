#include <Wire.h>

// http://datasheets.maximintegrated.com/en/ds/DS1307.pdf
#define DS1307_CTRL_ID 0x68 

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  Wire.beginTransmission(DS1307_CTRL_ID);
  // sekundy na adrese 0x00
  Wire.write((uint8_t)0x00);
  // sekundy jsou ulozeny v 1 byte
  Wire.requestFrom(DS1307_CTRL_ID, 1);
  int s = Wire.read();
  // desitky sekund jsou v bite 4-6, je treba je posunout o 4 bite do prava
  Serial.print(s >> 4);
  // jednotky sekund jsou v bite 0-3, proto pouzijeme masku
  Serial.println(s & 0b00001111);
  Wire.endTransmission();
  
  delay(1000);
}
