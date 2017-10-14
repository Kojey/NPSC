/**
  ******************************************************************************
  * @file    eeprom_test.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-March-2017
  * @brief	 This file contains the unit test implementation for the
  * 			eeprom
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "../../../NPSC/UnitTest/inc/eeprom_test.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup eeprom_test
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Unit test for writing and reading to/from the
 *				eeprom
 * @param	None
 * @retval	bool
 */
bool test_eeprom_write_read(void){
	bool result = true;
	uint8_t data = 0xAA;
	int i;
	for(i=0; i<EEPROM_SIZE; ++i)
		eeprom_write(i,data);
	delay(10000);	// Give time to the eeprom to write the data
	for(i=0; i<EEPROM_SIZE; ++i)
		result &= assertEqual(data,eeprom_read(i));
	return result;
}

/**
 * @brief	Unit test for writing and reading a 32bit number
 * @param	None
 * @retval	bool
 */
bool test_eeprom_write4B_read4B(void){
	uint8_t data[4] = {10,20,30,40};
	uint32_t data_32 = (uint32_t)((data[0]<<24)|(data[1]<<16)|(data[2]<<8)|(data[3]));
	eeprom_write4Bytes(0x00,data);
	delay(1000); // Give time to the eeprom to write the data
	uint32_t value = eeprom_read4Bytes(0x00);
	return assertEqual(data_32, value);
}


/**
 * @brief	Unit test for writing and reading a Nbit number
 * @param	None
 * @retval	bool
 */
bool test_eeprom_writeNB_readNB(void){
	uint32_t N = 15;
	uint8_t data[N], data_out[N];
	int i;
	for(i=0; i<N; ++i)	// Filling the array
		data[i] = 4*i;
	eeprom_writeNBytes(0x00,data,N);
	delay(1000); // Give time to the eeprom to write the data
	eeprom_readNBytes(0x00,data_out,N);
	bool result = true;
	for(i=0; i<N; ++i)
		result &= assertEqual(data[i],data_out[i]);
	return result;
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
