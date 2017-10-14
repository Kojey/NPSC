/**
  ******************************************************************************
  * @file    NPSC_temperature.c
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
#include "NPSC_temperature.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
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


/** @defgroup Temperature_Init Initialise the temperature reader
 * @{
 */
/**
 * @brief	Initialise the ADC
 * @note	This function configure the ADC peripheral
 * 			1) Enable peripheral clocks
 * 			3) Configure ADC channel8 pin as analog input
 * 			4) Configure ADC1 channel 1
 * 	@param 	None
 * 	@retval None
 */
void temperature_init(void){
	// Clock configuration
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	// Analogue pin configuration
	{
		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_Init(GPIOB,&GPIO_InitStruct);
	}

	// ADC structure configuration
	{
		ADC_DeInit();
		ADC_InitTypeDef ADC_InitStruct;
		ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;
		ADC_InitStruct.ADC_Resolution = ADC_Resolution_12b;
		ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;
		ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
		ADC_InitStruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
		ADC_InitStruct.ADC_NbrOfConversion = 1;
		ADC_InitStruct.ADC_ScanConvMode = DISABLE;
		ADC_Init(ADC1,&ADC_InitStruct);
		ADC_Cmd(ADC1,ENABLE);
		ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_144Cycles);
	}
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
uint16_t temperature_value(void){
	ADC_SoftwareStartConv(ADC1);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	return ADC_GetConversionValue(ADC1);
}

/**
 * @brief Convert the ADC value to its corresponding
 * 			temperature value
 * @param None
 * @retval int32_t of the temperature read
 */
int32_t temperature_read(void){
	// Convert digital reading to voltage equivalent
	float gradient = 3000.0/0xFFF;
	float voltage = temperature_value()*gradient;

	// Convert voltage to temperature
	return (int32_t) ((voltage-500)/10.0);
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
