/**********************************************************************/
//  Demo function:This demo will sweep 4 LEDs with a settable speed.
//
//  Author:Frankie.Chu
//  Date:23 September, 2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//
/*******************************************************************************/

//-------pin definition of LEDs---------------//
#define LED4	5
#define LED3	4
#define LED2	3
#define LED1	2

void setup()
{
	/*Initialization for the hardware.*/
	init_pins();
}
void loop()
{
	byte speed = 1;
	runLED(speed);//Sweeping speed of LEDs, range from 1 to 10.
}
/*Initialization for the hardware,and should be call first*/
void init_pins()
{
	pinMode(LED4, OUTPUT);
	pinMode(LED3, OUTPUT);
	pinMode(LED2, OUTPUT);
	pinMode(LED1, OUTPUT);
	turnOffAll();//Turn off all the LEDs first.
}
/*Turn on one LED*/
inline void turnOn(int pinLED)
{
	digitalWrite(pinLED, HIGH);
}
/*Turn Off one LED*/
inline void turnOff(int pinLED)
{
	digitalWrite(pinLED, LOW);
}
/*Turn on all the LEDs*/
inline void turnOnAll()
{
	turnOn(LED4);
	turnOn(LED3);
	turnOn(LED2);
	turnOn(LED1);
}
/*Turn off all the LEDs*/
inline void turnOffAll()
{
	turnOff(LED4);
	turnOff(LED3);
	turnOff(LED2);
	turnOff(LED1);
}
/****************************************************************/
/*Function:Sweep all LEDs.								        */
/*Parameter:byte speed,range from 1 to 10,1 = lowest,10 = fastest*/
/*Return:	void 												 */
void runLED(byte speed)
{
	if((speed > 0)&&(speed < 11))//If the value of speed is valid?
	{
		uint8_t shifter = 0x01;
		for(uint8_t i = 0;i < 4;i ++)
		{
			if(shifter&0x01)//if the lowest significant bit that represents LED1 is HIGH? 
				turnOn(LED1);//yes, turn on LED1.
			else			
				turnOff(LED1);//no, turn off LED1.
			if(shifter&0x02) 
				turnOn(LED2);
			else			
				turnOff(LED2);
			if(shifter&0x04) 
				turnOn(LED3);
			else			
				turnOff(LED3);
			if(shifter&0x08)
				turnOn(LED4);
			else			
				turnOff(LED4);
			shifter <<= 1;//left shift 1 bit, light up the next LED and put out the current one.
			delay(500/speed);
		}
		turnOffAll();//Turn off all LEDs after running the LEDs
	}
}

/*The end of the runLED.ino*/

