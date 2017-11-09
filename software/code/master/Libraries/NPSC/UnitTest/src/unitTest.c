/**
  ******************************************************************************
  * @file    test.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    24-March-2017
  * @brief	 This file contains the unit test implementation for the
  * 			external rtc
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <unitTest.h>
#include "neopixel.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup rtc_test
  * @brief
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
 * @brief	Turn on LEDs based on test results
 * @param	*function: pointer to a function with no parameters
 */
void unitTest_result(bool (*function)(void)){
	// initialise test display
	STM_EVAL_LEDInit(LED6); // blue led
	STM_EVAL_LEDInit(LED5); // red led
	STM_EVAL_LEDInit(LED3); // orange led
	neopixel_setBrightness(100);
	STM_EVAL_LEDOn(LED3);
	neopixel_setAllPixelRGB(255,80,0);
	delay(1);

	// Blue: SUCCESS
	// Red: ERROR
	(*function)?STM_EVAL_LEDOn(LED6):STM_EVAL_LEDOn(LED5);
	(*function)?neopixel_setAllPixelRGB(0,0,255):neopixel_setAllPixelRGB(255,0,0);
}
/**
 *
 */
bool unitTest_all(void){
	bool result = true;
	result &= test_rtc_clock();
	result &= test_queue_create();
	result &= test_queue_enqueue();
	result &= test_queue_dequeue();
/*	result &= test_eeprom_write_read();
	result &= test_eeprom_write4B_read4B();
	result &= test_eeprom_writeNB_readNB();*/
	result &= test_clock_time();
	result &= test_clock_date();
	result &= test_clock_alarm();
	return result;

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
