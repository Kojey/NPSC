/**
  ******************************************************************************
  * @file    NPSC_neopixel.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    01-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			neopixel firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_INC_NPSC_NEOPIXEL_H_
#define NPSC_INC_NPSC_NEOPIXEL_H_

/* Includes ------------------------------------------------------------------*/
#include "NPSC_utils.h"

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
#define WS2812_FREQ							(8E5) 			// it is fixed: WS2812 require 800kHz
#define TIMER_CLOCK_FREQ					(84E6)//(168000000)   	// can be modified - multiples of 0.8MHz are suggested
#define TIMER_PERIOD						(TIMER_CLOCK_FREQ / WS2812_FREQ)
#define LED_NUMBER							(180)					// how many LEDs the MCU should control?
#define LED_DATA_SIZE						(LED_NUMBER * 24)
#define RESET_SLOTS_BEGIN					(50)
#define RESET_SLOTS_END						(50)
#define WS2812_LAST_SLOT					(1)
// TODO maybe LED_BUFFER_SIZE create bugs in rings
#define LED_BUFFER_SIZE						(RESET_SLOTS_BEGIN + LED_DATA_SIZE + WS2812_LAST_SLOT + RESET_SLOTS_END)
#define WS2812_0							(TIMER_PERIOD / 3)				// WS2812's zero high time is long about one third of the period
#define WS2812_1							(TIMER_PERIOD * 2 / 3)		// WS2812's one high time is long about two thirds of the period
#define WS2812_RESET						(0)
#define MAX_8BIT							(255)
/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
extern bool neopixel_buffer_free;
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

/*	Function used to change the state of the neopixels ************************/
/**	@defgroup NeoPixel_State
 * 	@{
 */
void neopixel_setBrightness(uint8_t b);
void neopixel_setState(uint8_t s);
void neopixel_show(void);
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
uint32_t neopixel_colourRGB(uint8_t r,uint8_t g,uint8_t b);
uint32_t neopixel_colourRGBW(uint8_t r,uint8_t g,uint8_t b, uint8_t w);
/**
 * @}
 */

/*	Function used to set pixel colours ****************************************/
/**	@defgroup NeoPixel_Display
 * 	@{
 */
void neopixel_setPixelColourRGB(uint8_t n,uint8_t r,uint8_t g,uint8_t b);
void neopixel_setPixelColourRGBW(uint8_t n,uint8_t r,uint8_t g,uint8_t b, uint8_t w);
void neopixel_setPixelColour(uint8_t n,uint32_t c);
void neopixel_setPixelColourW(uint8_t n,uint32_t c);
void neopixel_setAllPixelRGB(uint8_t r,uint8_t g,uint8_t b);
void neopixel_setAllPixelColour(uint32_t colour);
void neopixel_setAllPixelRGBW(uint8_t r,uint8_t g,uint8_t b, uint8_t w);
/**
 * @}
 */

#endif /* NPSC_INC_NPSC_NEOPIXEL_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
