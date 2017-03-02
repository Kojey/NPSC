/*
 * neopixel.h
 *
 *  Created on: 01 Mar 2017
 *      Author: Kojey
 */

#ifndef NPC_INC_NEOPIXEL_H_
#define NPC_INC_NEOPIXEL_H_

#include "utils.h"

/* WS2812 Defines constants*/
#define WS2812_FREQ							(8E5) 			// it is fixed: WS2812 require 800kHz
#define TIMER_CLOCK_FREQ					(84E6)//(168000000)   	// can be modified - multiples of 0.8MHz are suggested
#define TIMER_PERIOD						(TIMER_CLOCK_FREQ / WS2812_FREQ)
#define LED_NUMBER							(3)					// how many LEDs the MCU should control?
#define LED_DATA_SIZE						(LED_NUMBER * 24)
#define RESET_SLOTS_BEGIN					(50)
#define RESET_SLOTS_END						(50)
#define WS2812_LAST_SLOT					(1)
#define LED_BUFFER_SIZE						(RESET_SLOTS_BEGIN + LED_DATA_SIZE + WS2812_LAST_SLOT + RESET_SLOTS_END)
#define WS2812_0							(TIMER_PERIOD / 3)				// WS2812's zero high time is long about one third of the period
#define WS2812_1							(TIMER_PERIOD * 2 / 3)		// WS2812's one high time is long about two thirds of the period
#define WS2812_RESET						(0)
#define MAX_8BIT							(255)

/* Methods */
void TIMx_DMA_IRQHandler(void);
void neopixel_init(void);
void neopixel_setState(uint8_t s);
void neopixel_show(void);
void neopixel_clear(void);
void neopixel_dataInit(void);
void neopixel_setPixelColorRGB(uint8_t n,uint8_t r,uint8_t g,uint8_t b);
void neopixel_setPixelColorRGBW(uint8_t n,uint8_t r,uint8_t g,uint8_t b, uint8_t w);
void neopixel_setPixelColor(uint8_t n,uint32_t c);
void neopixel_setPixelColorW(uint8_t n,uint32_t c);
void neopixel_setBrightness(uint8_t b);
uint32_t neopixel_colorRGB(uint8_t r,uint8_t g,uint8_t b);
uint32_t neopixel_colorRGBW(uint8_t r,uint8_t g,uint8_t b, uint8_t w);

#endif /* NPC_INC_NEOPIXEL_H_ */
