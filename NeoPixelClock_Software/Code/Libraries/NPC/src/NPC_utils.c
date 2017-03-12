/**
  ******************************************************************************
  * @file    NPC_utils.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-February-2017
  * @brief   This file provides utility functions to the NPC clock
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "../inc/NPC_utils.h"

/** @addtogroup NPC
  * @{
  */

/** @defgroup Utils
  * @brief utils driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t pixel_color;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Find max between a, b, and c
 * @param	a: First value
 * @param	b: second value
 * @param	c: Third value
 * @retval	uint32_t of the maximum value
 */
uint32_t max(uint32_t a, uint32_t b, uint32_t c){
	return a>b?(a>c?a:c):(b>c?b:c);
}

/**
 * @brief	delay for the number of microsecond
 * @note 	TODO use RTOS delay instead
 * @param	microseconds
 * @retval	None
 */
void delay(uint32_t microseconds) {
  /* Hangs for specified number of microseconds. */
  volatile uint32_t counter = 0;
  microseconds *= 3;
  for(; counter<microseconds; counter++);
}
