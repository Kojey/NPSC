/**
  ******************************************************************************
  * @file    queue_test.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-Oct-2017
  * @brief   This file contains template of unit tests for the queue
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_UNITTEST_INC_TEST_QUEUE_H_
#define NPSC_UNITTEST_INC_TEST_QUEUE_H_

/* Includes ------------------------------------------------------------------*/
#include "unitTest.h"
#include "NPSC_utils.h"


/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @defgroup queue_test
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

bool queue_create(void);
bool queue_enque(void);
bool queue_dequeue(void);

#endif /* NPSC_UNITTEST_INC_TEST_QUEUE_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
