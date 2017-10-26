/**
  ******************************************************************************
  * @file    test_suite.h
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

#ifndef NPSC_UNITTEST_INC_TEST_SUITE_H_
#define NPSC_UNITTEST_INC_TEST_SUITE_H_

/* Includes ------------------------------------------------------------------*/
#include "unitTest.h"
#include "rtc_test.h"
#include "queue_test.h"
#include "eeprom_test.h"
#include "clock_test.h"
#include "clock_management_test.h"


/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @defgroup suite_test
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

bool test_all(void);

#endif /* NPSC_UNITTEST_INC_TEST_SUITE_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
