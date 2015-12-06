/****************************************************************************/
//  Demo function:Use the light sensor to control the brightness of the LED.
//		The brighter the ambient light intensity, the darker the LED.
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

/*Definition of the LED and the light sensor*/
#define LED2	3
#define LED4	5
#define LIGHT_SENSOR	A1

void setup()
{
	Serial.begin(9600);
	init_pins();
}
void loop()
{
	/*The brighter the ambient light intensity, the darker the LED*/
	uint8_t light_level,duty_cycle;
	light_level = getLightLevel();//should be 0~7
	duty_cycle = light_level*30;  //the duty_cycle of the PWM should be 0~210
	
	/*The LED that is controled by PWM pin should be LED2 or LED4.*/
	/*The greater the duty_cycle,the brighter the LED.*/
	analogWrite(LED2,duty_cycle);
	delay(500);
}
/*Initialization for the hardware.*/
void init_pins()
{
	/*Set LED2 and LED4 to be output.*/
	/*The initialization of the output level is LOW.*/
	pinMode(LED2, OUTPUT);
	digitalWrite(LED2, LOW);
	pinMode(LED4, OUTPUT);
	digitalWrite(LED4, LOW);
	/*set the light sensor that connects with A1 to be input*/
	pinMode(LIGHT_SENSOR, INPUT);
}
/****************************************************************/
/*Function:Get the ambient light level.							*/
/*Parameter:void												*/
/*Return:	uint8_t,range from 0 to 7,0 = brightest,7 = darkest */
uint8_t getLightLevel()
{
	uint16_t resistance;
	uint8_t light_level;
	resistance = (uint16_t)getLightIntensity();
	Serial.print("resistance = ");
	Serial.println(resistance);
	if(resistance < 10) light_level = 0;
	else if(resistance < 50)light_level = 1;
	else if(resistance < 80)light_level = 2;
	else if(resistance < 110)light_level = 3;
	else if(resistance < 140)light_level = 4;
	else if(resistance < 170)light_level = 5;
	else if(resistance < 200)light_level = 6;
	else light_level = 7;
	return light_level;
}
/*********************************************************************/
/*Function:Get the resistance of the light sensor					 */
/*Parameter:void													 */
/*Return:	float,the resistance of the light sensor,its unit is kohm */
/*			The brighter the ambient light intensity,the smaller the */
/*			resistance.												 */
float getLightIntensity()
{
	int sensorValue = analogRead(LIGHT_SENSOR);
	float rsensor;
	rsensor=(float)(1023-sensorValue)*10/sensorValue;
	return rsensor;
}

/*The end of the file "SensorControlBrightness.ino"*/
