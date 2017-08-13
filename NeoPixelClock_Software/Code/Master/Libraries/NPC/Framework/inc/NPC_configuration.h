/**
  ******************************************************************************
  * @file    NPC_configuration.h
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

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_


/* Includes ------------------------------------------------------------------*/
#include "NPC_bluetooth.h"
#include "NPC_clock.h"
#include "NPC_neopixel.h"
#include "NPC_audio.h"
#include "NPC_eeprom.h"
#include "NPC_temperature.h"

/** @addtogroup NPC
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
void NPC_init(void);
void Error_Handler(void);

#endif /* CONFIGURATION_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**@} */
