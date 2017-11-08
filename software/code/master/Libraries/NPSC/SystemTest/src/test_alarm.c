/**
  ******************************************************************************
  * @file    test_alarm.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    24-March-2017
  * @brief	 This file contains the unit test implementation for the
  * 			external rtc
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "test_alarm.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup test_alarm
  * @brief
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief 	Unit test: Different RTC_ClockTypeDef are written and read from the external
 * 				RTC to check that the time was stored accordingly
 * 				Note that read and write occurs within less than a second
 * @param	None
 * @retval	bool
 */

/**
 * @brief	All address offset should depend on the alarm id
 */
bool test_alarmAddress(){
	AlarmTypeDef alarm;
	alarm.id = 6;
	return assertEqual(alarm_idAddress(alarm.id),alarm.id*ALARM_SIZE)
			&& assertEqual(alarm_repeatAddress(alarm.id),alarm.id*ALARM_SIZE+1)
			&& assertEqual(alarm_enableAddress(alarm.id),alarm.id*ALARM_SIZE+2)
			&& assertEqual(alarm_fetchedAddress(alarm.id),alarm.id*ALARM_SIZE+3)
			&& assertEqual(alarm_ringtoneAddress(alarm.id),alarm.id*ALARM_SIZE+4)
			&& assertEqual(alarm_patternAddress(alarm.id),alarm.id*ALARM_SIZE+5)
			&& assertEqual(alarm_alarmAddress(alarm.id),alarm.id*ALARM_SIZE+6)
			&& assertEqual(alarm_labelAddress(alarm.id),alarm.id*ALARM_SIZE+6+16);
}

/**
 * @brief	Saved alarm and loaded alarm should be the same
 */
bool test_alarmSaveLoad(){
	AlarmTypeDef alarm,_alarm;

	alarm.id=0;
	alarm.repeat=Weekly;
	alarm.enable=false;
	alarm.fetched=true;
	alarm.ringtone=tone1;
	alarm.pattern=pattern1;
	alarm.alarm.RTC_AlarmTime.RTC_H12=RTC_H12_AM;
	alarm.alarm.RTC_AlarmTime.RTC_Hours=10;
	alarm.alarm.RTC_AlarmDateWeekDay=7;
	strcpy(alarm.label,"Wake up KOJEY!!!");

	alarm_save(&alarm);
	_alarm=alarm_load(alarm.id);
	return assertEqual(alarm.id,_alarm.id)
			&& assertEqual(alarm.repeat,_alarm.repeat)
			&& assertEqual(alarm.enable,_alarm.enable)
			&& assertEqual(alarm.fetched,_alarm.fetched)
			&& assertEqual(alarm.ringtone,_alarm.ringtone)
			&& assertEqual(alarm.pattern,_alarm.pattern)
			&& assertEqualArray((uint8_t *)&alarm.alarm,(uint8_t *)&_alarm.alarm,sizeof(RTC_AlarmTypeDef))
			&& assertEqualArray((uint8_t *)&alarm.label,(uint8_t *)&_alarm.label,ALARM_LABEL_SIZE);
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
