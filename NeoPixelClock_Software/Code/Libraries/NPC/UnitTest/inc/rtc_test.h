/**
  ******************************************************************************
  * @file    rtc_test.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    24-March-2017
  * @brief   This file contains template of unit tests for the rtc
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_UNITTEST_INC_TEST_RTC_H_
#define NPC_UNITTEST_INC_TEST_RTC_H_

/* Includes ------------------------------------------------------------------*/
#include "uintTest.h"
#include "../../Framework/inc/NPC_clock.h"


/** @addtogroup NPC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @defgroup rtc_test
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

#endif /* NPC_UNITTEST_INC_TEST_RTC_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
