/**
  ******************************************************************************
  * @file    assertion.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    21-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			unit testing
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_TEST_INC_ASSERTION_H_
#define NPSC_TEST_INC_ASSERTION_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @addtogroup unitTest
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Assert ******************************************************************/
/**	@defgroup unitTest_Assert
 * 	@{
 */
bool assertTrue(bool condition);
bool assertFalse(bool condition);
bool assertEqual(int a, int b);
bool assertEqualArray(uint8_t* a, uint8_t* b, int N);
bool assertNotEqual(int a, int b);
bool assertGreater(int a, int b);
bool assertLess(int a, int b);
bool assertInRange(int x, int a, int b);
bool assertGreaterOrEqual(int a, int b);
bool assertLessOrEqual(int a, int b);
/**
 * @}
 */

#endif /* NPSC_TEST_INC_ASSERTION_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
