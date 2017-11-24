/**
  ******************************************************************************
  * @file    timer.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    11-Nov-2017
  * @brief	 This file provides firmware functions to manage the temperature
  * 			sensor
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "timer.h"
#include "neopixel_ring.h"
/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup Timer
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t timer_frequency = 1;
bool timer_start = false;
bool timer_event = false;
/* Private functions ---------------------------------------------------------*/


/** @defgroup Timer_init Initialise the temperature reader
 * @{
 */
/**
 * @brief
 * 	@param 	None
 * 	@retval None
 */
void timer_init(void){
	// Clock configuration

	// Enable TIM5
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 ,ENABLE);
	// Setup the timer
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_Prescaler = 10000;
	TIM_TimeBaseStruct.TIM_Period = (uint32_t) 8399/timer_frequency;//126000/timer_frequency + 1;
	TIM_TimeBaseStruct.TIM_ClockDivision = 0;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStruct);
	TIM_Cmd(TIM5, ENABLE);
	TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);

	// Enable the TIM5 global Interrupt
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	timer_start = true;
}
/**
 * @}
 */

/** @defgroup Temperature_Data Temperature information
 *  @{
 */

/**
 * @brief Read ADC value
 * @param None
 * @retval uint32_t of the ADC value
 */
void TIM5_IRQHandler(void){
	if (TIM_GetITStatus(TIM5, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
		STM_EVAL_LEDToggle(LED6);
		timer_event = true;
	}
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
/**
 * @}
 */
