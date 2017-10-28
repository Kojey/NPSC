/**
  ******************************************************************************
  * @file    test.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    25-Oct-2017
  * @brief
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_TEST_INC_TEST_H_
#define NPSC_TEST_INC_TEST_H_

/* Includes ------------------------------------------------------------------*/
#include "assertion.h"
#include "test_clock.h"
#include "test_clock_management.h"
#include "test_eeprom.h"
#include "test_queue.h"
#include "test_rtc.h"
#include "test_alarm.h"


/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @defgroup test
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

void test_result(bool);
bool test_all(void);

#endif /* NPSC_TEST_INC_TEST_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
