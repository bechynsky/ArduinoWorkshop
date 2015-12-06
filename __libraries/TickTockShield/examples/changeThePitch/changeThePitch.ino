//  Demo function:Use the buttons to adjust the pitch of the buzzer sound.
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

#define DEBUG 1//comment out if you don't need debug information
//-------pin definition of keys---------------//
#define KEY_UP		10
#define KEY_DOWN	9
//-------pin definition of the buzzer--------//
#define ALARM_BUZZER 6

int tempo = 300;

/*play a tone, the larger the tone is, the lower the frequency becomes*/
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(ALARM_BUZZER, HIGH);
    delayMicroseconds(tone);
    digitalWrite(ALARM_BUZZER, LOW);
    delayMicroseconds(tone);
  }
}

void setup() 
{
#ifdef DEBUG
		Serial.begin(9600);
#endif
 	init_pins();
}

void loop() 
{
	static int tone = 1000;
	int16_t key_pressed = scanKey();
	if(KEY_UP == key_pressed)
	{
	/*Every time the menu key pressed, it will raise the pitch of the */
	/*buzzer sound. */
		if(tone > 100)
		tone -= 100;
		playTone(tone,tempo);
	#ifdef DEBUG
		Serial.print("tone");
		Serial.println(tone);
	#endif
	}
	else if(KEY_DOWN == key_pressed)
	{
	/*Every time the menu key pressed, it will lower the pitch of the */
	/*buzzer sound. */
		if(tone < 2000)
		tone += 100;
		playTone(tone,tempo);
	#ifdef DEBUG//output debug message
		Serial.print("tone");
		Serial.println(tone);
	#endif
	}
	/*if a key has been pressed, wait for extra 200ms*/
	if(key_pressed > 0)delay(200);
}
/*Initialization for the keys and the buzzer*/
void init_pins()
{
	/*K1 and K2 are set to be input pins*/
	pinMode(KEY_UP, INPUT);
	digitalWrite(KEY_UP, HIGH);
	pinMode(KEY_DOWN, INPUT);
	digitalWrite(KEY_DOWN, HIGH);
	/*The buzzer is set to be output pin*/
	pinMode(ALARM_BUZZER, OUTPUT);
	digitalWrite(ALARM_BUZZER, LOW);
	
}

/*Scan keys and get to know which one is pressed*/
/*Return: if no key is pressed, return -1.*/
int16_t scanKey()
{
	int16_t pin_number = -1;//define non-existent pin number
	if(digitalRead(KEY_UP) == LOW)
	{
		delay(20);
		if(digitalRead(KEY_UP) == LOW)//validate a press that outlasts 20ms
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

