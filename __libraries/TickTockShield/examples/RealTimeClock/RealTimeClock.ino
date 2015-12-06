/****************************************************************************/
//  Demo function:
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

#include "Wire.h"
#include <TimerOne.h>
#include <MsTimer2.h>
#include <EEPROM.h>
#include "TM1636.h"
#include "TickTockShield.h"

#define ON 1
#define OFF 0

//definitions of global variables
boolean flag_update;//1 = update the time on the 4-digit display
unsigned char halfsecond;//each time the timer2 interrupts,halfsecond plus one.
boolean flag_clockpoint = 1;//change between 0 and 1 every 500ms. If it is 1,
						//the clockpoint is on.Else the clockpoint is off.
boolean flag_2s;//2 seconds flag.1 = to the end of 2 seconds so as to set 
				//flag_display_time
boolean flag_10s;//10 seconds flag.1 = to the end of 10 seconds so as to 
				//display temperature
boolean flag_display_time = 1;//1 = can display time that get from the RTC
uint8_t counter_times = 20;//20*halfsecond = 10seconds.
					//If it is 20,to count for 10s,so display time for 10s.
					//If it is 4,to count for 2s,so display the temperture for 2s
boolean flag_500ms_blink;//when adjusting the time or the alarm,the hour or minute
						//displayed on the 4-digit display will blink every 500ms.
boolean flag_scan_again;//1 = can scan key again at the state of SYSTEM_NORAML
						//To avoid the mistake of entering the state of SYSTEM_ADJUSTING 
						//again when pressing MENU for 3s to confirm the setting.
uint8_t counter_500ms;//when counter_500 reach 6,flag_scan_again is set 1.

/*status definitions for the tick shield control system*/
uint8_t system_states;
	#define SYSTEM_NORAML    0 //default status,and the system will turn to "normal" status 
	#define SYSTEM_ADJUSTING 1 //triggered when key MENU is pressed at the "normal" status.
	#define SYSTEM_ALARMING  2

//--Declare a TickTockShield Class object--//
TickTockShield ticktockshield;

extern int8_t disp[4];//external global array defined in TickTockShield.cpp

extern byte g_hand;//external global variable.
					//the clock hand, HOUR shows that it is adjusting the hour, 
				   	//MINUTE shows that it is adjusting the minute.

void setup() 
{
#ifdef DEBUG
	Serial.begin(9600);
#endif
	ticktockshield.init();

	/*Run the 4 LEDs from left to right*/
	ticktockshield.runLED();
	if(isFirstLoad())//if it is the first time to load the firmware?
	{
		ticktockshield.setAlarm(12,0);//Yes,the alarm clock is initialized to 12:00
									//and the data in the EEPROM.
	}
	else ticktockshield.getAlarm();//No,read the alarm clock stored in EEPROM
	/*When system starts, adjust the brightness of the digital tube 
			according to the ambient light intensity.*/
	uint8_t lightlevel; 
	lightlevel = ticktockshield.getLightLevel();
	ticktockshield.adjustBrightness(lightlevel);
	/*Read the ambient temperature and display on the digital tube.*/
	ticktockshield.displayTemperature(ticktockshield.getTemperature());
	delay(1000);
	MsTimer2::set(500, Timer2ISR);//Timer2 generates an interrupt every 500ms
	MsTimer2::start();//Timer2 starts counting
}
void loop() 
{
  clockStart();
}
/****************************************************************/
/*Function:Implement the function of a clock with an alarm clock, and */
/*			the buttons can adjust the clock.*/
void clockStart()
{
  if(system_states == SYSTEM_NORAML)//if it is normal states?
  {
  /*Yes, the clock will update every 500ms,and check whether the Menu is pressed */
  /*to enter SYSTEM_ADJUSTING state and check if it should be enter SYSTEM_ALARMING state.*/
    if(flag_update)//if update flag is not zero?
    { 
      flag_update = 0;
      if(flag_clockpoint)
      {
        tm1636.point(POINT_ON);
      }
      else tm1636.point(POINT_OFF); 
      ticktockshield.getTime();
      if(ticktockshield.isAlarmEnable())
      {
        tm1636.point(POINT_ON);
        ticktockshield.displayTime();
        system_states = SYSTEM_ALARMING;
        return;
      }
      if(flag_display_time)ticktockshield.displayTime();

      if(flag_2s)
      {
        flag_2s = 0;
        flag_display_time = 1;

        counter_times = 20;
        halfsecond = 0;
      }
      if(flag_10s)
      {
        flag_10s = 0;
        flag_display_time = 0;
        tm1636.point(POINT_OFF);
        ticktockshield.displayTemperature(ticktockshield.getTemperature());
        counter_times = 4;
        halfsecond = 0;
      }
      if((flag_scan_again)&&(KEY_MENU == ticktockshield.scanKey()))
      {
        ticktockshield.writeToAdjustArea();
        ticktockshield.processKey();
        system_states = SYSTEM_ADJUSTING;
      }

    }
  }
  else if(system_states == SYSTEM_ADJUSTING)
  {
    ticktockshield.scanKey();
    ticktockshield.processKey();
    ticktockshield.processSystemStatus();
    if(ticktockshield.getQuitReq())
    {
      system_states = SYSTEM_NORAML;
      counter_500ms = 0;
      flag_scan_again = 0;
    }
    else flag_scan_again = 1;
  }
  else if(system_states == SYSTEM_ALARMING)
  {
    /*It will sound alarm for a minute untill the "MENU" key is pressed*/
    if(ticktockshield.isAlarmEnable())
    {
      ticktockshield.alarming();
    }
    else 
    {
      ticktockshield.turnOffAlarm();
      system_states = SYSTEM_NORAML;
    }
    if(KEY_MENU == ticktockshield.scanKey())
    {
      ticktockshield.turnOffAlarm();
      system_states = SYSTEM_NORAML;
    }
  }
}

//--------------------------------------
boolean isFirstLoad()
{
  unsigned char mark[] = "ALARM";
  unsigned char temp_data[5];
  for(unsigned char i = 0;i < 5;i ++)
  {
    temp_data[i] = EEPROM.read(i);
    if(temp_data[i] != mark[i])
    {
      EEPROM.write(0,mark[0]);
      EEPROM.write(1,mark[1]);
      EEPROM.write(2,mark[2]);
      EEPROM.write(3,mark[3]);
      EEPROM.write(4,mark[4]);
      return true;
    }
  }
  return false;
}

/*Function:It is timer 2 interrupt service routine.Timer2 generates an interrupt*/ 
/*  every 500ms.And every time it interrupts,this function will be executed.*/		
void Timer2ISR()
{
  halfsecond ++;
  if(halfsecond  == counter_times)
  {
    halfsecond  = 0;
    if(counter_times == 4)flag_2s = 1;
    else if(counter_times == 20)flag_10s = 1;
  }
  flag_update = 1;
  flag_clockpoint = (~flag_clockpoint) & 0x01;//change between 0 and 1 every 500ms.
  flag_500ms_blink = ~flag_500ms_blink;
  if(ticktockshield.isAdjustingTime())
  {
    if(g_hand == HOUR)
    {
      if(flag_500ms_blink)
      {
        disp[0] = INDEX_BLANK;
        disp[1] = INDEX_BLANK;
      }
    }
    else
    {
      if(flag_500ms_blink)
      {
        disp[2] = INDEX_BLANK;
        disp[3] = INDEX_BLANK;
      }
    }
    tm1636.display(disp);
  }
  counter_500ms ++;
  if(counter_500ms == 6)
  {
    counter_500ms = 0;
    flag_scan_again = 1;
  }

}



