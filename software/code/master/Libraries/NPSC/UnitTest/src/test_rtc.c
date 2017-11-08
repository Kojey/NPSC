/**
  ******************************************************************************
  * @file    test_rtc.c
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
#include "../../UnitTest/inc/test_rtc.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup rtc_test
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
bool test_rtc_clock(){

	/*
	 * Wednesday, 25th October, 2017 6:4:20
	 */
	// set clock to Wednesday, 25th October, 2017 6:4:20
	RTC_ClockTypeDef clock;
	clock.time.RTC_Seconds=20;
	clock.time.RTC_Minutes=8;
	clock.time.RTC_Hours=6;
	clock.date.RTC_WeekDay=RTC_Weekday_Wednesday;
	clock.date.RTC_Date=25;
	clock.date.RTC_Month=10;
	clock.date.RTC_Year=17;
	rtc_setClockStruct(&clock);
	// get clock from external RTC
	delay(10000);
	RTC_ClockTypeDef _clock;
	_clock = rtc_getClockStruct();
	bool result1 =  assertEqual(clock.time.RTC_Minutes,_clock.time.RTC_Minutes)
						&& assertEqual(clock.time.RTC_Hours,_clock.time.RTC_Hours)
						&& assertEqual(clock.date.RTC_WeekDay,_clock.date.RTC_WeekDay)
						&& assertEqual(clock.date.RTC_Date,_clock.date.RTC_Date)
						&& assertEqual(clock.date.RTC_Month,_clock.date.RTC_Month)
						&& assertEqual(clock.date.RTC_Year,_clock.date.RTC_Year);


	// set clock to Wednesday, 8th November, 2017 16:0:0
	clock.time.RTC_Seconds=0;
	clock.time.RTC_Minutes=0;
	clock.time.RTC_Hours=16;
	clock.date.RTC_WeekDay=RTC_Weekday_Wednesday;
	clock.date.RTC_Date=8;
	clock.date.RTC_Month=16;
	clock.date.RTC_Year=17;
	rtc_setClockStruct(&clock);
	// get clock from external RTC
	delay(10000);
	_clock = rtc_getClockStruct();
	bool result2 = assertEqual(clock.time.RTC_Minutes,_clock.time.RTC_Minutes)
						&& assertEqual(clock.time.RTC_Hours,_clock.time.RTC_Hours)
						&& assertEqual(clock.date.RTC_WeekDay,_clock.date.RTC_WeekDay)
						&& assertEqual(clock.date.RTC_Date,_clock.date.RTC_Date)
						&& assertEqual(clock.date.RTC_Month,_clock.date.RTC_Month)
						&& assertEqual(clock.date.RTC_Year,_clock.date.RTC_Year);
	return result1 && result2;
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
