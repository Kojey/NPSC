/**
  ******************************************************************************
  * @file    NPSC_rtc.h
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

#ifndef NPSC_INC_NPSC_RTC_H_
#define NPSC_INC_NPSC_RTC_H_

/* Includes ------------------------------------------------------------------*/
#include "NPSC_utils.h"

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
void rtc_transmission_start(uint8_t direction);
void rtc_transmission_write(uint8_t data);
uint8_t rtc_transmission_read_ack(void);
uint8_t rtc_transmission_read_nack(void);
void rtc_transmission_stop(void);
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
uint8_t rtc_get_seconds(void);
uint8_t rtc_get_minutes(void);
uint8_t rtc_get_hours(void);
uint8_t rtc_get_day(void);
uint8_t rtc_get_date(void);
uint8_t rtc_get_month(void);
uint8_t rtc_get_year(void);
RTC_TimeTypeDef rtc_get_theTime(void);
RTC_DateTypeDef rtc_get_theDate(void);
RTC_ClockTypeDef rtc_get_clock(void);
ErrorStatus rtc_set_seconds(uint8_t);
ErrorStatus rtc_set_minutes(uint8_t);
ErrorStatus rtc_set_hours(uint8_t);
ErrorStatus rtc_set_day(uint8_t);
ErrorStatus rtc_set_date(uint8_t);
ErrorStatus rtc_set_month(uint8_t);
ErrorStatus rtc_set_year(uint8_t);
ErrorStatus rtc_set_theTime(RTC_TimeTypeDef *);
ErrorStatus rtc_set_theDate(RTC_DateTypeDef *);
ErrorStatus rtc_set_clock(RTC_ClockTypeDef *);
/**
 * @}
 */

char * rtc_get_day_string(uint8_t);
char * rtc_get_month_string(uint8_t);

#endif /* NPSC_INC_NPSC_RTC_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
