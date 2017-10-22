/**
  ******************************************************************************
  * @file    clock_management.h
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

/* TODO restrict the alarm application to 2 alarms
	further development will involve having a queue
	of alarms
*/
#ifndef NPSC_APPLICATION_INC_CLOCK_MANAGEMENT_H_
#define NPSC_APPLICATION_INC_CLOCK_MANAGEMENT_H_

/* Includes ------------------------------------------------------------------*/
#include "NPSC_clock.h"
#include "NPSC_eeprom.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Application
 *
 */
/** @addtogroup Clock_Management
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/**
 * @defgroup Clock_management_address
 * @{
 */
#define TIME_BASE_ADDRESS		0x00
#define DATE_BASE_ADDRESS		0x04
#define ALARM_BASE_ADDRESS		0x08
/**
 * @}
 */
/**
 * @defgroup Clock_management_alarm_offset
 * @{
 */
#define OFFSET_NAME				0x00
#define OFFSET_DATEWEEKDAY		NAME_SIZE
#define OFFSET_DATEWEEKDAY_SEL	OFFSET_DATEWEEKDAY + 1
#define OFFSET_MASK				OFFSET_DATEWEEKDAY_SEL + 4
#define OFFSET_H12				OFFSET_MASK + 4
#define OFFSET_HOURS			OFFSET_H12 + 1
#define OFFSET_MINUTES			OFFSET_HOURS + 1
#define OFFSET_SECONDS			OFFSET_MINUTES + 1
/**
 * @}
 */
/**
 * @defgroup Clock_management_constants
 * @{
 */
#define NAME_SIZE	31
/**
 * @}
 */
/* Exported variables --------------------------------------------------------*/
/**
 * @defgroup clock_management variables
 * @{
 */
extern uint16_t eeprom_index;
extern uint16_t next_alarm;	// index of the next non out-dated alarm (@ref Alarm_Definition)
/**
 * @}
 */
/* Exported types ------------------------------------------------------------*/
/**
 * @defgroup type
 * @brief	Alarm type
 * @{
 */
typedef struct {
	char alarmName[NAME_SIZE];
	RTC_AlarmTypeDef alarmParameters;
}Alarm_Definition;
/**
 * @}
 */
/* Exported macro ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Eeprom access  *************************************************************/
/**	@defgroup Clock_Management_Eeprom
 * 	@{
 */
ErrorStatus ClockManagement_saveAlarm(Alarm_Definition * Alarm_Def, uint16_t address);
ErrorStatus ClockManagement_saveTime(RTC_TimeTypeDef * Time_Def);
ErrorStatus ClockManagement_saveDate(RTC_DateTypeDef * Date_Def);
Alarm_Definition ClockManagement_loadAlarm(uint16_t index);
RTC_TimeTypeDef ClockManagement_loadTime(void);
RTC_DateTypeDef ClockManagement_loadDate(void);
/**
 * @}
 */

/* Alarm comparison ***********************************************************/
/**	@defgroup Clock_Management_AlarmComp
 * 	@{
 */
bool ClockManagement_isTimeBefore(RTC_TimeTypeDef * time1, RTC_TimeTypeDef * time2);
bool ClockManagement_isDateBefore(RTC_DateTypeDef * date1, RTC_DateTypeDef * date2);
bool ClockManagement_isAlarmBefore(Alarm_Definition * alarm1, Alarm_Definition * alarm2);
/**
 * @}
 */

/* Alarm update ***************************************************************/
/**	@defgroup Clock_Management_AlarmUpdate
 *  @{
 */
void CLockManagement_updateAlarm(void);
/**
 * @}
 */
#endif /* NPSC_APPLICATION_INC_CLOCK_MANAGEMENT_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
