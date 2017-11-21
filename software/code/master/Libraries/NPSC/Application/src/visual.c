/**
  ******************************************************************************
  * @file    visual.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    28-Oct-2017
  * @brief   This file contains method for managing the application
  * 			received from the on-board touch screen and the bluetooth
  * 			device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "visual.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Application
 *  @{
 */
/** @defgroup Application
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Convert one digit to the neopixel seven segments display
 * @param	digit
 * @param	digit_pixels Array of 13 boolean mapping each number to the neopixel of each digit
 */
void visual_timeDigit(uint8_t digit,bool * digit_pixels){
	switch (digit) {
		case 0:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=9)?true:false;
			break;
		case 1:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i==6||i==7||i==8||i==11||i==12)?true:false;
			break;
		case 2:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=1&&i!=7)?true:false;
			break;
		case 3:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=1&&i!=3)?true:false;
			break;
		case 4:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=3&&i!=4&&i!=5&&i!=10)?true:false;
			break;
		case 5:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=3&&i!=12)?true:false;
			break;
		case 6:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=12)?true:false;
			break;
		case 7:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=1&&i!=2&&i!=3&&i!=4&&i!=5&&i!=9)?true:false;
			break;
		case 8:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = true;
			break;
		case 9:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
				digit_pixels[i] = (i!=3)?true:false;
			break;
		default:
			for(int i =0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
			digit_pixels[i] = false;
			break;
	}
}

/**
 * @brief	Add time information to the time array
 * @param	hour
 * @param 	minute
 * @param	second: boolean indicating the sate of the second pixel on the time pcb
 */
void visual_time(uint8_t hour,uint8_t minute, bool enable, bool second, uint32_t colour){
	// separate hour and minute
	uint8_t hour_units = hour%10;
	uint8_t hour_tens = (hour - hour_units)/10;
	uint8_t minute_units = minute%10;
	uint8_t minute_tens =  (minute-minute_units)/10;

	if(enable){
		//	hours tens
		visual_timeDigit(hour_tens,digit_pixels);
		for(int i=0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
			digit_pixels[i]?neopixel_updatePixelColour(VISUAL_RING_SIZE+i,colour)
					:neopixel_updatePixelColour(VISUAL_RING_SIZE+i,NEOPIXEL_NO_COLOUR);
		//	hours units
		visual_timeDigit(hour_units,digit_pixels);
		for(int i=0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
			digit_pixels[i]?neopixel_updatePixelColour(VISUAL_RING_SIZE+VISUAL_TIME_DIGIT_SIZE+i,colour)
					:neopixel_updatePixelColour(VISUAL_RING_SIZE+VISUAL_TIME_DIGIT_SIZE+i,NEOPIXEL_NO_COLOUR);
		//	seconds
		second?neopixel_updatePixelColour(VISUAL_RING_SIZE+2*VISUAL_TIME_DIGIT_SIZE,colour)
			  :neopixel_updatePixelColour(VISUAL_RING_SIZE+2*VISUAL_TIME_DIGIT_SIZE,NEOPIXEL_NO_COLOUR);
		second?neopixel_updatePixelColour(VISUAL_RING_SIZE+2*VISUAL_TIME_DIGIT_SIZE+1,colour)
			  :neopixel_updatePixelColour(VISUAL_RING_SIZE+2*VISUAL_TIME_DIGIT_SIZE+1,NEOPIXEL_NO_COLOUR);
		//	minute tens
		visual_timeDigit(minute_tens,digit_pixels);
		for(int i=0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
			digit_pixels[i]?neopixel_updatePixelColour(VISUAL_RING_SIZE+2*VISUAL_TIME_DIGIT_SIZE+1+i,colour)
					:neopixel_updatePixelColour(VISUAL_RING_SIZE+2*VISUAL_TIME_DIGIT_SIZE+1+i,NEOPIXEL_NO_COLOUR);
		//	minute units
		visual_timeDigit(minute_units,digit_pixels);
		for(int i=0; i<VISUAL_TIME_DIGIT_SIZE; ++i)
			digit_pixels[i]?neopixel_updatePixelColour(VISUAL_RING_SIZE+3*VISUAL_TIME_DIGIT_SIZE+1+i,colour)
					:neopixel_updatePixelColour(VISUAL_RING_SIZE+3*VISUAL_TIME_DIGIT_SIZE+1+i,NEOPIXEL_NO_COLOUR);
	}else
		for(int i=0; i<VISUAL_TIME_SIZE; ++i)
			neopixel_updatePixelColour(VISUAL_RING_SIZE+i,NEOPIXEL_NO_COLOUR);
}

/**
 * @brief	Convert the weekdays into neopixels information for the weekday board
 * @param 	weekday
 */
void visual_weekday(uint8_t weekday, bool enable, uint32_t colour){
	if(enable)
		for(int i=0; i<VISUAL_WEEKDAY_SIZE; ++i)
			(i==weekday)?neopixel_updatePixelColour(VISUAL_RING_SIZE+VISUAL_TIME_SIZE+i,colour)
						:neopixel_updatePixelColour(VISUAL_RING_SIZE+VISUAL_TIME_SIZE+i,NEOPIXEL_NO_COLOUR);
	else
		for(int i=0; i<VISUAL_WEEKDAY_SIZE; ++i)
			neopixel_updatePixelColour(VISUAL_RING_SIZE+VISUAL_TIME_SIZE+i,NEOPIXEL_NO_COLOUR);
}

/**
 * @brief	Convert pattern into neopixel information for the ring
 */
void visual_ring(Pattern pattern, bool enable){
	switch (pattern) {
		case Hour_Minute_Second:
			visual_patternHourMinuteSecond(1,2,3);
			break;
		default:
			break;
	}
}

/**
 * @brief
 */
void visual_patternHourMinuteSecond(uint8_t hour, uint8_t minute, uint8_t second){
	hour %= 24;
	minute %= 59;
	second %= 59;
	neopixel_updatePixelRangeRGB(0,hour*59/24,NEOPIXEL_COLOUR_RED);
	neopixel_updatePixelRangeRGB(hour*59/24,60,NEOPIXEL_NO_COLOUR);
	neopixel_updatePixelRangeRGB(60,60+minute,NEOPIXEL_COLOUR_BLUE);
	neopixel_updatePixelRangeRGB(60+minute,120,NEOPIXEL_NO_COLOUR);
	neopixel_updatePixelRangeRGB(120,120+second,NEOPIXEL_COLOUR_GREEN);
	neopixel_updatePixelRangeRGB(120+second,180,NEOPIXEL_NO_COLOUR);
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
