/**
  ******************************************************************************
  * @file    rtc_test.c
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
#include <test_suite.h>

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
 *
 */
bool test_all(void){
	bool result = true;
	result &= test_rtc_clock();
	result &= test_queue_create();
	result &= test_queue_enque();
	result &= test_queue_dequeue();
/*	result &= test_eeprom_write_read();
	result &= test_eeprom_write4B_read4B();
	result &= test_eeprom_writeNB_readNB();*/
	result &= test_clock_time();
	result &= test_clock_date();
	result &= test_clock_alarm();
	result &= test_ClockMangement_save_and_load_time();
	result &= test_ClockMangement_save_and_load_date();
	result &= test_ClockMangement_save_and_load_alarm();
	result &= test_ClockMangement_time_comparison();
	result &= test_ClockMangement_date_comparison();
	result &= test_ClockMangement_alarm_comparison();
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
