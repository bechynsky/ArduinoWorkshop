/****************************************************************************/
//  Demo function:Get the ambient temperature by the temperature sensor on the
//		Tick Tock Shield and the formula, and it is displayed by the 4-digit 
//		display like " 25C" when the temperature is 25 degrees Celsius.
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
#include "TM1636.h"

//--Declare a TM1636 Class object that control the 4-digit display--//
TM1636 tm1636(7,8);
//-Declare the resistance of the resistor that connects with the temperature sensor-//
#define RESISTOR_CONNECT_THERMISTOR	10000//the resistance is 8k ohm
//-------pin definition of temperature sensor-------------//
#define TEMPERATURE_SENSOR	A0

void setup()
{
	init_pins();
	/*Set the default brightness is BRIGHT_TYPICAL and clear the display*/
	tm1636.init();
}
void loop()
{
	int8_t temperature;
	/*Read the ambient temperature and display on the digital tube.*/
	temperature = getTemperature();
	displayTemperature(temperature);
	delay(500);
}
/*Initialization for the hardware.*/
void init_pins()
{
	/*set the temperature sensor that connects with A0 to be input*/
	pinMode(TEMPERATURE_SENSOR, INPUT);
}
/****************************************************************/
/*Return:int8_t,Temperature that range from -40 to 125 degrees.	*/
int8_t getTemperature()
{
	float temperature,resistance;
	int a;
	a = analogRead(TEMPERATURE_SENSOR);
	resistance   = (float)(1023-a)*RESISTOR_CONNECT_THERMISTOR/a; //Calculate the resistance of the thermistor
	int B = 3975;
	/*Calculate the temperature according to the following formula.*/
	temperature  = 1/(log(resistance/RESISTOR_CONNECT_THERMISTOR)/B+1/298.15)-273.15;
	return (int8_t)temperature;// the type convert from floating point to 8-bit integer
}
/*********************************************************************/
/*Function:Display 8-bit integer temperature on the 4-digit display. */
/*Parameter:-int8_t temperature,Temperature that range from -40 to 125 degrees. */
/*Return:	  void													*/
void displayTemperature(int8_t temperature)
{
	int8_t temp[4];
	if(temperature < 0)//if the temperature is below zero?
	{
	/*Yes, then the left-most bit will display "-".*/
		temp[0] = INDEX_NEGATIVE_SIGN;
		temperature = abs(temperature);
	}
	else if(temperature < 100)//if temperature >= 0 and temperature < 100?
	{
	/*Yes, then the left-most bit will display nothing.*/
		temp[0] = INDEX_BLANK;
	}
	else //if temperature > 100?
	{
	/*Yes, then the left-most bit will normally display.*/
		temp[0] = temperature/100;
	}
	temperature %= 100;
	temp[1] = temperature / 10;//index of second bit from left
	temp[2] = temperature % 10;//index of the third bit from left
	temp[3] = 12;	          //index of 'C' for celsius degree symbol.
	tm1636.display(temp);
}

/*The end of the "MeasureTemperature.ino"*/
