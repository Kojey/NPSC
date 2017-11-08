/**
  ******************************************************************************
  * @file    framework.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    17-February-2017
  * @brief   This file contains all the main initialization prototypes used by
  * 			the NPC
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_FRAMEWORK_FRAMEWORK_H_
#define NPSC_FRAMEWORK_FRAMEWORK_H_


/* Includes ------------------------------------------------------------------*/
#include "audio.h"
#include "bluetooth.h"
#include "clock.h"
#include "eeprom.h"
#include "neopixel.h"
#include "nextion.h"
#include "rtc.h"
#include "temperature.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Configuration
  * @{
  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void framework_init(void);
void Error_Handler(void);

#endif /* NPSC_FRAMEWORK_FRAMEWORK_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**@} */
