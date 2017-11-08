/**
  ******************************************************************************
  * @file    test_eeprom.c
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
#include "../../UnitTest/inc/test_eeprom.h"

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
bool test_eeprom_write_read(uint16_t address, uint8_t data){
	eeprom_write(address,data);
	delay(10000);	// Give time to the eeprom to write the data
	return assertEqual(data,eeprom_read(address));
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
bool test_eeprom_writeNB_readNB(uint16_t start ,uint16_t size){
	start = assertInRange(start,0,EEPROM_SIZE)?start:0;
	size = assertLess(start+size,EEPROM_SIZE)?size:EEPROM_SIZE;
	uint8_t data[size], _data[size];
	// Filling the array
	int i;
	for(i=0; i<size; ++i)
		data[i] = (i+5)%0xFF;
	// write data
	eeprom_writeNBytes(start,data,size);
	eeprom_readNBytes(start,_data,size);
/*	bool result = true;
	for(i=0; i<N; ++i)
		result &= assertEqual(data[i],data_out[i]);*/
	return assertEqualArray(data,_data,size);
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
