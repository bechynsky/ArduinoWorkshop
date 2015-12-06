#ifndef TICKTOCKSHIELD_H_
#define TICKTOCKSHIELD_H_

#include "TM1636.h"

#define DS1307_I2C_ADDRESS 0x68

//debug configuration
#define DEBUG 0
//-------pin definition of keys---------------//
#define KEY_MENU	11
#define KEY_UP		10
#define KEY_DOWN	9

//-------pin definition of LEDs---------------//
#define LED_CLOCK_ADJUST	5
#define LED_ALARM_ADJUST	4
#define LED_ALARM_ENABLE	3
#define LED_BRIGHT_ADJUST	2

#define ALARM_BUZZER		6

//-------pin definition of sensors-------------//
#define TEMPERATURE_SENSOR	A0
#define LIGHT_SENSOR		A1

#define LED_ON	1
#define LED_OFF 0

#define HOUR	0
#define MINUTE	1
/*Direction of the LEDs to run*/
#define LEFT_TO_RIGHT 0
#define RIGHT_TO_LEFT 1
//-------Status bit definition of the Status flag----//
/*volatile typedef enum{
  SS_NO_INPUT = 0,//no keys input
  SS_CLOCKH_ADJUST,//adjust the hour of the clock
  SS_CLOCKM_ADJUST,	//adjust the minute of the clock
  SS_ALARMH_ADJUST,	//adjust the hour of the alarm
  SS_ALARMM_ADJUST,	//adjust the minute of the alarm
  SS_ALARM_ENABLE,  //to enable or disable the alarm
  SS_BRIGHT_ADJUST,	//adjust the brightness of the 4-digit display
  SS_CONFIRM_EXIT,  //It will confirm the setting and exit after pressing the MENU button for more than 3s
  					//or after pressing it again at the status of adjust brightness.
  SS_QUIT,			//It will exit without saving any setting if no button is pressed within 5s.
}keyStatusType;*/
//extern keyStatusType system_status;

#define SS_NO_INPUT 		0//no keys input
#define SS_CLOCKH_ADJUST	1//adjust the hour of the clock
#define SS_CLOCKM_ADJUST	2//adjust the minute of the clock
#define SS_ALARMH_ADJUST	3//adjust the hour of the alarm
#define SS_ALARMM_ADJUST	4//adjust the minute of the alarm
#define SS_ALARM_ENABLE  	5//to enable or disable the alarm
#define SS_BRIGHT_ADJUST	6//adjust the brightness of the 4-digit display
#define SS_CONFIRM_EXIT  	7//It will confirm the setting and exit after pressing the MENU button for more than 3s
							 //or after pressing it again at the status of adjust brightness.
#define SS_QUIT				8//It will exit without saving any setting if no button is pressed within 5s.


#define KEY_PRESSED 1
#define KEY_RELEASE 2

#define RESISTOR_CONNECT_THERMISTOR	10000
struct AlarmStruct
{
  byte hour;
  byte minute;
  boolean flag_enable;
};
class TickTockShield
{
public:
  void init();
  void setLed(unsigned char led_status, int pinLED);
  void turnOffLED();
  void turnOnLED();
  void runLED(byte = 1, byte = LEFT_TO_RIGHT);
  int16_t scanKey();
  void processKey();
  void processSystemStatus();
  void quit();
  void saveChanges();
  inline void modifyAlarmFlag();
  void adjustClock(uint8_t hand);
  void adjustAlarm(uint8_t hand);
  void adjustBrightness();
  void adjustBrightness(uint8_t grayscale);
  int8_t getTemperature();
  void displayTemperature(int8_t temperature);
  float getLightIntensity();
  uint8_t getLightLevel();
  void ringOn();
  void ringOff();
  void alarming();
  void turnOffAlarm();
  boolean isAlarmEnable();
  boolean compareWithAlarm();
  inline void alarmDisable();
  void setAlarm(struct AlarmStruct alarm_);
  void setAlarm(uint8_t hour,uint8_t minute,uint8_t = 0);
  void getAlarm();

  void writeToAdjustArea();
  void writeToNormalArea();
  void writeTime();
  void getTime();
  void displayTime();
  void display(int8_t DispData []);
  void clearTime(uint8_t hand);
  byte decToBcd(byte val);
  byte bcdToDec(byte val);
  byte getQuitReq(){return flag_require_quit;}
  boolean isAdjustingTime();
private:
  /*Globle variables in the class*/
  byte g_second, g_minute, g_hour;
  /*when the clock is being adjusted, these two variables save the temporary data.*/
  byte g_minute_temp,g_hour_temp;
  byte g_dayOfWeek;
  byte g_dayOfMonth, g_month, g_year;
  AlarmStruct alarm;
  byte g_brightness;
  byte g_brightness_temp;
  /*when the alarm is being adjusted, this variable save the temporary data.*/
  AlarmStruct alarm_temp;
  int16_t pre_pin_number;//pin number of the key pressed before
  int16_t key_pin_pressed;//pin number of the key pressed now
  uint8_t tempKeyValue;
  uint8_t stateMenu;
  uint8_t stateUp;
  uint8_t stateDown;
  
  uint8_t system_status;
  byte flag_require_quit;
  boolean flag_adjust_time;
  boolean flag_alarm_over;
  
  void keyInit();
  void ledInit();
  void sensorInit();
  void buzzerInit();
};
extern TM1636 tm1636;

#endif
