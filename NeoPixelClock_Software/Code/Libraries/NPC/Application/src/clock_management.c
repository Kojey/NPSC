/**
  ******************************************************************************
  * @file    clock_mamagement.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    19-March-2017
  * @brief	 comment
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "../inc/clock_management.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Application
 *  @{
 */
/** @defgroup Clock_Management
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**	@defgroup Clock_Management_Eeprom
 * 	@brief	Saving and Loading of clock information
 *
 *
 @verbatim
 ===============================================================================
        ##### Clock Management: Eeprom date, time, and alarm access #####
 ===============================================================================
 @endverbatim
 *
 *	@{
 */

/**
 * @brief	Save an alarm settings to eeprom
 * @param 	Alarm_Def: the alarm setitngs
 * @retval	None
 */
void ClockManagement_saveAlarm(Alarm_Definition * Alarm_Def){

}

/**
 * @brief	Save the time settings to eeprom
 * @param 	Time_Def: the time setitngs
 * @retval	None
 */
void ClockManagement_saveTime(RTC_TimeTypeDef * Time_Def){

}

/**
 * @brief	Save the date settings to eeprom
 * @param 	Date_Def: the date setitngs
 * @retval	None
 */
void ClockManagement_saveDate(RTC_DateTypeDef * Date_Def){

}

/**
 * @brief	load an alarm settings from eeprom
 * @param 	index: the index in memory of the alarm
 * @retval	Alarm_Definition
 */
Alarm_Definition ClockManagement_loadAlarm(uint16_t index){
	Alarm_Definition alarm;
	return alarm;
}

/**
 * @brief	Load the time settings from eeprom
 * @param 	index: the index in memory of the time
 * @retval	RTC_TimeTypeDef
 */
RTC_TimeTypeDef ClockManagement_loadTime(uint16_t index){
	RTC_TimeTypeDef time;
	return time;
}

/**
 * @brief	Load the date settings from eeprom
 * @param 	index: the index in memory of the date
 * @retval	RTC_DateTypeDef
 */
RTC_DateTypeDef ClockManagement_loadDate(uint16_t index){
	RTC_DateTypeDef date;
	return date;
}

/**
 * @}
 */

/**	@defgroup Clock_Management_AlarmComp
 * 	@brief	Comparison between dates, times and alarms
 *
 *
 @verbatim
 ===============================================================================
        ##### Clock Management: Time, Date, and Alarm comparison #####
 ===============================================================================
 @endverbatim
 *
 *	@{
 */

/**
 * @brief	Convert an alarm to an integer
 * @param	alarm
 * @retval	uint32_t representing the alarm
 */
uint32_t  ClockManagement_alarm2int(Alarm_Definition * alarm){
	return 0;
}

/**
 * @brief	Convert a time to an integer
 * @param	time
 * @retval	uint32_t representing the time
 */
uint32_t  ClockManagement_time2int(Alarm_Definition * time){
	return 0;
}


/**
 * @brief	Convert an date to an integer
 * @param	date
 * @retval	uint32_t representing the date
 */
uint32_t  ClockManagement_date2int(Alarm_Definition * date){
	return 0;
}

/**
 * @brief	Compare two alarm
 * @param	alarm1: the reference alarm
 * @param	alarm2
 * @retval	uint32_t representing the time
 */
bool ClockManagement_isAlarmSoonerThan(Alarm_Definition alarm1, Alarm_Definition alarm2){
	return true;
}

/**
 * @}
 */

/**	@defgroup Clock_Management_AlarmUpdate
 * 	@brief	Manages updates of alarms and alarm parameters
 *
 *
 @verbatim
 ===============================================================================
        		##### Clock Management: Updates of alarm  #####
 ===============================================================================
 @endverbatim
 *
 *	@{
 */

/**
 * @brief Update the alarm with the closest alarm
 *
 */
void CLockManagement_updateAlarm(void){

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
