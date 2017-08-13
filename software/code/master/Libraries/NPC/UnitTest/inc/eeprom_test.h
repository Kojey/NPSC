/**
  ******************************************************************************
  * @file    eeprom_test.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-March-2017
  * @brief   This file contains template of unit tests for the eeprom
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_UNITTEST_INC_EEPROM_TEST_H_
#define NPC_UNITTEST_INC_EEPROM_TEST_H_

/* Includes ------------------------------------------------------------------*/
#include "../../Framework/inc/NPC_eeprom.h"
#include "unitTest.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @addtogroup eeprom_test
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
bool test_eeprom_write_read(void);
bool test_eeprom_write4B_read4B(void);
bool test_eeprom_writeNB_readNB(void);
#endif /* NPC_UNITTEST_INC_EEPROM_TEST_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
