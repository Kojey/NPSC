/**
  ******************************************************************************
  * @file    NPSC_configuration.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    17-February-2017
  * @brief   This file contains all the main initialization functions used by
  * 			the NPSC
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "NPSC_configuration.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup Configuration
  * @brief Configuration driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Initialize all firmwares used by the NPSC
 * @param	None
 * @retval	None
 */
void NPSC_init(void){
	/* Initialise system parameters */
	SystemInit();
	/* Initialise NPSC shared variables */
	parameters_init();
	/* Initialise bluetooth */
	bluetooth_init();
	/* Initialise nextion */
	nextion_init();
	/* Initialise neopixel */
	neopixel_init();
	/* Initialise rtc */
	rtc_init();
	/* Initialise clock */
	clock_init();
	/* Initialise eeprom*/
	eeprom_init();
	/* Initialise temperature */
	temperature_init();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler */
}

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
