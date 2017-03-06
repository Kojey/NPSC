/*
 * clock.c
 *
 *  Created on: 06 Mar 2017
 *      Author: Kojey
 */

	/* Make sure that VBAT is connected to an external power supply
		otherwise RTC info will be lost on VDD power off.
		Ideally RTC info should be saved and loaded from an eeprom to
		avoid lost
	*/

#include "../inc/clock.h"

/* Private variables */
RTC_InitTypeDef RTC_InitStruct;
RTC_DateTypeDef RTC_DateStrcut;
RTC_TimeTypeDef RTC_TimeStruct;


uint8_t aShowDate[50] = {0};
/**
 * @brief Initialize the clock, the frequency is set to 1Hz
 */
void clock_init(void){

	// RTC domain access
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); // Power controller
	PWR_BackupAccessCmd(ENABLE); // Backup access

	RCC_HSEConfig(RCC_HSE_ON);
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY)==RESET);
	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div8); // RTC Clock source

	RCC_RTCCLKCmd(ENABLE); // Enable clock
	RTC_WaitForSynchro();

	RTC_InitStruct.RTC_AsynchPrediv = RTC_PREDIV_A;
	RTC_InitStruct.RTC_SynchPrediv = RTC_PREDIV_S;
	RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_24;

	RTC_Init(&RTC_InitStruct);
	/*RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);*/
}

/**
 * @brief Set the date of the clock
 */
ErrorStatus clock_setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year){

	RTC_DateStrcut.RTC_Date = date;
	RTC_DateStrcut.RTC_Month = month;
	RTC_DateStrcut.RTC_WeekDay = weekDay;
	RTC_DateStrcut.RTC_Year = year;

	//RTC_DateStructInit(&RTC_DateStrcut);

	ErrorStatus status = RTC_SetDate(RTC_Format_BCD, &RTC_DateStrcut);

	return status;
}

/**
 * @brief Set the clock's time
 */
ErrorStatus clock_setTime(uint8_t hours, uint8_t minutes, uint8_t second, uint8_t format){

	RTC_TimeStruct.RTC_H12 = format;
	RTC_TimeStruct.RTC_Hours = hours;
	RTC_TimeStruct.RTC_Minutes = minutes;
	RTC_TimeStruct.RTC_Seconds = second;

	//RTC_TimeStructInit(&RTC_TimeStruct);

	return RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);
}

/**
 * @brief Get the date encoded in a 32b format
 * 32b = (8b)weekDay | (8b)date | (8b)month | (8b)year
 */
uint32_t clock_getDate(void){
	RTC_GetDate(RTC_Format_BIN,&RTC_DateStrcut);
	uint32_t weekDay = RTC_DateStrcut.RTC_WeekDay << 24;
	uint32_t date = RTC_DateStrcut.RTC_Date<< 16;
	uint32_t month = RTC_DateStrcut.RTC_Month << 8;
	uint32_t year = RTC_DateStrcut.RTC_Year;
	return (uint32_t) (weekDay|date|month|year);
}

/**
 * @brief Get the time encoded in a 32b format
 * 32b = (8b)hours | (8b)minutes | (8b)seconds | (8b)format
 */
uint32_t clock_getTime(void){
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	uint32_t hours = RTC_TimeStruct.RTC_Hours << 24;
	uint32_t minutes = RTC_TimeStruct.RTC_Minutes << 16;
	uint32_t seconds = RTC_TimeStruct.RTC_Seconds << 8;
	uint32_t format = RTC_TimeStruct.RTC_H12;
	return (uint32_t) (hours|minutes|seconds|format);
}
