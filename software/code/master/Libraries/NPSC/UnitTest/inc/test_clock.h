/**
  ******************************************************************************
  * @file    clock_test.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    24-March-2017
  * @brief   This file contains template of unit tests for the
  * 			stm32f4 internal clock
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_UNITTEST_INC_TEST_CLOCK_H_
#define NPSC_UNITTEST_INC_TEST_CLOCK_H_

/* Includes ------------------------------------------------------------------*/
#include "clock.h"
#include "../../UnitTest/inc/assertion.h"


/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @defgroup clock_test
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
bool test_clock_date(void);
bool test_clock_time(void);
bool test_clock_alarm(void);

#endif /* NPSC_UNITTEST_INC_TEST_CLOCK_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
