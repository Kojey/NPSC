/**
  ******************************************************************************
  * @file    NPSC_temperature.h
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

#ifndef NPSC_FRAMEWORK_TEMPERATURE_H_
#define NPSC_FRAMEWORK_TEMPERATURE_H_

/* Includes ------------------------------------------------------------------*/
#include "NPSC_utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
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
/** @defgroup Temperature_Init Initialise the temperature reader
 * @{
 */
void temperature_init(void);
/**
 * @}
 */

/* Data reading function ******************************************************/
/** @defgroup Temperature_Data
 *  @{
 */
uint16_t temperature_value(void);
int32_t temperature_read(void);
/**
 * @}
 */

#endif /* NPSC_FRAMEWORK_TEMPERATURE_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
