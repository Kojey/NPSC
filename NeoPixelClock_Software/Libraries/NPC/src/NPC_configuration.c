/*
 * Configuration.c
 *
 *  Created on: Feb 17, 2017
 *      Author: Kojey
 */

#include "../inc/NPC_configuration.h"


/** System init
 */
void System_Init(void){
	/* Configure bluetooth */
	bluetooth_init();
	/* Configure neopixel */
	neopixel_init();
	/* Configure clock */
	clock_init();
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
