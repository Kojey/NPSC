/*
 * neopixel.c
 *
 *  Created on: 01 Mar 2017
 *      Author: Kojey
 */

#include "../inc/neopixel.h"

static uint32_t LEDbuffer[LED_BUFFER_SIZE];// = {WS2812_1, WS2812_0};
static uint8_t brightness = 255;

void neopixel_init(void){

	// Init data
	neopixel_dataInit();

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
		//TIM_Cmd(TIM2,ENABLE);
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
		TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Disable);
	}

	// TIM interrupt DMA and FLAG management
	{
		NVIC_InitTypeDef NVIC_InitStruct;

		NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		NVIC_Init(&NVIC_InitStruct);

	}

/*	// DMA and NVIC management
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
			//DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);
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
	    if(index==LED_BUFFER_SIZE)
	    	// Start count of TIM2
			TIM_Cmd(TIM2,DISABLE);
	    index = (index + 1)% LED_BUFFER_SIZE;
	 }

	//GPIO_ToggleBits(GPIOD,GPIO_Pin_13);
}

/**
 * @brief Stop pushing data to the neopixels
 */
void neopixel_clear(){
	neopixel_dataInit();
	// TODO add FreeRTOS delay and stop PWM
}

/**
 * @brief  Initialize the LEDbuffer
 */
void neopixel_dataInit(){
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < RESET_SLOTS_BEGIN; index++) {
		LEDbuffer[buffIndex] = WS2812_RESET;
		buffIndex++;
	}
	for (index = 0; index < LED_DATA_SIZE; index++) {
		LEDbuffer[buffIndex] = WS2812_0;
		buffIndex++;
	}
	LEDbuffer[buffIndex] = WS2812_0;
	buffIndex++;
	for (index = 0; index < RESET_SLOTS_END; index++) {
		LEDbuffer[buffIndex] = WS2812_RESET;
		buffIndex++;
	}
	// Start count of TIM2
	TIM_Cmd(TIM2,ENABLE);
}

/**
 * @brief Set the color of one led
 * @n the led index
 * @r RED
 * @g GREEN
 * @b BLUE
 */
void neopixel_setPixelColorRGB(uint8_t n, uint8_t r, uint8_t g, uint8_t b){
	// scale according to brightness
	float _max = (float)max(r,g,b);
	float b_scale = brightness/_max;
	// scale RGB
	r = (uint8_t) ((float)r*b_scale);
	g = (uint8_t) ((float)g*b_scale);
	b = (uint8_t) ((float)b*b_scale);

	uint8_t tempBuffer[24];
	uint32_t i;
	uint32_t LEDindex;
	LEDindex = n % LED_NUMBER;

	for (i = 0; i < 8; i++) // GREEN data
		tempBuffer[i] = ((g << i) & 0x80) ? WS2812_1 : WS2812_0;
	for (i = 0; i < 8; i++) // RED
		tempBuffer[8 + i] = ((r << i) & 0x80) ? WS2812_1 : WS2812_0;
	for (i = 0; i < 8; i++) // BLUE
		tempBuffer[16 + i] = ((b << i) & 0x80) ? WS2812_1 : WS2812_0;
	TIM_Cmd(TIM2,DISABLE);
	for (i = 0; i < 24; i++)
		LEDbuffer[RESET_SLOTS_BEGIN + LEDindex * 24 + i] = tempBuffer[i];
	TIM_Cmd(TIM2,ENABLE);
}


/**
 * @brief Set the color of one led
 * @n the led index
 * @r RED
 * @g GREEN
 * @b BLUE
 * @w WHITE
 */
void neopixel_setPixelColorRGBW(uint8_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w){
	// scale w to 255:20
	float w_scale = MAX_8BIT/7.0;
	w = (uint8_t) w/(MAX_8BIT/w_scale);
	// scale
	float rgb_scale = (MAX_8BIT-w_scale)/MAX_8BIT;
	// scale RGB to 255:(255-20) and add white intensity
	r = (uint8_t) (r*rgb_scale+w);
	g = (uint8_t) (g*rgb_scale+w);
	b = (uint8_t) (b*rgb_scale+w);

	neopixel_setPixelColorRGB(n,r,g,b);
}
/**
 * @brief Set the color of one led
 * @n the led index
 * @c the 32bit RGB color
 */
void neopixel_setPixelColor(uint8_t n, uint32_t c){
	/*uint8_t r = ;
	uint8_t g;
	uint8_t b;*/
	neopixel_setPixelColorRGB(n,(uint8_t)(c>>16), (uint8_t)(c>>8), (uint8_t)(c));
}

/**
 * @brief Set the color of one led
 * @n the led index
 * @c the 32bit RGB color
 */
void neopixel_setPixelColorW(uint8_t n, uint32_t c){
	neopixel_setPixelColorRGBW(n, (uint8_t)(c>>16), (uint8_t)(c>>8), (uint8_t) (c),(uint8_t)(c>>24));
}
/**
 * @brief convert RGB 3 8bit color to a 32bit color
 * MS1 0, MS2 r, MS3 g, MS4 b
 */
uint32_t neopixel_colorRGB(uint8_t r,uint8_t g,uint8_t b){
	return (uint32_t)(r<<16 | g<<8 | b);
}
/**
 * @brief convert RGB 3 8bit color to a 32bit color
 * MS1 w, MS2 r, MS3 g, MS4 b
 */
uint32_t neopixel_colorRGBW(uint8_t r,uint8_t g,uint8_t b, uint8_t w){
	return (uint32_t)(w<<24 | r<<16 | g<<8 | b);
}

/**
 * @brief Set the brightness of the led
 */

void neopixel_setBrightness(uint8_t b){
	brightness = b;
}

/**
 * @brief set all the pixel on the line to a specific color
 */
void neopixel_setAllPixelRGB(uint8_t r,uint8_t g,uint8_t b){
	int i=0;
	for(i=0;i<LED_NUMBER;i++)
		neopixel_setPixelColorRGB(i,r,g,b);
}

/**
 * @brief set all the pixel on the line to a specific color
 */
void neopixel_setAllPixelRGBW(uint8_t r,uint8_t g,uint8_t b,uint8_t w){
	int i=0;
	for(i=0;i<LED_NUMBER;i++)
		neopixel_setPixelColorRGBW(i,r,g,b,w);
}
