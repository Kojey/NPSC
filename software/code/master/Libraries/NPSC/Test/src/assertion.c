/**
  ******************************************************************************
  * @file    assertion.c
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
#include "assertion.h"

/*
 * TODO	test all functions in this file
 */
/** @addtogroup NPSC
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
 * @brief	Assert that condition is true
 * @param	condition
 * @return bool: result of assertion
 */
bool assertTrue(bool condition){
	return condition==true?true:false;
}

/**
 * @brief	Assert that condition is false
 * @param	condition
 * @return 	bool: result of assertion
 */
bool assertFalse(bool condition){
	return condition==false?true:false;
}

/**
 * @brief	Assert that a equals b
 * @param	a
 * @param 	b
 * @return 	bool: result of assertion
 */
bool assertEqual(int a, int b){
	return a==b?true:false;
}

/**
 * @brief	Assert that a[i]==b[i] for
 * 				i in N
 * @param	*a
 * @param 	*b
 * @param	N
 * @return 	bool: result of assertion
 */
bool assertEqualArray(uint8_t* a, uint8_t* b, int N){
	bool result = true;
	int i=0;
	for(i=0;i<N;i++)
		result&=assertEqual(a[i],b[i]);
	return result;
}


/**
 * @brief	Assert that a is not equal to b
 * @param	a
 * @param 	b
 * @return 	bool: result of assertion
 */
bool assertNotEqual(int a, int b){
	return a!=b?true:false;
}

/**
 * @brief	Assert that a is greater than b
 * @param	a
 * @param 	b
 * @return 	bool: result of assertion
 */
bool assertGreater(int a, int b){
	return a>b?true:false;
}

/**
 * @brief	Assert that a less than than b
 * @param	a
 * @param 	b
 * @return bool: result of assertion
 */
bool assertLess(int a, int b){
	return a<b?true:false;
}

/**
 * @brief	Assert that a<=x<b
 * @param	x
 * @param	a
 * @param 	b
 * @return bool: result of assertion
 */
bool assertInRange(int x, int a, int b){
	return assertGreaterOrEqual(x,a)&&assertLess(x,b);
}
/**
 * @brief	Assert that a is greater or equals to b
 * @param	a
 * @param 	b
 * @return bool: result of assertion
 */
bool assertGreaterOrEqual(int a, int b){
	return a>=b?true:false;
}

/**
 * @brief	Assert that a is less or equals to b
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

