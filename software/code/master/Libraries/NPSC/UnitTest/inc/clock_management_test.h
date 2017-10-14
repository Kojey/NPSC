/**
  ******************************************************************************
  * @file    NPSC_bluetooth.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    01-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			bluetooth firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_UNITTEST_INC_CLOCK_MANAGEMENT_TEST_H_
#define NPSC_UNITTEST_INC_CLOCK_MANAGEMENT_TEST_H_

/* Includes ------------------------------------------------------------------*/
#include "clock_management.h"

#include "unitTest.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @
 */
/** @defgroup clock_management_test
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Save and Load unit test ****************************************************/
/**	@defgroup clock_management_test_save_lod
 * 	@brief	Save and Load unit test
 *  @{
  */

bool test_ClockMangement_save_and_load_time(void);
bool test_ClockMangement_save_and_load_date(void);
bool test_ClockMangement_save_and_load_alarm(void);

/**
 * @}
 */


/* Comparison unit test ****************************************************/
/**	@defgroup clock_management_test_comparison
 * 	@brief	comparison unit test
 *  @{
  */

bool test_ClockMangement_time_comparison(void);
bool test_ClockMangement_date_comparison(void);
bool test_ClockMangement_alarm_comparison(void);


/**
 * @}
 */

#endif /* NPSC_UNITTEST_INC_CLOCK_MANAGEMENT_TEST_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
