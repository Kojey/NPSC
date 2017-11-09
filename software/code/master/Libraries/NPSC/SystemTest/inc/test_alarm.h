/**
  ******************************************************************************
  * @file    test_rtc.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    25-Oct-2017
  * @brief   This file contains template of unit tests for the external rtc
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_SYSTEMTEST_ALARM_H_
#define NPSC_SYSTEMTEST_ALARM_H_

/* Includes ------------------------------------------------------------------*/
#include "assertion.h"
#include "alarm.h"


/** @addtogroup NPSC
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
bool test_alarm_address(void);
bool test_alarm_save_load(void);
#endif /* NPSC_SYSTEMTEST_ALARM_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
