/**
  ******************************************************************************
  * @file    visual.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    28-Oct-2017
  * @brief   This file contains method for managing the visuals
  * 			received from the on-board touch screen and the bluetooth
  * 			device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_APPLICATION_VISUAL_H_
#define NPSC_APPLICATION_VISUAL_H_

/* Includes ------------------------------------------------------------------*/
#include <neopixel_ring.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Visual
 *
 */
/** @addtogroup Visual
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void visual_timeDigit(uint8_t,bool*);
void visual_time(uint8_t ,uint8_t, bool, bool, uint32_t);
void visual_weekday(uint8_t, bool, uint32_t);
void visual_ring(Pattern, bool);
void visual_patternHourMinuteSecond(uint8_t,uint8_t,uint8_t);
#endif /* NPSC_APPLICATION_VISUAL_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
