/**
  ******************************************************************************
  * @file    test_clock_management.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    24-March-2017
  * @brief	 comment
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "test_clock_management.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup clock_management_test
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* Save and Load unit test ****************************************************/

/**	@defgroup clock_management_test_save_lod
 * 	@brief	Save and Load unit test
 *  @{
  */

/**
 * @brief	Unit testing for time save and load
 * @param	None
 * @retval	None
 */
bool test_ClockMangement_save_and_load_time(void){
	RTC_TimeTypeDef time1, time2;
	/*
	 * time:	01:27:20 PM
	 */
	time1.RTC_H12 = CLOCK_PM;
	time1.RTC_Hours = 01;
	time1.RTC_Minutes = 27;
	time1.RTC_Seconds = 20;

	ClockManagement_saveTime(&time1);
	time2 = ClockManagement_loadTime();

	return assertEqual(time1.RTC_H12, time2.RTC_H12)\
			& assertEqual(time1.RTC_Hours, time2.RTC_Hours)\
			& assertEqual(time1.RTC_Minutes, time2.RTC_Minutes)\
			& assertEqual(time1.RTC_Seconds, time2.RTC_Seconds);
}

/**
 * @brief	Unit testing for date save and load
 * @param	None
 * @retval	None
 */
bool test_ClockMangement_save_and_load_date(void){
	RTC_DateTypeDef date1, date2;
	/*
	 * date:	Friday 2017/03/31
	 */
	date1.RTC_Date = 31;
	date1.RTC_Month = RTC_Month_March;
	date1.RTC_WeekDay = RTC_Weekday_Friday;
	date1.RTC_Year = 17;

	ClockManagement_saveDate(&date1);
	date2 = ClockManagement_loadDate();

	return assertEqual(date1.RTC_Date, date2.RTC_Date)\
			& assertEqual(date1.RTC_Month, date2.RTC_Month)\
			& assertEqual(date1.RTC_WeekDay, date2.RTC_WeekDay)\
			& assertEqual(date1.RTC_Year, date2.RTC_Year);
}

/**
 * @brief	Unit testing for alarm save and load
 * @param	None
 * @retval	None
 */
bool test_ClockMangement_save_and_load_alarm(void){
	Alarm_Definition alarm1, alarm2;
	/*
	 * alarm:	"Wake up!!!" 05:00:00 AM everyday
	 */
	// TODO when assigning name to the alarm, the non used space should be filled by a char FOR TESTING ONLY
	strcpy(alarm1.alarmName,"Wake up!!!000000000000000000000");
	alarm1.alarmParameters.RTC_AlarmDateWeekDay = 31;
	alarm1.alarmParameters.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	alarm1.alarmParameters.RTC_AlarmMask = REPEAT_DAILY;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_H12 = CLOCK_AM;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_Hours = 05;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_Minutes = 00;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_Seconds = 00;

	ClockManagement_saveAlarm(&alarm1,ALARM_BASE_ADDRESS);
	alarm2 = ClockManagement_loadAlarm(ALARM_BASE_ADDRESS);
	return assertTrue(strcmp(alarm1.alarmName,alarm2.alarmName))\
			& assertEqual(alarm1.alarmParameters.RTC_AlarmDateWeekDay,alarm2.alarmParameters.RTC_AlarmDateWeekDay )\
			& assertEqual(alarm1.alarmParameters.RTC_AlarmDateWeekDaySel,alarm2.alarmParameters.RTC_AlarmDateWeekDaySel)\
			& assertEqual(alarm1.alarmParameters.RTC_AlarmMask,alarm2.alarmParameters.RTC_AlarmMask)\
			& assertEqual(alarm1.alarmParameters.RTC_AlarmTime.RTC_H12,alarm2.alarmParameters.RTC_AlarmTime.RTC_H12)\
			& assertEqual(alarm1.alarmParameters.RTC_AlarmTime.RTC_Hours,alarm2.alarmParameters.RTC_AlarmTime.RTC_Hours)\
			& assertEqual(alarm1.alarmParameters.RTC_AlarmTime.RTC_Minutes,alarm2.alarmParameters.RTC_AlarmTime.RTC_Minutes)\
			& assertEqual(alarm1.alarmParameters.RTC_AlarmTime.RTC_Seconds,alarm2.alarmParameters.RTC_AlarmTime.RTC_Seconds);
}

/**
 * @}
 */


/* Comparison unit test ****************************************************/

/**	@defgroup clock_management_test_comparison
 * 	@brief	comparison unit test
 *  @{
  */

/**
 * @brief	Unit testing for time comparison
 * @param	None
 * @retval	bool
 */
bool test_ClockMangement_time_comparison(void){
	bool result = true;
	RTC_TimeTypeDef time1, time2;

	/*
	 * time1: 04:51:30 PM
	 * time2: 03:51:30 PM
	 */
	time1.RTC_H12 = CLOCK_PM;
	time1.RTC_Hours = 04;
	time1.RTC_Minutes = 51;
	time1.RTC_Seconds = 30;
	time2.RTC_H12 = CLOCK_PM;
	time2.RTC_Hours = 03;
	time2.RTC_Minutes = 51;
	time2.RTC_Seconds = 30;
	result &= assertFalse(ClockManagement_isTimeBefore(&time1,&time2));

	/*
	 * time1: 02:51:30 PM
	 * time2: 02:55:30 PM
	 */
	time1.RTC_H12 = CLOCK_PM;
	time1.RTC_Hours = 02;
	time1.RTC_Minutes = 51;
	time1.RTC_Seconds = 30;
	time2.RTC_H12 = CLOCK_PM;
	time2.RTC_Hours = 02;
	time2.RTC_Minutes = 55;
	time2.RTC_Seconds = 30;
	result &= assertTrue(ClockManagement_isTimeBefore(&time1,&time2));

	return result;
}

/**
 * @brief	Unit testing for date comparison
 * @param	None
 * @retval	bool
 */
bool test_ClockMangement_date_comparison(void){
	bool result = true;
	RTC_DateTypeDef date1, date2;

	/*
	 * date1: 27-March-17
	 * date2: 25-March-17
	 */
	date1.RTC_Date = 27;
	date1.RTC_Month = RTC_Month_March;
	date1.RTC_WeekDay = RTC_Weekday_Friday;
	date1.RTC_Year = 17;
	date2.RTC_Date = 25;
	date2.RTC_Month = RTC_Month_March;
	date2.RTC_WeekDay = RTC_Weekday_Friday;
	date2.RTC_Year = 17;
	result &= assertFalse(ClockManagement_isDateBefore(&date1,&date2));

	/*
	 * date1: 24-March-17
	 * date2: 24-April-18
	 */
	date1.RTC_Date = 24;
	date1.RTC_Month = RTC_Month_March;
	date1.RTC_WeekDay = RTC_Weekday_Friday;
	date1.RTC_Year = 17;
	date2.RTC_Date = 24;
	date2.RTC_Month = RTC_Month_April;
	date2.RTC_WeekDay = RTC_Weekday_Friday;
	date2.RTC_Year = 18;
	result &= assertTrue(ClockManagement_isDateBefore(&date1,&date2));

	return result;
}


/**
 * @brief	Unit testing for alarm comparison
 * @param	None
 * @retval	bool
 */
bool test_ClockMangement_alarm_comparison(void){

	Alarm_Definition alarm1,alarm2;

	/*
	 * alarm1: 24th 7:40:10 AM
	 * alarm2: 24th 7:40:20 AM
	 */
	strcpy(alarm1.alarmName,"Name of alarm 1");
	alarm1.alarmParameters.RTC_AlarmDateWeekDay = 24;
	alarm1.alarmParameters.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	alarm1.alarmParameters.RTC_AlarmMask = REPEAT_NEVER;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_H12 = CLOCK_AM;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_Hours = 7;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_Minutes = 40;
	alarm1.alarmParameters.RTC_AlarmTime.RTC_Seconds = 10;
	strcpy(alarm2.alarmName,"Name of alarm 1");
	alarm2.alarmParameters.RTC_AlarmDateWeekDay = 24;
	alarm2.alarmParameters.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
	alarm2.alarmParameters.RTC_AlarmMask = REPEAT_NEVER;
	alarm2.alarmParameters.RTC_AlarmTime.RTC_H12 = CLOCK_AM;
	alarm2.alarmParameters.RTC_AlarmTime.RTC_Hours = 7;
	alarm2.alarmParameters.RTC_AlarmTime.RTC_Minutes = 40;
	alarm2.alarmParameters.RTC_AlarmTime.RTC_Seconds = 00;

	return assertTrue(ClockManagement_isAlarmBefore(&alarm1,&alarm2));
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
/**
 * @}
 */
