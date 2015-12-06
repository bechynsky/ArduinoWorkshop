//  Demo function:Sixteen characters that is 0 to 9 and A b C d E F will flow 
//				from right to left.
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

void setup()
{
	/*Set the default brightness is BRIGHT_TYPICAL and clear the display*/
	tm1636.init();
}
void loop()
{
	int8_t NumTab[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};//index of 0~9,A,b,C,d,E,F
	int8_t table_length;
	table_length = sizeof(NumTab);//get the length of the number table: NumTab
	int8_t disp[4];//store the index of the 4 digit to display. 
	unsigned char digit_index = 0;
	unsigned char starting_index = 0;//starting index of NumTab
	while(1)
	{
		digit_index = starting_index;
		starting_index ++;
		if(starting_index == table_length) 
		{
			starting_index = 0;//start again
		}
		for(unsigned char BitSelect = 0;BitSelect < 4;BitSelect ++)
		{
		  disp[BitSelect] = NumTab[digit_index];
		  digit_index ++;
		  if(digit_index == table_length) digit_index = 0;
		}
		tm1636.display(disp);//display on the 4-digit display.
		delay(300);//display 4-digit number for 300ms and then it will change.
	}
}


/*The end of the file "CharacterFlow.ino"*/
