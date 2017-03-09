/*
 * clock.h
 *
 *  Created on: 06 Mar 2017
 *      Author: Kojey
 */

#ifndef NPC_INC_CLOCK_H_
#define NPC_INC_CLOCK_H_

/* Defines */
// RTC Pre-division for asynchronous and synchronous
#define RTC_PREDIV_A	0x7C //124
#define RTC_PREDIV_S	0X1F3F //7999
// Clock alarm definitions
#define CLOCK_A			RTC_Alarm_A
#define CLOCK_B			RTC_Alarm_B
// AM and PM definition
#define CLOCK_AM				RTC_H12_AM
#define CLOCK_PM				RTC_H12_PM
// Date and Time unit variable definitions
#define CLOCK_WEEKDAY					(uint8_t) (clock_getDate() >> 24)
#define CLOCK_MONTH						(uint8_t) (clock_getDate() >> 16)
#define CLOCK_DATE						(uint8_t) (clock_getDate() >> 8)
#define CLOCK_YEAR						(uint8_t) clock_getDate()
#define CLOCK_HOURS						(uint8_t) (clock_getTime() >> 24)
#define CLOCK_MINUTES					(uint8_t) (clock_getTime() >> 16)
#define CLOCK_SECONDS					(uint8_t) (clock_getTime() >> 8)
#define CLOCK_HOUR_FORMAT				(uint8_t) clock_getTime()

#include "utils.h"

/* Functions Declarations */
void clock_init(void);
ErrorStatus clock_setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year);
ErrorStatus clock_setTime(uint8_t hours, uint8_t minutes, uint8_t second, uint8_t format);
uint32_t clock_getDate(void);
uint32_t clock_getTime(void);
void clock_setAlarm(void);
void RTC_Alarm_IRQHandler(void);
#endif /* NPC_INC_CLOCK_H_ */
