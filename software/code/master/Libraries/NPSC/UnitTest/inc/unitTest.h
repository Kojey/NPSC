/**
  ******************************************************************************
  * @file    unitTest.h
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

#ifndef NPSC_UNITTEST_INC_UNITTEST_H_
#define NPSC_UNITTEST_INC_UNITTEST_H_

/* Includes ------------------------------------------------------------------*/
#include "NPSC_utils.h"

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
bool assertGreater(int a, int b);
bool assertLess(int a, int b);
bool assertGreaterOrEqual(int a, int b);
bool assertLessOrEqual(int a, int b);
/**
 * @}
 */

#endif /* NPSC_UNITTEST_INC_UNITTEST_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
