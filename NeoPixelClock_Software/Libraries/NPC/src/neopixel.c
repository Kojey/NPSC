/*
 * neopixel.c
 *
 *  Created on: 01 Mar 2017
 *      Author: Kojey
 */

#include "../inc/neopixel.h"

static uint32_t LEDbuffer[LED_BUFFER_SIZE] = {WS2812_1, WS2812_0};

void neopixel_init(void){
	// Enable RCC for timer TIM2, GPIOA and DMA1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

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
		TIM_BaseStruct.TIM_RepetitionCounter = LED_BUFFER_SIZE+1;
		// Initialize TIM2
		TIM_TimeBaseInit(TIM2,&TIM_BaseStruct);
		//
		TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
		// Start count of TIM2
		TIM_Cmd(TIM2,ENABLE);
	}

	// TIM Output Compare management
	{
		TIM_OCInitTypeDef TIM_OCStruct;

		TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCStruct.TIM_Pulse = WS2812_1;
		// Initialize TIM2 PWM1
		TIM_OC1Init(TIM2,&TIM_OCStruct);
		// Activate OCPreload
		TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Disable);
	}

	// TIM interrupt DMA and FLAG management
	{
		NVIC_InitTypeDef NVIC_InitStruct;

		NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStruct);

	}

	/*// DMA and NVIC management
	{
		// DMA management
		{
			DMA_InitTypeDef DMA_InitStruct;

			DMA_InitStruct.DMA_BufferSize = LED_BUFFER_SIZE;
			DMA_InitStruct.DMA_Channel = DMA_Channel_3;
			DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
			DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)&LEDbuffer[0];
			DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
			DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
			DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
			DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&TIM2->CCR1;
			DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
			DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
			DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
			DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
			DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
			DMA_InitStruct.DMA_Priority = DMA_Priority_VeryHigh;
			// Initialize DMA
			DMA_Init(DMA1_Stream5,&DMA_InitStruct);

			// Start DMA
			DMA_Cmd(DMA1_Stream5, ENABLE);
			// Enable DMA complete interrupt
			DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);
		}

		// NVIC management
		{
			NVIC_InitTypeDef NVIC_InitStruct;

			NVIC_InitStruct.NVIC_IRQChannel = DMA1_Stream5_IRQn;
			NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
			NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
			NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
			// enable NVIC
			NVIC_Init(&NVIC_InitStruct);
		}



		// Enable TIM DMA
		TIM_DMACmd(TIM2,TIM_DMA_CC1,ENABLE);
		//
		//TIM_CtrlPWMOutputs(TIM2,DISABLE);
	}*/
}

void TIM2_IRQHandler(void){
	static int index = 0;

	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	    TIM2->CCR1 = LEDbuffer[index];

	    index = (index + 1)% LED_BUFFER_SIZE;
	 }

	GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
}
void DMA1_Stream5_IRQHandler(void){

}
