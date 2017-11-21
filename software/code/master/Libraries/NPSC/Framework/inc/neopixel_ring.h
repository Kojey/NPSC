/**
  ******************************************************************************
  * @file    neopixel_ring.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    01-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			neopixel_ring firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_FRAMEWORK_NEOPIXELRING_H_
#define NPSC_FRAMEWORK_NEOPIXELRING_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup NeoPixel
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/**
 * @defgroup Constant
 * @brief Defines constants
 * @{
 */

#define NEOPIXEL_PERIPH_TIM				RCC_APB1Periph_TIM2
#define NEOPIXEL_PERIPH_GPIO				RCC_AHB1Periph_GPIOA
#define NEOPIXEL_PERIPH_DMA				RCC_AHB1Periph_DMA1
#define NEOPIXEL_PIN						GPIO_Pin_5
#define NEOPIXEL_TIM						TIM2
#define NEOPIXEL_GPIO						GPIOA
#define NEOPIXEL_GPIO_SOURCE 				GPIO_PinSource5
#define NEOPIXEL_GPIO_AF			 		GPIO_AF_TIM2
#define NEOPIXEL_TIM_IRQ 					TIM2_IRQn


#define NEOPIXEL_TIMER_CLOCK_FREQ			(84E6)//(168000000)   	// can be modified - multiples of 0.8MHz are suggested
#define NEOPIXEL_TIMER_PERIOD				(NEOPIXEL_TIMER_CLOCK_FREQ / NEOPIXEL_FREQ)
#define NEOPIXEL_LED_NUMBER					(VISUAL_RING_SIZE+VISUAL_TIME_SIZE+VISUAL_WEEKDAY_SIZE)					// how many LEDs the MCU should control?
#define NEOPIXEL_LED_DATA_SIZE				(NEOPIXEL_LED_NUMBER * 24)
#define NEOPIXEL_LED_BUFFER_SIZE			(NEOPIXEL_RESET_SLOTS_BEGIN + NEOPIXEL_LED_DATA_SIZE + NEOPIXEL_WS2812_LAST_SLOT + NEOPIXEL_RESET_SLOTS_END)
#define NEOPIXEL_WS2812_0					(NEOPIXEL_TIMER_PERIOD / 3)				// WS2812's zero high time is long about one third of the period
#define NEOPIXEL_WS2812_1					(NEOPIXEL_TIMER_PERIOD * 2 / 3)

#define NEOPIXEL_COLOUR(r,g,b)	(uint32_t)(r<<16 | g<<8 | b)

#define NEOPIXEL_NO_COLOUR					NEOPIXEL_COLOUR(0,0,0)
#define NEOPIXEL_COLOUR_RED					NEOPIXEL_COLOUR(255,0,0)
#define NEOPIXEL_COLOUR_GREEN				NEOPIXEL_COLOUR(0,255,0)
#define NEOPIXEL_COLOUR_BLUE				NEOPIXEL_COLOUR(0,0,255)

/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
extern bool neopixel_buffer_free;
extern int neopixel_buffer_index;
/* Exported macro ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/*  Function used to initialize the bluetooth device and handle transmission **/
/**	@defgroup NeoPixel_Init
 * 	@{
 */
void neopixel_init(void);

/**
 * @}
 */

/*	Function used to change the state of the neopixel_rings ************************/
/**	@defgroup NeoPixel_State
 * 	@{
 */
void neopixel_setBrightness(uint8_t b);
void neopixel_setState(uint8_t s);
void neopixel_start(void);
void neopixel_stop(void);
void neopixel_clear(void);
void neopixel_dataInit(void);
void TIM2_IRQHandler(void);
/**
 * @}
 */

/*	Function used to create and access colour *********************************/
/**	@defgroup NeoPixel_Colour
 *  @{
 */
uint32_t neopixel_colourRGBto32bits(uint8_t r,uint8_t g,uint8_t b);
uint32_t neopixel_colourRGBWTo32bits(uint8_t r,uint8_t g,uint8_t b, uint8_t w);
/**
 * @}
 */

/*	Function used to set pixel colours ****************************************/
/**	@defgroup NeoPixel_Display
 * 	@{
 */
void neopixel_setPixelRGB(uint8_t n,uint8_t r,uint8_t g,uint8_t b);
void neopixel_setPixelRGBW(uint8_t n,uint8_t r,uint8_t g,uint8_t b, uint8_t w);
void neopixel_setPixelColour(uint8_t n,uint32_t c);
void neopixel_setPixelColourW(uint8_t n,uint32_t c);
void neopixel_setAllPixelRGB(uint8_t r,uint8_t g,uint8_t b);
void neopixel_setAllPixelColour(uint32_t colour);
void neopixel_setAllPixelRGBW(uint8_t r,uint8_t g,uint8_t b, uint8_t w);

void neopixel_updatePixelColour(uint8_t n, uint32_t c);
void neopixel_updatePixelRangeRGB(uint8_t min, uint8_t max, uint32_t c);
/**
 * @}
 */

#endif /* NPSC_FRAMEWORK_NEOPIXELRING_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
