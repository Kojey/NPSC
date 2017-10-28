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
 * @brief	Save alarm to eeprom
 * @param 	alarm
 */
void alarm_save(AlarmTypeDef * alarm){
	int d=100;
	eeprom_write(alarm_idAddress(alarm->id),alarm->id);
	delay(d);
	eeprom_write(alarm_repeatAddress(alarm->id),alarm->repeat);
	delay(d);
	eeprom_write(alarm_enableAddress(alarm->id),alarm->enable);
	delay(d);
	eeprom_write(alarm_fetchedAddress(alarm->id),alarm->fetched);
	delay(d);
	eeprom_write(alarm_ringtoneAddress(alarm->id),alarm->ringtone);
	delay(d);
	eeprom_write(alarm_patternAddress(alarm->id),alarm->pattern);
	delay(d);
	eeprom_writeNBytes(alarm_alarmAddress(alarm->id),(uint8_t *)&alarm->alarm,sizeof(alarm->alarm));
	delay(d);
	eeprom_writeNBytes(alarm_labelAddress(alarm->id),(uint8_t *)&alarm->label,sizeof(alarm->label));
	delay(d);
}
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
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
