/*
 * clock.h
 *
 *  Created on: 06 Mar 2017
 *      Author: Kojey
 */

#ifndef NPC_INC_CLOCK_H_
#define NPC_INC_CLOCK_H_

#define RTC_PREDIV_A	0x7C//124
#define RTC_PREDIV_S	0X1F3F//7999

#define AM				RTC_H12_AM
#define PM				RTC_H12_PM

#include "utils.h"

void clock_init(void);
ErrorStatus clock_setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year);
ErrorStatus clock_setTime(uint8_t hours, uint8_t minutes, uint8_t second, uint8_t format);
uint32_t clock_getDate(void);
uint32_t clock_getTime(void);

#endif /* NPC_INC_CLOCK_H_ */
