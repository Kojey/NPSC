/**
  ******************************************************************************
  * @file    audio.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    12-March-2017
  * @brief	 This file provides firmware functions to manage the audio
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <audio.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup Audio
  * @brief Manage audio configuration and play audio
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**	@defgroup Audio_Init Configuration functions
 * 	@brief	Audio configuration functions
 * @{
 */

/**
 * @brief Disable the DMA
 * @param None
 * @retval None
 */
void audio_disable(void){
	DMA_ClearFlag(DMA1_Stream5,DMA_FLAG_TCIF5);
	DMA_Cmd(DMA1_Stream5,DISABLE);
}


/**
 * @brief	Perform audio initialization
 * @param	DACBuffer:	Array to be pushed to the DMA
 * @param	Mode: 	DMA Mode (default:DMA_Mode_Normal)
 * @param	Size: 	sample size (default:SAMPLE_SIZE)
 * @retval 	None
 */
void audio_init(uint16_t *DACBuffer, uint16_t Size){

	// RCC configuration
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1 | RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC | RCC_APB1Periph_TIM6, ENABLE);

	// GPIO configuration [GPIOA_4]
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	// TIMER configuration [TIM6]
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStruct;
	TIM_TimeBaseStruct.TIM_Period = DMA_FREQUENCY;
	TIM_TimeBaseStruct.TIM_Prescaler = 1;
	TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStruct.TIM_RepetitionCounter = 0x0000;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStruct);
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);
	TIM_Cmd(TIM6, ENABLE);

	// DMA configuration	[Channel_7, Stream_5]
	DMA_InitTypeDef DMA_InitStruct;
	DMA_StructInit(&DMA_InitStruct);
	DMA_InitStruct.DMA_Channel=DMA_Channel_7;
	DMA_InitStruct.DMA_PeripheralBaseAddr=(uint32_t)(DAC_BASE + 0x08);  //DAC channel1 12-bit right-aligned data holding register (ref manual pg. 264)
	DMA_InitStruct.DMA_Memory0BaseAddr=(uint32_t)DACBuffer;
	DMA_InitStruct.DMA_DIR=DMA_DIR_MemoryToPeripheral;
	DMA_InitStruct.DMA_BufferSize = Size;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA1_Stream5, &DMA_InitStruct);
	DMA_Cmd(DMA1_Stream5, ENABLE);

	// DAC configuration	[Channel_1,TIM6]
	DAC_InitTypeDef DAC_InitStruct;
	DAC_InitStruct.DAC_Trigger = DAC_Trigger_T6_TRGO;
	DAC_InitStruct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStruct.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	DAC_InitStruct.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStruct);
	DAC_DMACmd(DAC_Channel_1,ENABLE);
	DAC_Cmd(DAC_Channel_1, ENABLE);
}



/**
 * @}
 */

/**	@defgroup Audio_Play Play audio functions
 * 	@brief	Audio functions
 * @{
 */

/**
 * @brief	Play a sample
 * @param	DACBuffer:	Array to be pushed to the DMA
 * @param	Size: sample size (default:SAMPLE_SIZE)
 * @return 	None
 */
void audio_play(uint16_t *DACBuffer, uint16_t Size ){
	audio_disable();
	audio_init(DACBuffer,Size);
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
