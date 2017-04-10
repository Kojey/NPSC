/**
  ******************************************************************************
  * @file    NPC_utils.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-February-2017
  * @brief   This file contains all the utility functions prototypes used by
  * 			the NPC
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef UTILS_H_
#define UTILS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <ctype.h>
#include "stm32f4xx.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Utils
  * @{
  */

/* Exported types ------------------------------------------------------------*/
typedef enum {false = 0, true = !false} bool;

/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern uint8_t pixel_color;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint32_t max(uint32_t a, uint32_t b, uint32_t c);
void delay(uint32_t microseconds);

#endif /* UTILS_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
