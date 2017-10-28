/**
  ******************************************************************************
  * @file    clock_test.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    24-March-2017
  * @brief	 This file contains the unit test implementation for the
  * 			internal clock
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <clock_test.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup clock_test
  * @brief
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief 	Unit test for date save and load
 * @param	None
 * @retval	bool
 */
bool test_clock_date(void){
	/*
	 * Friday 24-March-17
	 */
	uint8_t weekday = RTC_Weekday_Friday;
	uint8_t month = RTC_Month_March;
	uint8_t date = 24;
	uint8_t year = 17;
	clock_setDate(weekday, month, date, year);

	return assertEqual(weekday,CLOCK_WeekDay)\
			& assertEqual(month,CLOCK_Month)\
			& assertEqual(date, CLOCK_Date)\
			& assertEqual(year, CLOCK_Year);
}

/**
 * @brief 	Unit test for time save and load
 * @param	None
 * @retval	bool
 */
bool test_clock_time(void){
	/*
	 * 12:42:45 PM
	 */
	uint8_t h12 = RTC_H12_PM;
	uint8_t hours = 12;
	uint8_t minutes = 42;
	uint8_t seconds = 45;
	clock_setTime(h12,hours,minutes,seconds);

	return assertEqual(h12,CLOCK_Format)\
			& assertEqual(hours,CLOCK_Hours)\
			& assertEqual(minutes, CLOCK_Minutes)\
			& assertEqual(seconds, CLOCK_Seconds);
}

/**
 * @brief 	Unit test for alarm save and load
 * @param	None
 * @retval	bool
 */
bool test_clock_alarm(void){
	RTC_AlarmTypeDef alarm1, alarm2;

	alarm1.RTC_AlarmDateWeekDay = 24;
	alarm1.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	alarm1.RTC_AlarmMask = REPEAT_Hours;
	alarm1.RTC_AlarmTime.RTC_H12 = RTC_H12_PM;
	alarm1.RTC_AlarmTime.RTC_Hours = 2;
	alarm1.RTC_AlarmTime.RTC_Minutes = 11;
	alarm1.RTC_AlarmTime.RTC_Seconds = 50;

	clock_setAlarmA(&alarm1);

	RTC_GetAlarm(RTC_Format_BIN,RTC_Alarm_A,&alarm2);

	return assertEqual(alarm1.RTC_AlarmDateWeekDay, alarm2.RTC_AlarmDateWeekDay)\
			& assertEqual(alarm1.RTC_AlarmDateWeekDaySel, alarm2.RTC_AlarmDateWeekDaySel)\
			& assertEqual(alarm1.RTC_AlarmMask, alarm2.RTC_AlarmMask)\
			& assertEqual(alarm1.RTC_AlarmTime.RTC_H12, alarm2.RTC_AlarmTime.RTC_H12)\
			& assertEqual(alarm1.RTC_AlarmTime.RTC_Hours, alarm2.RTC_AlarmTime.RTC_Hours)\
			& assertEqual(alarm1.RTC_AlarmTime.RTC_Minutes, alarm2.RTC_AlarmTime.RTC_Minutes)\
			& assertEqual(alarm1.RTC_AlarmTime.RTC_Seconds, alarm2.RTC_AlarmTime.RTC_Seconds);
}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
