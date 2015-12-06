/****************************************************************************/
//  Demo function:Use the three buttons to control four LEDs.
//			Note: K3-menu, K2-increase,K1-decrease
//			Power up: all the LED off
//	Every time the menu key pressed, the status changes from TEST_START
//	to TEST_END or from TEST_END to TEST_START.
//  When it starts, "increase" key can turn on one more LED from right to left
//	every time the "increase" key pressed. 
//	The "decrease" key operation is inverse process of "increase" key's.
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

#include <TimerOne.h>

#define DEBUG 1//comment out if you don't need debug information

//-------pin definition of LEDs---------------//
#define LED_CLOCK_ADJUST	5
#define LED_ALARM_ADJUST	4
#define LED_ALARM_ENABLE	3
#define LED_BRIGHTNESS_ADJUST	2
//-------pin definition of keys---------------//
#define KEY_MENU	11
#define KEY_UP		10
#define KEY_DOWN	9

//------the status of the test---------------//
/*Every time the MENU key pressed, it toggle status between TEST_START and TEST_END	*/
/*When it is TEST_START, it turns to be TESTING if UP key or DOWN key is pressed.*/
uint8_t status;
	#define TEST_END   0 //the LEDs are off
	#define TEST_START 1 //the LEDs blink once per second
	#define TESTING	   2 //UP key or DOWN key can control the LEDs
	
const int LEDS_PIN[] = 
{
	LED_BRIGHTNESS_ADJUST,
	LED_ALARM_ENABLE,
	LED_ALARM_ADJUST,
	LED_CLOCK_ADJUST
};
/*Store ID of highest ranked lit LED.*/
/*eg:If highest ranked lit LED is LED1, LED_on_number is 0.*/
/*	 If it is LED2, LED_on_number is 1 and so on.*/
int8_t LED_on_number = -1;

/*Toggle the status between TEST_START and TEST_END.*/
/*If flag_test_start is 0, the status is TEST_END.*/
/*Otherwise, the status is TEST_START.*/
boolean flag_test_start;//the initial value is 0

/*If flag_all_on is 0,then turn on all LEDs.*/
/*Otherwise, turn off all LEDs.*/
/*Use only when the status is TEST_START.*/
boolean flag_all_on;

void setup()
{
#ifdef DEBUG//if debug message needed, start serial communication
	Serial.begin(9600);
#endif
	/*Initialization for the hardware*/
	init_pins();
	Timer1.initialize(500000); // set a timer of length 500000 microseconds 
	Timer1.attachInterrupt( timer1Isr ); // attach the interrupt service routine to the timer1
}
void loop()
{
	int16_t key_pressed = scanKey();//poll status of all keys
	if(key_pressed == KEY_MENU)
	{
	/*Every time the menu key pressed, it toggle status between TEST_START and TEST_END	*/
		flag_test_start = ~flag_test_start;
		if(flag_test_start)status = TEST_START;
		else status = TEST_END;
	}
	else if(key_pressed == KEY_UP)
	{
	/*When it is TESTING, "UP" key can turn on one more LED from right to left*/
	/*every time the "UP" key pressed. */
		if(status == TEST_START)status = TESTING;
		if(status == TESTING)turnOnMoreLED();
	}
	else if(key_pressed == KEY_DOWN)
	{
	/*When it is TESTING, "DOWN" key can turn off one more LED from left to right*/
	/*every time the "DOWN" key pressed. */
		if(status == TEST_START)status = TESTING;
		if(status == TESTING)turnOffMoreLED();
	}
	/*if a key has been pressed, wait for extra 200ms*/
	if(key_pressed > 0)delay(200);
}
/*Initialization for the hardware,and should be called first*/
void init_pins()
{
	/*set keys to be inputs and define the initial status as HIGH*/
	pinMode(KEY_MENU, INPUT);
	digitalWrite(KEY_MENU, HIGH);
	pinMode(KEY_UP, INPUT);
	digitalWrite(KEY_UP, HIGH);
	pinMode(KEY_DOWN, INPUT);
	digitalWrite(KEY_DOWN, HIGH);
	/*define the pin mode of LEDs*/
	pinMode(LED_CLOCK_ADJUST, OUTPUT);
	pinMode(LED_ALARM_ADJUST, OUTPUT);
	pinMode(LED_BRIGHTNESS_ADJUST, OUTPUT);
	pinMode(LED_ALARM_ENABLE, OUTPUT);
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
	turnOn(LED_CLOCK_ADJUST);
	turnOn(LED_ALARM_ADJUST);
	turnOn(LED_BRIGHTNESS_ADJUST);
	turnOn(LED_ALARM_ENABLE);
}
/*Turn off all the LEDs*/
inline void turnOffAll()
{
	turnOff(LED_CLOCK_ADJUST);
	turnOff(LED_ALARM_ADJUST);
	turnOff(LED_BRIGHTNESS_ADJUST);
	turnOff(LED_ALARM_ENABLE);
}

/*Turn on one more LED*/
void turnOnMoreLED()
{
	if(LED_on_number < 3) //when not all LEDs are on
	{
		LED_on_number ++;
		turnOn(LEDS_PIN[LED_on_number]);
		for(byte i = LED_on_number + 1;i < 4;i ++)
			turnOff(LEDS_PIN[i]);//make sure the higher ranked LEDs are off
	}
}

/*Turn off one more LED*/
void turnOffMoreLED()
{
	if((LED_on_number > 0) || (LED_on_number == 0))//when not all LEDs are off
	{
		turnOff(LEDS_PIN[LED_on_number]);
		LED_on_number --;
	}
}

/*Scan keys and get to know which one is pressed*/
int16_t scanKey()
{
	int16_t pin_number = -1;//define non-existent pin number
	if(digitalRead(KEY_MENU) == LOW)
	{
		delay(20);
		if(digitalRead(KEY_MENU) == LOW)
		{
			pin_number = KEY_MENU;
		}
	#ifdef DEBUG //print out the message on serial monitor
		Serial.println("KEY_MENU is pressed");
	#endif
		
	}
	else if(digitalRead(KEY_UP) == LOW)
	{
		delay(20);
		if(digitalRead(KEY_UP) == LOW)
		{
			pin_number = KEY_UP;
		}
	#ifdef DEBUG
		Serial.println("KEY_UP is pressed");
	#endif
	}
	else if(digitalRead(KEY_DOWN) == LOW)
	{
		delay(20);
		if(digitalRead(KEY_DOWN) == LOW)
		{
			pin_number = KEY_DOWN;
		}
	#ifdef DEBUG
		Serial.println("KEY_DOWN is pressed");
	#endif
	}
	return pin_number;
}
/*Timer one interrupt service routine*/
void timer1Isr()
{
	if(status == TEST_START)
	{
	/*if it start, all the LEDs will blink once a second.*/
		flag_all_on = ~flag_all_on;
		if(flag_all_on)
		{
			LED_on_number = 3;//no more LED to turn on
			turnOnAll();
		}
		else 
		{
			LED_on_number = -1;//no more LED to turn off
			turnOffAll();
		}
	}
	else if(status == TEST_END) 
	{
		turnOffAll();
		LED_on_number = -1;
	}
}
