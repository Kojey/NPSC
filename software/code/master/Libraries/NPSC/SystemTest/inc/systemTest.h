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

#ifndef NPSC_SYSTEMTEST_SYSTEMTEST_H_
#define NPSC_SYSTEMTEST_SYSTEMTEST_H_

/* Includes ------------------------------------------------------------------*/
#include "test_alarm.h"
#include "test_clock_management.h"


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

void systemTest_result(bool (*f)(void));
bool systemTest_all(void);

#endif /* NPSC_SYSTEMTEST_SYSTEMTEST_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
