/**
  ******************************************************************************
  * @file    alarm.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    28-Oct-2017
  * @brief   This file contains method for managing the applications
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

#ifndef NPSC_APPLICATION_ALARM_H_
#define NPSC_APPLICATION_ALARM_H_

/* Includes ------------------------------------------------------------------*/
#include "rtc.h"
#include "clock.h"
#include "eeprom.h"
/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Application
 *
 */
/** @addtogroup Alarm
  * @{
  */


/* Exported constants --------------------------------------------------------*/

#define ALARM_LABEL_SIZE			10
#define ALARM_SIZE					60	// size of AlarmTypeDef

/* Exported variables --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

// Alarm type definition
typedef struct {
	uint8_t id;
	Alarm_repeat repeat;	// daily or weekly or never
	bool enable;
	bool fetched;	// is this alarm in one of the alarms (Alarm_A or Alarm_B)?
	Ringtone ringtone;
	Pattern pattern;
	RTC_AlarmTypeDef alarm;
	char label[ALARM_LABEL_SIZE];
} AlarmTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/


void alarm_save(AlarmTypeDef *);
AlarmTypeDef alarm_load(uint8_t);

uint16_t alarm_idAddress(uint8_t);
uint16_t alarm_repeatAddress(uint8_t);
uint16_t alarm_enableAddress(uint8_t);
uint16_t alarm_fetchedAddress(uint8_t);
uint16_t alarm_ringtoneAddress(uint8_t);
uint16_t alarm_patternAddress(uint8_t);
uint16_t alarm_alarmAddress(uint8_t);
uint16_t alarm_labelAddress(uint8_t);


char * alarm_repeatToString(Alarm_repeat);
char * alarm_ringToneToString(Ringtone);
char * alarm_patternToString(Pattern);
#endif /* NPSC_APPLICATION_ALARM_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
