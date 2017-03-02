/*
 * neopixel.c
 *
 *  Created on: 01 Mar 2017
 *      Author: Kojey
 */

#include "../inc/neopixel.h"

void neopixel_init(void){
	// Enable RCC for timer TIM2, GPIOA
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	// GPIO management
	{
		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_TIM2);
		GPIO_Init(GPIOA,&GPIO_InitStruct);
	}

	// TIM Timebase management
	{
		TIM_TimeBaseInitTypeDef TIM_BaseStruct;

		TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseStruct.TIM_Period = TIMER_PERIOD - 1;
		TIM_BaseStruct.TIM_Prescaler = 0;
		TIM_BaseStruct.TIM_RepetitionCounter = 0;
		// Initialize TIM2
		TIM_TimeBaseInit(TIM2,&TIM_BaseStruct);
		// Start count of TIM2
		TIM_Cmd(TIM2,ENABLE);
	}

	// TIM Output Compare management
	{
		TIM_OCInitTypeDef TIM_OCStruct;

		TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCStruct.TIM_Pulse = WS2812_0;
		// Initialize TIM2 PWM1
		TIM_OC1Init(TIM2,&TIM_OCStruct);
		// Activate OCPreload
		TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	}

	// TIM interrupt DMA and FLAG management
	{
		NVIC_InitTypeDef NVIC_InitStruct;

		NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStruct);

	}
}

void TIM2_IRQHandler(void){
	int i=0;
	i++;
}
