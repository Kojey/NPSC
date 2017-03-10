/**
  ******************************************************************************
  * @file    clock.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    06-March-2017
  * @brief   This file contains all the functions prototypes for the clock firmware
  *          library used for the NPC.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_CLOCK_H_
#define NPC_INC_CLOCK_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/** @addtogroup NPC
  * @{
  */

/** @addtogroup clock
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/**
 * @defgroup RTC_PREDIV_Definitions for Asynchronous and Synchronous
 * @{
 */
#define RTC_PREDIV_A					0x7C //124
#define RTC_PREDIV_S					0X1F3F //7999
/**
 * @}
 */

/**
 * @defgroup CLOCK_Choice
 * @{
 */
#define CLOCK_A							RTC_Alarm_A
#define CLOCK_B							RTC_Alarm_B
/**
 * @}
 */

/**
 * @defgroup CLOCK_Format
 * @{
 */
#define CLOCK_AM						RTC_H12_AM
#define CLOCK_PM						RTC_H12_PM
/**
 * @}
 */

/** @defgroup CLOCK_Value: Get time or date parameters
  * @{
  */
#define CLOCK_WeekDay					(uint8_t) (clock_getDate() >> 24)
#define CLOCK_Month						(uint8_t) (clock_getDate() >> 16)
#define CLOCK_date						(uint8_t) (clock_getDate() >> 8)
#define CLOCK_Year						(uint8_t) clock_getDate()
#define CLOCK_Hours						(uint8_t) (clock_getTime() >> 24)
#define CLOCK_Minutes					(uint8_t) (clock_getTime() >> 16)
#define CLOCK_seconds					(uint8_t) (clock_getTime() >> 8)
#define CLOCK_Format					(uint8_t) clock_getTime()
/**
 * @}
 */

/** @defgroup REPEAT_Definitions
  * @{
  */
#define REPEAT_DateWeekDay		(uint32_t) RTC_AlarmMask_DateWeekDay
#define REPEAT_Hours			(uint32_t) RTC_AlarmMask_Hours
#define REPEAT_Minutes			(uint32_t) RTC_AlarmMask_Minutes
#define REPEAT_Seconds			(uint32_t) RTC_AlarmMask_Seconds
#define REPEAT_None				(uint32_t) RTC_AlarmMask_None
/**
  * @}
  */


/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/*  Function used to set the RTC configuration to the default reset state *****/
void clock_init(void);

/* Time and Date configuration functions **************************************/
ErrorStatus clock_setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year);
ErrorStatus clock_setTime( uint8_t am_pm, uint8_t hours, uint8_t minutes, uint8_t second);
uint32_t clock_getDate(void);
uint32_t clock_getTime(void);

/* Alarms (Alarm A and Alarm B) configuration functions  **********************/
RTC_AlarmTypeDef clock_createAlarm(uint8_t am_pm,uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t dateWeekDaySel, uint8_t dateWeekDay, uint32_t repeat);
void clock_setA(RTC_AlarmTypeDef * Alarm);
void clock_setAlarm(uint8_t am_pm, uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t dateWeekDaySel, uint8_t dateWeekDay, uint32_t repeat);
void RTC_Alarm_IRQHandler(void);

#endif /* NPC_INC_CLOCK_H_ */

/**
 * @}
 */

/**
 * @}
 */
