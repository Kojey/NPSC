/**
  ******************************************************************************
  * @file    unitTest.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    21-March-2017
  * @brief	 This file contains the implementation of the function
  * 			used for Unit Testing
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "../inc/unitTest.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup unitTest
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**	@defgroup unitTest_Assert
 * 	@brief
 *  @{
 */

/**
 * @brief	Assert than condition is true
 * @param	condition
 * @return bool: result of assertion
 */
bool assertTrue(bool condition){
	return condition==true?true:false;
}

/**
 * @brief	Assert than condition is false
 * @param	condition
 * @return 	bool: result of assertion
 */
bool assertFalse(bool condition){
	return condition==false?true:false;
}

/**
 * @brief	Assert than a equals b
 * @param	a
 * @param 	b
 * @return 	bool: result of assertion
 */
bool assertEqual(int a, int b){
	return a==b?true:false;
}

/**
 * @brief	Assert than a is greater than b
 * @param	a
 * @param 	b
 * @return 	bool: result of assertion
 */
bool assertGreater(int a, int b){
	return a>b?true:false;
}

/**
 * @brief	Assert than a less than than b
 * @param	a
 * @param 	b
 * @return bool: result of assertion
 */
bool assertLess(int a, int b){
	return a<b?true:false;
}

/**
 * @brief	Assert than a is greater or equals to b
 * @param	a
 * @param 	b
 * @return bool: result of assertion
 */
bool assertGreaterOrEqual(int a, int b){
	return a>=b?true:false;
}

/**
 * @brief	Assert than a is less or equals to b
 * @param	a
 * @param 	b
 * @return bool: result of assertion
 */
bool assertLessOrEqual(int a, int b){
	return a<=b?true:false;
}

/**
 * @}
 */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */

