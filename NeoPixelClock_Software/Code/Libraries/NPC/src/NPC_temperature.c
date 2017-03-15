/**
  ******************************************************************************
  * @file    NPC_temperature.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    15-March-2017
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
#include "../inc/NPC_temperature.h"

/** @addtogroup NPC
  * @{
  */

/** @defgroup Temperature
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void temperature_init(void){
	// Enable ADC1 and GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    // Configure GPIOB
    {
    	GPIO_InitTypeDef GPIO_InitStruct;
    	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB,&GPIO_InitStruct);
    }

    // Configure ADC
    {
    	ADC_InitTypeDef ADC_InitStruct;
    	ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
		ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStruct.ADC_NbrOfConversion = 1;
		ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
		ADC_InitStruct.ADC_ScanConvMode = DISABLE;
		ADC_Init(ADC1,&ADC_InitStruct);
		ADC_Cmd(ADC1,ENABLE);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_144Cycles);
    }

}

/**
 *
 */
int16_t temperature_read(void){
	ADC_SoftwareStartConv(ADC1);
	while(!)
}
/**
 * @}
 */

/**
 * @}
 */
