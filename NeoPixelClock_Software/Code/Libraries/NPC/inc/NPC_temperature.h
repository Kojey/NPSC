/**
  ******************************************************************************
  * @file    NPC_temperature.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    15-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			temperature firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_NPC_TEMPERATURE_H_
#define NPC_INC_NPC_TEMPERATURE_H_

/* Includes ------------------------------------------------------------------*/
#include "NPC_utils.h"

/** @addtogroup NPC
  * @{
  */

/** @addtogroup Temperature
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Initialisation function ****************************************************/
void temperature_init(void);
/* Data reading function ******************************************************/
uint16_t temperature_value(void);
int32_t temperature_read(void);
#endif /* NPC_INC_NPC_TEMPERATURE_H_ */

/**
 * 	@}
 */

/**
 * @}
 */
