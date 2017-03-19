/**
  ******************************************************************************
  * @file    clock_mamagement.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    19-March-2017
  * @brief   This file contains all the application level functions usable
  * 			by the user
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_APPLICATION_INC_CLOCK_MANAGEMENT_H_
#define NPC_APPLICATION_INC_CLOCK_MANAGEMENT_H_

/* Includes ------------------------------------------------------------------*/
#include "../../Framework/inc/NPC_eeprom.h"
#include "../../Framework/inc/NPC_clock.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Application
 *
 */
/** @addtogroup Clock_Management
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/**
 * @defgroup type
 * @brief	Alarm type
 * @{
 */
typedef struct {
	char alarmName[20];
	RTC_AlarmTypeDef alarmParameters;
}Alarm_Definition;
/**
 * @}
 */
/* Exported constants --------------------------------------------------------*/
/**
 * @defgroup Clock_management address
 * @{
 */
#define TIME_ADDRESS		0x00
#define DATE_ADDRESS		0x00
#define ALARM_ADDRESS		0x00
/**
 * @}
 */
/* Exported variables --------------------------------------------------------*/
/**
 * @defgroup clock_management variables
 */
extern uint16_t eeprom_index;
extern uint16_t next_alarm;	// index of the next non out-dated alarm (@ref Alarm_Definition)
/**
 * @}
 */

/* Exported macro ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Eeprom access  *************************************************************/
void ClockManagement_saveAlarm(Alarm_Definition * Alarm_Def);
void ClockManagement_saveTime(RTC_TimeTypeDef * Time_Def);
void ClockManagement_saveDate(RTC_DateTypeDef * Date_Def);
Alarm_Definition ClockManagement_loadAlarm(uint16_t index);
RTC_TimeTypeDef ClockManagement_loadTime(uint16_t index);
RTC_DateTypeDef ClockManagement_loadDate(uint16_t index);

/* Alarm comparison ***********************************************************/
uint32_t  ClockManagement_alarm2int(Alarm_Definition * alarm);
uint32_t  ClockManagement_time2int(Alarm_Definition * time);
uint32_t  ClockManagement_date2int(Alarm_Definition * date);
bool ClockManagement_isAlarmSoonerThan(Alarm_Definition alarm1, Alarm_Definition alarm2);

/* Alarm update ***************************************************************/
void CLockManagement_updateAlarm(void);

#endif /* NPC_APPLICATION_INC_CLOCK_MANAGEMENT_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
