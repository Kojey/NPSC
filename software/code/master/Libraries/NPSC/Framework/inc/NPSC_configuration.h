/**
  ******************************************************************************
  * @file    NPSC_configuration.h
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

#ifndef NPSC_FRAMEWORK_CONFIGURATION_H_
#define NPSC_FRAMEWORK_CONFIGURATION_H_


/* Includes ------------------------------------------------------------------*/
#include "NPSC_audio.h"
#include "NPSC_bluetooth.h"
#include "NPSC_clock.h"
#include "NPSC_rtc.h"
#include "NPSC_eeprom.h"
#include "NPSC_neopixel.h"
#include "NPSC_nextion.h"
#include "NPSC_temperature.h"

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
void NPSC_init(void);
void Error_Handler(void);

#endif /* NPSC_FRAMEWORK_CONFIGURATION_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**@} */
