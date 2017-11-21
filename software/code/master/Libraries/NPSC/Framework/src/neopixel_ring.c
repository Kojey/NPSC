/**
  ******************************************************************************
  * @file    neopixel_ring.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    01-March-2017
  * @brief   This file provides firmware functions to manage the neopixel_rings
  *
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <neopixel_ring.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup NeoPixel
  * @brief neopixel_ring driver modules
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint32_t neopixel_buffer[NEOPIXEL_LED_BUFFER_SIZE];
static uint8_t neopixel_ring_brightness = 255;
bool neopixel_buffer_free = false;
int neopixel_buffer_index = 0;
/* Private functions ---------------------------------------------------------*/

/**	@defgroup NeoPixel_Init Initialisation functions
 * 	@brief	Neopixel initialisation functions
 *  @{
 */

/**
 * @brief	Initialise the neopixel_ring
 * @param	None
 * @retval	None
 */
void neopixel_init(void){

	// Init data
	neopixel_dataInit();

	// Enable RCC for timer TIM2, GPIOA and DMA1
	RCC_APB1PeriphClockCmd(NEOPIXEL_PERIPH_TIM, ENABLE);
	RCC_AHB1PeriphClockCmd(NEOPIXEL_PERIPH_GPIO, ENABLE);
	RCC_AHB1PeriphClockCmd(NEOPIXEL_PERIPH_DMA, ENABLE);

	// GPIO management
	{
		GPIO_InitTypeDef GPIO_InitStruct;

		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStruct.GPIO_Pin = NEOPIXEL_PIN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

		GPIO_PinAFConfig(NEOPIXEL_GPIO,NEOPIXEL_GPIO_SOURCE,NEOPIXEL_GPIO_AF);
		GPIO_Init(NEOPIXEL_GPIO,&GPIO_InitStruct);
	}

	// TIM Timebase management
	{
		TIM_TimeBaseInitTypeDef TIM_BaseStruct;

		TIM_BaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_BaseStruct.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_BaseStruct.TIM_Period = NEOPIXEL_TIMER_PERIOD - 1;
		TIM_BaseStruct.TIM_Prescaler = 0;
		TIM_BaseStruct.TIM_RepetitionCounter = NEOPIXEL_LED_BUFFER_SIZE+1;
		// Initialise TIM2
		TIM_TimeBaseInit(NEOPIXEL_TIM,&TIM_BaseStruct);
		//
		TIM_ITConfig(NEOPIXEL_TIM,TIM_IT_Update,ENABLE);
		// Start count of TIM2
		//TIM_Cmd(TIM2,ENABLE);
	}

	// TIM Output Compare management
	{
		TIM_OCInitTypeDef TIM_OCStruct;

		TIM_OCStruct.TIM_OCMode = TIM_OCMode_PWM1;
		TIM_OCStruct.TIM_OCPolarity = TIM_OCPolarity_High;
		TIM_OCStruct.TIM_OutputState = TIM_OutputState_Enable;
		TIM_OCStruct.TIM_Pulse = NEOPIXEL_WS2812_0;
		// Initialise TIM2 PWM1
		TIM_OC1Init(NEOPIXEL_TIM,&TIM_OCStruct);
		// Activate OCPreload
		TIM_OC1PreloadConfig(NEOPIXEL_TIM,TIM_OCPreload_Disable);
	}

	// TIM interrupt DMA and FLAG management
	{
		NVIC_InitTypeDef NVIC_InitStruct;

		NVIC_InitStruct.NVIC_IRQChannel = NEOPIXEL_TIM_IRQ;
		NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		TIM_ClearITPendingBit(NEOPIXEL_TIM, TIM_IT_Update);
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
			// Initialise DMA
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
	neopixel_clear();
}

/**
 * @}
 */

/**	@defgroup NeoPixel_State State alteration functions
 * 	@brief	Neopixel state alteration functions
 *  @{
 */

/**
 * @brief	Timer Handler for neopixel_ring
 * @note	LEDBuffer is pushed every time the handle is called
 * @param	None
 * @retval	None
 */
void TIM2_IRQHandler(void){

	if (TIM_GetITStatus(NEOPIXEL_TIM, TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(NEOPIXEL_TIM, TIM_IT_Update);

		if(neopixel_buffer_index<NEOPIXEL_LED_BUFFER_SIZE){
			NEOPIXEL_TIM->CCR1 = neopixel_buffer[neopixel_buffer_index];
			neopixel_buffer_index++;
		}
	    if(neopixel_buffer_index>=NEOPIXEL_LED_BUFFER_SIZE){
	    	neopixel_stop();
	    }
	}

}

/**
 * @brief 	Stop pushing data to the neopixel_rings
 */
void neopixel_clear(void){
	neopixel_dataInit();
	// TODO add FreeRTOS delay and stop PWM
	neopixel_stop();
}

/**
 * @brief Stop the PWM wave generation
 */
void neopixel_stop(void){
	TIM_Cmd(NEOPIXEL_TIM,DISABLE);
}
/**
 * @brief Start the transmission of data
 */
void neopixel_start(void){
	// start sending from start
	neopixel_buffer_index = 0;
	TIM_Cmd(NEOPIXEL_TIM,ENABLE);
}


/**
 * @brief  	Initialise the LEDbuffer with zeros
 * @note	Does not start the transmission
 */
void neopixel_dataInit(void){
	uint32_t index, buffIndex;
	buffIndex = 0;

	for (index = 0; index < NEOPIXEL_RESET_SLOTS_BEGIN; index++) {
		neopixel_buffer[buffIndex] = WS2812_RESET;
		buffIndex++;
	}
	for (index = 0; index < NEOPIXEL_LED_DATA_SIZE; index++) {
		neopixel_buffer[buffIndex] = NEOPIXEL_WS2812_0;
		buffIndex++;
	}
	neopixel_buffer[buffIndex] = WS2812_RESET;
	buffIndex++;
	for (index = 0; index < NEOPIXEL_RESET_SLOTS_END; index++) {
		neopixel_buffer[buffIndex] = WS2812_RESET;
		buffIndex++;
	}
}

/**
 * @brief 	Set the RGB colour of one neopixel.
 * @note	This operation does not overwrite the information of the other neopixels
 * @param	n: Led index
 * @param	r: RED intensity
 * @param	g: GREEN intensity
 * @param	b: BLUE intensity
 * @retval	None
 */
void neopixel_setPixelRGB(uint8_t n, uint8_t r, uint8_t g, uint8_t b){
	// scale according to brightness
	float _max = (float)max(r,g,b);
	float b_scale = neopixel_ring_brightness/_max;
	// scale RGB
	r = (uint8_t) ((float)r*b_scale);
	g = (uint8_t) ((float)g*b_scale);
	b = (uint8_t) ((float)b*b_scale);

	uint8_t tempBuffer[24];
	uint32_t i;
	uint32_t LEDindex;
	LEDindex = n % NEOPIXEL_LED_NUMBER;

	for (i = 0; i < 8; i++) // GREEN data
		tempBuffer[i] = ((g << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	for (i = 0; i < 8; i++) // RED
		tempBuffer[8 + i] = ((r << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	for (i = 0; i < 8; i++) // BLUE
		tempBuffer[16 + i] = ((b << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	neopixel_stop();
	for (i = 0; i < 24; i++)
		neopixel_buffer[NEOPIXEL_RESET_SLOTS_BEGIN + LEDindex * 24 + i] = tempBuffer[i];
	neopixel_start();
}


void neopixel_updatePixelRGB(uint8_t n, uint8_t r, uint8_t g, uint8_t b){
	// scale according to brightness
	float _max = (float)max(r,g,b);
	float b_scale = neopixel_ring_brightness/_max;
	// scale RGB
	r = (uint8_t) ((float)r*b_scale);
	g = (uint8_t) ((float)g*b_scale);
	b = (uint8_t) ((float)b*b_scale);

	uint8_t tempBuffer[24];
	uint32_t i;
	uint32_t LEDindex;
	LEDindex = n % NEOPIXEL_LED_NUMBER;

	for (i = 0; i < 8; i++) // GREEN data
		tempBuffer[i] = ((g << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	for (i = 0; i < 8; i++) // RED
		tempBuffer[8 + i] = ((r << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	for (i = 0; i < 8; i++) // BLUE
		tempBuffer[16 + i] = ((b << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	neopixel_stop();
	for (i = 0; i < 24; i++)
		neopixel_buffer[NEOPIXEL_RESET_SLOTS_BEGIN + LEDindex * 24 + i] = tempBuffer[i];
}
/**
 * @brief 	Set the brightness of the led
 * @note	- completely dim: 0
 * 			- fully bright:	255
 * @param	b: Brightness
 * @retval	None
 */

void neopixel_setBrightness(uint8_t b){
	neopixel_ring_brightness = b;
}
/**
 * @}
 */

/**	@defgroup NeoPixel_Colour Colour generation functions
 * 	@brief	Neopixel colour functions
 *  @{
 */

/**
 * @brief 	Convert RGB 3 8bit colour to a 32bit colour
 * @note	MS3 0, MS2 r, MS1 g, MS0 b
 * @param	r: RED intensity
 * @param	g: GREEN intensity
 * @param	b: BLUE intensity
 * @retval	uint32_t RGB colour
 */
uint32_t neopixel_colourRGB(uint8_t r,uint8_t g,uint8_t b){
	return (uint32_t)(r<<16 | g<<8 | b);
}

/**
 * @brief 	Convert RGB 3 8bit colour to a 32bit colour
 * @note	MS3 w, MS2 r, MS1 g, MS0 b
 * @param	r: RED intensity
 * @param	g: GREEN intensity
 * @param	b: BLUE intensity
 * @param	w: WHITE intensity
 * @retval	uint32_t RGB colour
 */
uint32_t neopixel_colourRGBWTo32bits(uint8_t r,uint8_t g,uint8_t b, uint8_t w){
	return (uint32_t)(w<<24 | r<<16 | g<<8 | b);
}

/**
 * @}
 */

/**	@defgroup NeoPixel_Display colour display functions
 * 	@brief	Neopixel colour display functions
 *  @{
 */

/**
 * @brief Set the colour of one led
 * @param	n: Led index
 * @param	r: RED intensity
 * @param	g: GREEN intensity
 * @param	b: BLUE intensity
 * @param	w: WHITE intensity
 * @retval	None
 */
void neopixel_setPixelRGBW(uint8_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w){
	// scale w to 255:20
	float w_scale = MAX_8BIT/7.0;
	w = (uint8_t) w/(MAX_8BIT/w_scale);
	// scale
	float rgb_scale = (MAX_8BIT-w_scale)/MAX_8BIT;
	// scale RGB to 255:(255-20) and add white intensity
	r = (uint8_t) (r*rgb_scale+w);
	g = (uint8_t) (g*rgb_scale+w);
	b = (uint8_t) (b*rgb_scale+w);

	neopixel_setPixelRGB(n,r,g,b);
}

/**
 * @brief 	Set the colour of one led
 * @param	n: Led index
 * @param	c: 32bit RGB colour
 * @retval	None
 */
void neopixel_setPixelColour(uint8_t n, uint32_t c){
	neopixel_setPixelRGB(n,(uint8_t)(c>>16), (uint8_t)(c>>8), (uint8_t)(c));
}

/**
 * @brief 	Set the colour of one led
 * @param	n: Led index
 * @param	c: 32bit RGB colour
 * @retval	None
 */
void neopixel_updatePixelColour(uint8_t n, uint32_t c){
	neopixel_updatePixelRGB(n,(uint8_t)(c>>16), (uint8_t)(c>>8), (uint8_t)(c));
}

/**
 * @brief 	Set the colour of one led
 * @param	n: Led index
 * @param	c: 32bit RGB colour
 * @retval	None
 */
void neopixel_setPixelColourW(uint8_t n, uint32_t c){
	neopixel_setPixelRGBW(n, (uint8_t)(c>>16), (uint8_t)(c>>8), (uint8_t) (c),(uint8_t)(c>>24));
}

/**
 * @brief 	Set the colour of the neopixel in the given range
 */
void neopixel_updatePixelRangeRGB(uint8_t min, uint8_t max, uint32_t c){
	min %= VISUAL_RING_SIZE;
	max %= VISUAL_RING_SIZE;
	for(int i=min; i<max; ++i)
		neopixel_updatePixelColour(i,c);
}

/**
 * @brief set all the pixel on the line to a specific colour
 * @param	r: RED intensity
 * @param	g: GREEN intensity
 * @param	b: BLUE intensity
 * @retval	None
 */
void neopixel_setAllPixelRGB(uint8_t r,uint8_t g,uint8_t b){
	// scale according to brightness
	/*float _max = (float)max(r,g,b);
	float b_scale = brightness/_max;
	// scale RGB
	r = (uint8_t) ((float)r*b_scale);
	g = (uint8_t) ((float)g*b_scale);
	b = (uint8_t) ((float)b*b_scale);
*/
	uint8_t tempBuffer[24];
	int i,j;

	for (i = 0; i < 8; i++) // GREEN data
		tempBuffer[i] = ((g << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	for (i = 0; i < 8; i++) // RED
		tempBuffer[8 + i] = ((r << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	for (i = 0; i < 8; i++) // BLUE
		tempBuffer[16 + i] = ((b << i) & 0x80) ? NEOPIXEL_WS2812_1 : NEOPIXEL_WS2812_0;
	// stop timer before updating the buffer
	neopixel_stop();
	for(j=0;j<NEOPIXEL_LED_NUMBER;j++){
		for (i = 0; i < 24; i++)
			neopixel_buffer[NEOPIXEL_RESET_SLOTS_BEGIN + j * 24 + i] = tempBuffer[i];
	}
	neopixel_start();
}

/**
 * @brief set all the pixel on the line to a specific colour
 * @param	colour: an RGB colour
 * @retval	None
 */
void neopixel_setAllPixelColour(uint32_t colour){
	uint8_t r = colour>>16;
	uint8_t g = colour>>8;
	uint8_t b = colour;
	neopixel_setAllPixelRGB(r,g,b);
}

/**
 * @brief set all the pixel on the line to a specific colour
 * @param	r: RED intensity
 * @param	g: GREEN intensity
 * @param	b: BLUE intensity
 * @param	w: WHITE intensity
 * @retval	None
 */
void neopixel_setAllPixelRGBW(uint8_t r,uint8_t g,uint8_t b,uint8_t w){
	// scale w to 255:20
	float w_scale = MAX_8BIT/7.0;
	w = (uint8_t) w/(MAX_8BIT/w_scale);
	// scale
	float rgb_scale = (MAX_8BIT-w_scale)/MAX_8BIT;
	// scale RGB to 255:(255-20) and add white intensity
	r = (uint8_t) (r*rgb_scale+w);
	g = (uint8_t) (g*rgb_scale+w);
	b = (uint8_t) (b*rgb_scale+w);
	neopixel_setAllPixelRGB(r,g,b);

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
