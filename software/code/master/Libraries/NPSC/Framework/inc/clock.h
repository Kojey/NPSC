/**
  ******************************************************************************
  * @file    clock.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    06-March-2017
  * @brief   This file contains all the functions prototypes for the clock firmware
  *          library used for the NPSC.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_FRAMEWORK_CLOCK_H_
#define NPSC_FRAMEWORK_CLOCK_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Clock
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/**
 * @defgroup RTC_PREDIV_Definitions
 * @brief	definition of prescaler for Asynchronous and Synchronous
 * @{
 */
#define RTC_PREDIV_A					0x7C //124
#define RTC_PREDIV_S					0X1F3F //7999
/**
 * @}
 */

/**
 * @defgroup CLOCK_Choice
 * @brief Clock A or B
 * @{
 */
#define CLOCK_A							RTC_Alarm_A
#define CLOCK_B							RTC_Alarm_B
/**
 * @}
 */

/**
 * @defgroup CLOCK_Format
 * @brief AM or PM
 * @{
 */
#define CLOCK_AM						RTC_H12_AM
#define CLOCK_PM						RTC_H12_PM
/**
 * @}
 */

/** @defgroup CLOCK_Value
  *	@brief Access time or date parameters
  * @{
  */
#define CLOCK_WeekDay					(uint8_t) (clock_getDate() >> 24)
#define CLOCK_Date						(uint8_t) (clock_getDate() >> 16)
#define CLOCK_Month						(uint8_t) (clock_getDate() >> 8)
#define CLOCK_Year						(uint8_t) clock_getDate()
#define CLOCK_Hours						(uint8_t) (clock_getTime() >> 24)
#define CLOCK_Minutes					(uint8_t) (clock_getTime() >> 16)
#define CLOCK_Seconds					(uint8_t) (clock_getTime() >> 8)
#define CLOCK_Format					(uint8_t) clock_getTime()
/**
 * @}
 */

/** @defgroup REPEAT_Definitions
  * @brief Alarm repeat options
  * @{
  */

#define REPEAT_NEVER			(uint32_t) RTC_AlarmMask_None
#define REPEAT_DAILY			(uint32_t) RTC_AlarmMask_DateWeekDay
#define REPEAT_WEEKLY			(uint32_t) RTC_AlarmMask_None

/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/*  Function used to set the RTC configuration to the default reset state *****/
/**	@defgroup Clock_Init
 * 	@{
 */
void clock_init(void);
/**
 * @}
 */

/* Time and Date configuration functions **************************************/
  /**@defgroup Clock_Time_Date
   * @{
   */
ErrorStatus clock_setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year);
ErrorStatus clock_setTime( uint8_t am_pm, uint8_t hours, uint8_t minutes, uint8_t second);
uint32_t clock_getDate(void);
uint32_t clock_getTime(void);
ErrorStatus clock_setDateStruct(RTC_DateTypeDef *);
ErrorStatus clock_setTimeStruct(RTC_TimeTypeDef *);
ErrorStatus clock_setClockStruct(RTC_ClockTypeDef *);
RTC_DateTypeDef clock_getDateStruct(void);
RTC_TimeTypeDef clock_getTimeStruct(void);
RTC_ClockTypeDef clock_getClockStruct(void);
/**
 * @}
 */

/* Alarms (Alarm A and Alarm B) configuration functions  **********************/
/** @defgroup Clock_Alarms
 *  @{
 */
RTC_AlarmTypeDef clock_createAlarm(uint8_t am_pm,uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t dateWeekDaySel, uint8_t dateWeekDay, uint32_t repeat);
void clock_setAlarmA(RTC_AlarmTypeDef * Alarm);
void clock_setAlarmB(RTC_AlarmTypeDef * Alarm);
void clock_setAlarm(uint8_t am_pm, uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t dateWeekDaySel, uint8_t dateWeekDay, uint32_t repeat);
void RTC_Alarm_IRQHandler(void);
/**
 * @}
 */

#endif /* NPSC_FRAMEWORK_CLOCK_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
