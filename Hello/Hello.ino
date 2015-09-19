#include <TM1636.h>

TM1636 tm1636(7,8);

void setup() {
  tm1636.init();
}

/*
 *  0000
 * 5    1
 * 5    1
 * 5    1
 *  6666 
 * 4    2
 * 4    2
 * 4    2
 *  3333
 *  
 *  A  = 01110111 - 0x77
 *  H  = 01110110 - 0x76
 *  O  = 00111111 - 0x3F
 *  J  = 00011110 - 0x1E
 */

void LED(int addr, int data) {
  tm1636.start();
  tm1636.writeByte(ADDR_FIXED);
  tm1636.stop();

  tm1636.start();
  tm1636.writeByte(0xc0 | addr);
  tm1636.writeByte(data);
  tm1636.stop();

  tm1636.start();
  tm1636.writeByte(0x28);
  tm1636.stop();
  
}

int segdata = 0;

void loop() {


  LED(0,0x77);
  LED(1,0x76);
  LED(2,0x3f);
  LED(3,0x1E);
  
  delay(400);
  
}
