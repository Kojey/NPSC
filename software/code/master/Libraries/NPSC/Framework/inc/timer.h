/**
  ******************************************************************************
  * @file    timer.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    11-Nov-2017
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

#ifndef NPSC_FRAMEWORK_TIMER_H_
#define NPSC_FRAMEWORK_TIMER_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

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


/* Data reading function ******************************************************/
void timer_init(void);
void TIM5_IRQHandler(void);

#endif /* NPSC_FRAMEWORK_TIMER_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
