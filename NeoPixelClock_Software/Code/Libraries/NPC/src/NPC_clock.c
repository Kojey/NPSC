/**
  ******************************************************************************
  * @file    clock.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    06-March-2017
  * @brief   This file provides firmware functions to manage the Date, Time and Alarm
  * 			of the NPC clock
  *
@verbatim

 ===================================================================
                  ##### Note on VBat and VDD #####
 ===================================================================
 [..]
	(+)	Make sure that VBAT is connected to an external power supply
		otherwise RTC info will be lost on VDD power off.
		Ideally RTC info should be saved and loaded from an EEPROM or
		SD card to avoid lost

                  ##### How to use Clock Driver #####
 ===================================================================
 [..]
   (+) Initialize the Clock using clock_init()
   (+) Set the Date using clock_setDate(...)
   (+) Set the Time using clock_setTime(...)
   (+) Set the Alarm using clock_setAlarm(...)

@endverbatim

  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "../inc/NPC_clock.h"


/** @addtogroup NPC
  * @{
  */

/** @defgroup Clock
  * @brief clock driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
RTC_TimeTypeDef RTC_TimeStruct;
RTC_InitTypeDef RTC_InitStruct;
RTC_DateTypeDef RTC_DateStrcut;
RTC_AlarmTypeDef RTC_AlarmStruct;
EXTI_InitTypeDef EXTI_InitStruct;

/* Private functions ---------------------------------------------------------*/

/**	@defgroup Clock initialization functions
 * 	@brief	Clock initialization functions
 *
@verbatim
 ===============================================================================
         ##### Clock initialization functions #####
 ===============================================================================

 [..] This section provide functions allowing to initialize the clock.

@endverbatim
  * @{
  */

/**
 * @brief	Initialize the clock to 1Hz and setup peripherals for Alarm
 * @param	None
 * @retval	None
 */
void clock_init(void){

	/* RTC domain access */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); // Power controller
	PWR_BackupAccessCmd(ENABLE); // Backup access

	RCC_RTCCLKConfig(RCC_RTCCLKSource_HSE_Div8); // RTC Clock source

	RCC_RTCCLKCmd(ENABLE); // Enable clock
	RTC_WaitForSynchro();

	/* Set clock frequency to 1Hz */
	{
		RTC_InitStruct.RTC_AsynchPrediv = RTC_PREDIV_A;
		RTC_InitStruct.RTC_SynchPrediv = RTC_PREDIV_S;
		RTC_InitStruct.RTC_HourFormat = RTC_HourFormat_12;
		RTC_Init(&RTC_InitStruct);
	}

	/* EXTI configuration */
	{
		EXTI_ClearITPendingBit(EXTI_Line17);
		EXTI_InitStruct.EXTI_Line = EXTI_Line17;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStruct);
	}
	/* Enable Alarm interrupt */
	{
		NVIC_InitTypeDef NVIC_InitStruct;
		NVIC_InitStruct.NVIC_IRQChannel = RTC_Alarm_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
	}
}
/**
 * @}
 */

/**	@defgroup Clock Time and Date Configuration functions
 * 	@brief	Time and date configuration functions
 *
@verbatim
 ===============================================================================
         ##### Clock configuration functions #####
 ===============================================================================

 [..] This section provide functions allowing to program and read the RTC Clock information.

@endverbatim
  * @{
  * */

/**
 * @brief	Set the clock's date
 * @param	None
 * @retval	An ErrorStatus representing the outcome of the operation
 *				- SUCCESS: RTC Shift registers are configured
 *          	- ERROR: RTC Shift registers are not configured
 */
ErrorStatus clock_setDate(uint8_t weekDay, uint8_t month, uint8_t date, uint8_t year){

	RTC_DateStrcut.RTC_Date = date;
	RTC_DateStrcut.RTC_Month = month;
	RTC_DateStrcut.RTC_WeekDay = weekDay;
	RTC_DateStrcut.RTC_Year = year;

	return RTC_SetDate(RTC_Format_BIN, &RTC_DateStrcut);
}

/**
 * @brief	Set the clock's time
 * @param	None
 * @retval	An ErrorStatus representing the outcome of the operation
 *				- SUCCESS: RTC Shift registers are configured
 *          	- ERROR: RTC Shift registers are not configured
 */
ErrorStatus clock_setTime(uint8_t am_pm, uint8_t hours, uint8_t minutes, uint8_t second){

	RTC_TimeStruct.RTC_H12 = am_pm;
	RTC_TimeStruct.RTC_Hours = hours;
	RTC_TimeStruct.RTC_Minutes = minutes;
	RTC_TimeStruct.RTC_Seconds = second;

	return RTC_SetTime(RTC_Format_BIN, &RTC_TimeStruct);
}

/**
 * @brief	Get the date encoded in a 32b format
 * @param	None
 * @retval	An uint32_t containing the weekDay as its MB3, date : MB2, month : MB1, year : MB0
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
 * @brief	Get the time encoded in a 32b format
 * @param	None
 * @retval	An uint32_t containing the hour as its MB3, minutes : MB2, Seconds : MB1, format : MB0
 */
uint32_t clock_getTime(void){
	RTC_GetTime(RTC_Format_BIN,&RTC_TimeStruct);
	uint32_t hours = RTC_TimeStruct.RTC_Hours << 24;
	uint32_t minutes = RTC_TimeStruct.RTC_Minutes << 16;
	uint32_t seconds = RTC_TimeStruct.RTC_Seconds << 8;
	uint32_t format = RTC_TimeStruct.RTC_H12;
	return (uint32_t) (hours|minutes|seconds|format);
}
/**
 * @}
 */

/** @defgroup Clock Alarms configuration functions
 *  @brief   Alarm configuration functions
 *
@verbatim
 ===============================================================================
         ##### Alarm configuration functions #####
 ===============================================================================

 [..] This section provide functions allowing to program and read the RTC Alarms.

@endverbatim
  * @{
  */

/**
 * @brief	Create an Alarm Structure given all the parameters
 * @param 	am_pm: 	AM PM format (CLOCK_AM)
 * @param	hours: 	Alarm hours
 * @param	minutes: Alarm minutes
 * @param	seconds: Alarm seconds
 * @param	dateWeekDaySel: Date of WeekDay selection  @ref RTC_AlarmDateWeekDay_Definitions
 * @param	dateWeekDay:	Specify Alarm Date/Weekday if Date then value range from 1-31, else @ref RTC_WeekDay_Definitions
 * @param	repeat: Specify the repetition of the Alarm
 * @retval	An RTC_AlarmTypeDef containing all the parameters above
 */
RTC_AlarmTypeDef clock_createAlarm(uint8_t am_pm,uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t dateWeekDaySel, uint8_t dateWeekDay, uint32_t repeat){
	RTC_AlarmTypeDef Alarm_Struct;
	/* Time definition */
	Alarm_Struct.RTC_AlarmTime.RTC_Hours = hours;
	Alarm_Struct.RTC_AlarmTime.RTC_Minutes = minutes;
	Alarm_Struct.RTC_AlarmTime.RTC_Seconds= seconds;
	Alarm_Struct.RTC_AlarmTime.RTC_H12 = am_pm;
	/* Date definition */
	Alarm_Struct.RTC_AlarmDateWeekDaySel = dateWeekDaySel;
	Alarm_Struct.RTC_AlarmDateWeekDay = dateWeekDay;
	/* Repetition */
	Alarm_Struct.RTC_AlarmMask = repeat;

	return Alarm_Struct;
}

/**
 * @brief	Set an alarm to RTC_Alarm_A, given a Alarm structure @ref RTC_AlarmTypeDef
 * @param 	Alarm:	A pointer to the RTC_AlarmTypeDef
 * @retval	None
 */
void clock_setA(RTC_AlarmTypeDef * Alarm){
	RTC_AlarmCmd(RTC_Alarm_A,DISABLE);
	RTC_SetAlarm(RTC_Format_BIN,RTC_Alarm_A,Alarm);
	RTC_ITConfig(RTC_IT_ALRA,ENABLE);
	RTC_AlarmCmd(CLOCK_A,ENABLE);
	RTC_ClearFlag(RTC_FLAG_ALRAF);
}

/**
 * @brief	Set an alarm to RTC_Alarm_A, given all the alarm parameters
 * @param 	am_pm: 	AM PM format (CLOCK_AM)
 * @param	hours: 	Alarm hours
 * @param	minutes: Alarm minutes
 * @param	seconds: Alarm seconds
 * @param	dateWeekDaySel: Date of WeekDay selection  @ref RTC_AlarmDateWeekDay_Definitions
 * @param	dateWeekDay:	Specify Alarm Date/Weekday if Date then value range from 1-31, else @ref RTC_WeekDay_Definitions
 * @param	repeat: Specify the repetition of the Alarm
 * @retval	None
 */
void clock_setAlarm(uint8_t am_pm,uint8_t hours, uint8_t minutes, uint8_t seconds, uint32_t dateWeekDaySel, uint8_t dateWeekDay, uint32_t repeat){

	RTC_AlarmCmd(RTC_Alarm_A,DISABLE); // Reset alarm A

	/* Update Alarm Structure */
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Hours = hours;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Minutes = minutes;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_Seconds = seconds;
	RTC_AlarmStruct.RTC_AlarmTime.RTC_H12 = am_pm;
	RTC_AlarmStruct.RTC_AlarmDateWeekDaySel = dateWeekDaySel;
	RTC_AlarmStruct.RTC_AlarmDateWeekDay = dateWeekDay;
	RTC_AlarmStruct.RTC_AlarmMask = repeat;

	/* Set Alarm and Interrupts */
	RTC_SetAlarm(RTC_Format_BIN,CLOCK_A,&RTC_AlarmStruct);
	RTC_ITConfig(RTC_IT_ALRA,ENABLE);
	RTC_AlarmCmd(CLOCK_A,ENABLE);
	RTC_ClearFlag(RTC_FLAG_ALRAF);
}

/**
 * @brief	Alarm Handler
 * @param	None
 * @retval	None
 */

void RTC_Alarm_IRQHandler(void){
	/* ALARM A Detection */
	while(RTC_GetITStatus(RTC_IT_ALRA)==RESET);	// Wait for Alarm A event
	RTC_ClearITPendingBit(RTC_IT_ALRA);			// Clear Alarm A interrupt pending bit
	EXTI_ClearITPendingBit(EXTI_Line17);		// Clear External Interrupt pending bit

	/* TODO What need to be done when Alarm event occurs*/
	GPIO_ToggleBits(GPIOD, GPIO_Pin_13);
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
