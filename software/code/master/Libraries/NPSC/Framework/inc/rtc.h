/**
  ******************************************************************************
  * @file    rtc.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    21-Oct-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			rtc firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_FRAMEWORK_RTC_H_
#define NPSC_FRAMEWORK_RTC_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Rtc
  * @brief Rtc framework
  * @{
  */

/* Exported constants --------------------------------------------------------*/
#define RTC_RCC_GPIOX			RCC_AHB1Periph_GPIOB
#define RTC_RCC_I2C				RCC_APB1Periph_I2C1
#define RTC_GPIOX				GPIOB
#define RTC_PIN_SCL				GPIO_Pin_8
#define RTC_PIN_SDA				GPIO_Pin_9
#define RTC_PINSOURCE_SCL		GPIO_PinSource8
#define RTC_PINSOURCE_SDA		GPIO_PinSource9
#define RTC_AF					GPIO_AF_I2C1
#define RTC_I2CX				I2C1

#define RTC_ADDRESS				0x68
#define RTC_ADDRESS_SECONDS		0x00
#define RTC_ADDRESS_MINUTES 	0x01
#define RTC_ADDRESS_HOURS		0x02
#define RTC_ADDRESS_DAY			0x03
#define RTC_ADDRESS_DATE		0x04
#define RTC_ADDRESS_MONTH		0x05
#define RTC_ADDRESS_YEAR 		0x06
#define RTC_ADDRESS_CONTROL 	0X07
#define RTC_ADDRESS_RAM_START 	0X08
#define RTC_ADDRESS_RAM_END 	0X3F


#define RTC_MASK_LOW			0x0F
#define RTC_MASK_HIGH			0xF0

/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint8_t rtc_am_pm;
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

/* Initialisation functions ***************************************************/
/**	@defgroup Rtc_Init Initialisation functions
 * @{
 */
void rtc_init(void);
/**
 * @}
 */

/**	@defgroup Rtc_Init Initialisation functions
 * @{
 */
void rtc_init(void);
/**
 * @}
 */

/**	@defgroup Rtc_Trans RTC transmission functions
 * @{
 */
void rtc_transmissionStart(uint8_t direction);
void rtc_transmissionWrite(uint8_t data);
uint8_t rtc_transmissionReadAck(void);
uint8_t rtc_transmissionReadNack(void);
void rtc_transmissionStop(void);
/**
 * @}
 */

/**	@defgroup Rtc_Data Data transmission
 * @{
 */
void rtc_write(uint8_t address, uint8_t data);
uint8_t rtc_read(uint8_t address);
/**
 * @}
 */

/**	@defgroup Rtc_Set_Get Alarm/Clock
 * @note	Refer to DS1307 datasheet table 2
 * @{
 */
void rtc_get(uint8_t);
uint8_t rtc_getSeconds(void);
uint8_t rtc_getMinutes(void);
uint8_t rtc_getHours(void);
uint8_t rtc_getDay(void);
uint8_t rtc_getDate(void);
uint8_t rtc_getMonth(void);
uint8_t rtc_getYear(void);
RTC_TimeTypeDef rtc_getTimeStruct(void);
RTC_DateTypeDef rtc_getDateStruct(void);
RTC_ClockTypeDef rtc_getClockStruct(void);
ErrorStatus rtc_setSeconds(uint8_t);
ErrorStatus rtc_setMinutes(uint8_t);
ErrorStatus rtc_setHours(uint8_t);
ErrorStatus rtc_setDay(uint8_t);
ErrorStatus rtc_setDate(uint8_t);
ErrorStatus rtc_setMonth(uint8_t);
ErrorStatus rtc_setYear(uint8_t);
ErrorStatus rtc_setTimeStruct(RTC_TimeTypeDef *);
ErrorStatus rtc_setDateStruct(RTC_DateTypeDef *);
ErrorStatus rtc_setClockStruct(RTC_ClockTypeDef *);
/**
 * @}
 */

char * rtc_dayToString(uint8_t);
char * rtc_MonthToString(uint8_t);
uint32_t rtc_weekdaySelTo32Bits(uint8_t);
uint32_t rtc_alarmMaskTo32Bits(uint8_t);
#endif /* NPSC_FRAMEWORK_RTC_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
