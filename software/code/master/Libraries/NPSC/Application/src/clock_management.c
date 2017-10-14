/**
  ******************************************************************************
  * @file    clock_management.c
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
#include "clock_management.h"

/** @addtogroup NPSC
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
 * @note	Save in this order: Name, DateWeekDat, DateWeekDaySel, Mask
 * 				H12, Hours, Minutes, Seconds
 * @param 	Alarm_Def: the alarm setitngs
 * @retval	ErrorStatus
 */
ErrorStatus ClockManagement_saveAlarm(Alarm_Definition * Alarm_Def, uint16_t address){
	return (ErrorStatus) (eeprom_writeNBytes(address+OFFSET_NAME,(uint8_t *)(Alarm_Def->alarmName),NAME_SIZE) \
			&& eeprom_write(address+OFFSET_DATEWEEKDAY,Alarm_Def->alarmParameters.RTC_AlarmDateWeekDay)\
			&& eeprom_write4Bytes(address+OFFSET_DATEWEEKDAY_SEL,(uint8_t *)(& Alarm_Def->alarmParameters.RTC_AlarmDateWeekDaySel))\
			&& eeprom_write4Bytes(address+OFFSET_MASK,(uint8_t *)(& Alarm_Def->alarmParameters.RTC_AlarmMask))\
			&& eeprom_write(address+OFFSET_H12,Alarm_Def->alarmParameters.RTC_AlarmTime.RTC_H12)\
			&& eeprom_write(address+OFFSET_HOURS,Alarm_Def->alarmParameters.RTC_AlarmTime.RTC_Hours)\
			&& eeprom_write(address+OFFSET_MINUTES,Alarm_Def->alarmParameters.RTC_AlarmTime.RTC_Minutes)\
			&& eeprom_write(address+OFFSET_SECONDS,Alarm_Def->alarmParameters.RTC_AlarmTime.RTC_Seconds));
}

/**
 * @brief	Save the time settings to eeprom
 * @note	Save H12, Hours, Minutes, and Seconds in
 * 				that order
 * @param 	Time_Def: the time setitngs
 * @retval	ErrorStatus
 */
ErrorStatus ClockManagement_saveTime(RTC_TimeTypeDef * Time_Def){
	return (ErrorStatus)(eeprom_write(TIME_BASE_ADDRESS, Time_Def->RTC_H12)\
			&& eeprom_write(TIME_BASE_ADDRESS+0x01, Time_Def->RTC_Hours)\
			&& eeprom_write(TIME_BASE_ADDRESS+0x02, Time_Def->RTC_Minutes)\
			&& eeprom_write(TIME_BASE_ADDRESS+0x03, Time_Def->RTC_Seconds));
}

/**
 * @brief	Save the date settings to eeprom
 * @note	Save Date, Month, WeekDay, and Year in
 * 				that order
 * @param 	Date_Def: the date setitngs
 * @retval	ErrorStatus
 */
ErrorStatus ClockManagement_saveDate(RTC_DateTypeDef * Date_Def){
	return (ErrorStatus) (eeprom_write(DATE_BASE_ADDRESS, Date_Def->RTC_Date)\
			&& eeprom_write(DATE_BASE_ADDRESS+1, Date_Def->RTC_Month)\
			&& eeprom_write(DATE_BASE_ADDRESS+2, Date_Def->RTC_WeekDay)\
			&& eeprom_write(DATE_BASE_ADDRESS+3, Date_Def->RTC_Year));
}

/**
 * @brief	load an alarm settings from eeprom
 * @note	Load in this order: Name, DateWeekDay, DateWeekDaySel, Mask
 * 				H12, Hours, Minutes, Seconds
 * @param 	index: the index in memory of the alarm
 * @retval	Alarm_Definition
 */
Alarm_Definition ClockManagement_loadAlarm(uint16_t index){
	Alarm_Definition alarm;
	eeprom_readNBytes(index+OFFSET_NAME,(uint8_t *)alarm.alarmName,NAME_SIZE);
	alarm.alarmParameters.RTC_AlarmDateWeekDay = eeprom_read(index+OFFSET_DATEWEEKDAY);
	alarm.alarmParameters.RTC_AlarmDateWeekDaySel = eeprom_read4Bytes(index+OFFSET_DATEWEEKDAY_SEL);
	alarm.alarmParameters.RTC_AlarmMask = eeprom_read4Bytes(index+OFFSET_MASK);
	alarm.alarmParameters.RTC_AlarmTime.RTC_H12 = eeprom_read(index+OFFSET_H12);
	alarm.alarmParameters.RTC_AlarmTime.RTC_Hours = eeprom_read(index+OFFSET_HOURS);
	alarm.alarmParameters.RTC_AlarmTime.RTC_Minutes = eeprom_read(index+OFFSET_MINUTES);
	alarm.alarmParameters.RTC_AlarmTime.RTC_Seconds = eeprom_read(index+OFFSET_SECONDS);
	return alarm;
}

/**
 * @brief	Load the time settings from eeprom
 * @note	Load H12, Hours, Minutes, and Seconds in
 * 				that order
 * @param 	None
 * @retval	RTC_TimeTypeDef
 */
RTC_TimeTypeDef ClockManagement_loadTime(void){
	RTC_TimeTypeDef time;
	time.RTC_H12 = eeprom_read(TIME_BASE_ADDRESS);
	time.RTC_Hours = eeprom_read(TIME_BASE_ADDRESS+0x01);
	time.RTC_Minutes = eeprom_read(TIME_BASE_ADDRESS+0x02);
	time.RTC_Seconds = eeprom_read(TIME_BASE_ADDRESS+0x03);
	return time;
}

/**
 * @brief	Load the date settings from eeprom
 * @note	Load Date, Month, WeekDay, and Year in
 * 				that order
 * @param 	None
 * @retval	RTC_DateTypeDef
 */
RTC_DateTypeDef ClockManagement_loadDate(void){
	RTC_DateTypeDef date;
	date.RTC_Date = eeprom_read(DATE_BASE_ADDRESS);
	date.RTC_Month = eeprom_read(DATE_BASE_ADDRESS+1);
	date.RTC_WeekDay = eeprom_read(DATE_BASE_ADDRESS+2);
	date.RTC_Year = eeprom_read(DATE_BASE_ADDRESS+3);
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
 * @brief	Compare two time
 * @param	is time1 before time2?
 * @retval	bool
 */
bool ClockManagement_isTimeBefore(RTC_TimeTypeDef * time1, RTC_TimeTypeDef * time2){
	// convert to 24h format
	if(time1->RTC_H12 == RTC_H12_PM)time1->RTC_Hours+=12;
	if(time2->RTC_H12 == RTC_H12_PM)time2->RTC_Hours+=12;
	// compare time
	if(time1->RTC_Hours < time2->RTC_Hours)return true;
	else if(time1->RTC_Hours == time2->RTC_Hours)
		if(time1->RTC_Minutes < time2->RTC_Minutes)return true;
		else if(time1->RTC_Minutes == time2->RTC_Minutes)
			if(time1->RTC_Seconds <= time2->RTC_Seconds)
				return true;
			else return false;
		else return false;
	else return false;
}


/**
 * @brief	Convert an date to an integer
 * @param	is date1 before date2?
 * @retval	bool
 */
bool ClockManagement_isDateBefore(RTC_DateTypeDef * date1, RTC_DateTypeDef * date2){
	// compare time
	if(date1->RTC_Year < date2->RTC_Year)return true;
	else if(date1->RTC_Year == date2->RTC_Year)
		if(date1->RTC_Month < date2->RTC_Month)return true;
		else if(date1->RTC_Month == date2->RTC_Month)
			if(date1->RTC_Date <= date2->RTC_Date)
				return true;
			else return false;
		else return false;
	else return false;
}

/**
 * @brief	Compare two alarm
 * @note	Only support same dateWeekDaySel comparison
 * 			TODO include mask comparison
 * @param	is alarm1 before alarm2?
 * @retval	uint32_t representing the time
 */
bool ClockManagement_isAlarmBefore(Alarm_Definition * alarm1, Alarm_Definition * alarm2){
	if(alarm1->alarmParameters.RTC_AlarmDateWeekDay < alarm2->alarmParameters.RTC_AlarmDateWeekDay)return true;
	else if(alarm1->alarmParameters.RTC_AlarmDateWeekDay == alarm2->alarmParameters.RTC_AlarmDateWeekDay)
		if(ClockManagement_isTimeBefore(&alarm1->alarmParameters.RTC_AlarmTime, &alarm1->alarmParameters.RTC_AlarmTime))
				return true;
		else return false;
	else return false;
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
