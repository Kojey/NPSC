/**
  ******************************************************************************
  * @file    alarm.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    28-Oct-2017
  * @brief   This file contains method for managing the application
  * 			received from the on-board touch screen and the bluetooth
  * 			device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "alarm.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Application
 *  @{
 */
/** @defgroup Application
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
 * @brief	Synchronize internal alarm to external alarm
 */
void alarm_synchronize(void){
	if(timer_start){
		RTC_ClockTypeDef clock = rtc_getClockStruct();
		clock_setClockStruct(&clock);
		timer_start=false;
	}
}
/**
 * @brief	Save alarm to memory
 * @param 	alarm
 */
void alarm_save(AlarmTypeDef * alarm){
	eeprom_write(alarm_idAddress(alarm->id),alarm->id);
	eeprom_write(alarm_repeatAddress(alarm->id),alarm->repeat);
	eeprom_write(alarm_enableAddress(alarm->id),alarm->enable);
	eeprom_write(alarm_fetchedAddress(alarm->id),alarm->fetched);
	eeprom_write(alarm_ringtoneAddress(alarm->id),alarm->ringtone);
	eeprom_write(alarm_patternAddress(alarm->id),alarm->pattern);
	eeprom_writeNBytes(alarm_alarmAddress(alarm->id),(uint8_t *)&alarm->alarm,sizeof(alarm->alarm));
	eeprom_writeNBytes(alarm_labelAddress(alarm->id),(uint8_t *)&alarm->label,sizeof(alarm->label));
}
/**
 * @brief	Load an alarm from memory
 * @param	index: alarm index
 */
AlarmTypeDef alarm_load(uint8_t index){
	AlarmTypeDef alarm;
	alarm.id=eeprom_read(alarm_idAddress(index));
	alarm.repeat=eeprom_read(alarm_repeatAddress(index));
	alarm.enable=eeprom_read(alarm_enableAddress(index));
	alarm.fetched=eeprom_read(alarm_fetchedAddress(index));
	alarm.ringtone=eeprom_read(alarm_ringtoneAddress(index));
	alarm.pattern=eeprom_read(alarm_patternAddress(index));
	eeprom_readNBytes(alarm_alarmAddress(index),(uint8_t *)&alarm.alarm,sizeof(alarm.alarm));
	eeprom_readNBytes(alarm_labelAddress(index),(uint8_t *)&alarm.label,sizeof(alarm.label));
	return alarm;
}
/**
 * @brief	Update alarm A and B
 * @param	updated
 */
void alarm_update(bool updated){
	if(updated){
		uint8_t index_a,index_b;
		RTC_AlarmTypeDef alarm_a,alarm_b;
		// get the two most close alarm
		index_a = 0;
		index_b = 1;
		// update alarm
		alarm_a = alarm_load(index_a).alarm;
		alarm_b = alarm_load(index_b).alarm;
		clock_setAlarmA(&alarm_a);
		clock_setAlarmB(&alarm_b);
	}
}

/****************
 *
 */

uint16_t alarm_idAddress(uint8_t id){
	 return id*ALARM_SIZE;
}
uint16_t alarm_repeatAddress(uint8_t id){
	return alarm_idAddress(id)+sizeof(uint8_t);
}
uint16_t alarm_enableAddress(uint8_t id){
	return alarm_repeatAddress(id)+sizeof(Alarm_repeat);
}
uint16_t alarm_fetchedAddress(uint8_t id){
	return alarm_enableAddress(id)+sizeof(bool);
}
uint16_t alarm_ringtoneAddress(uint8_t id){
	return alarm_fetchedAddress(id)+sizeof(bool);
}
uint16_t alarm_patternAddress(uint8_t id){
	return alarm_ringtoneAddress(id)+sizeof(Ringtone);
}
uint16_t alarm_alarmAddress(uint8_t id){
	return alarm_patternAddress(id)+sizeof(Pattern);
}
uint16_t alarm_labelAddress(uint8_t id){
	return alarm_alarmAddress(id)+sizeof(RTC_AlarmTypeDef);
}


/**
 * @brief
 */
char * alarm_repeatToString(Alarm_repeat repeat){
	switch (repeat) {
		case Never:return "Never";break;
		case Daily:return "Daily";break;
		case Weekly:return "Weekly";break;
		default:return "Error";break;
	}
}

char * alarm_ringToneToString(Ringtone ringtone){
	switch (ringtone) {
		case tone1:return "tone1";break;
		case tone2:return "tone2";break;
		case tone3:return "tone3";break;
		default:return "Error";	break;
	}
}

char * alarm_patternToString(Pattern pattern){
	switch (pattern) {
		case pattern1:return "pattern1";break;
		case pattern2:return "pattern2";break;
		case pattern3:return "pattern3";break;
		case pattern4:return "pattern4";break;
		case pattern5:return "pattern5";break;
		case Hour_Minute_Second:return "Hour_Minute_Second";break;
		default:return "Error";break;
	}
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
