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

#ifndef NPC_UNITTEST_INC_UINTTEST_H_
#define NPC_UNITTEST_INC_UINTTEST_H_

/* Includes ------------------------------------------------------------------*/
#include "../../Framework/inc/NPC_utils.h"

/** @addtogroup NPC
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

#endif /* NPC_UNITTEST_INC_UINTTEST_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
