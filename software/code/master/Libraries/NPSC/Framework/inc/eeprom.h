/**
  ******************************************************************************
  * @file    eeprom.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    12-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			eeprom firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_FRAMEWORK_EEPROM_H_
#define NPSC_FRAMEWORK_EEPROM_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Eeprom
  * @brief Eeprom framework
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @defgroup Instructions
 * @brief 25LC640A instruction set
 * @{
 */
#define WREN 0b00000110 // enable writing
#define WRDI 0b00000100 // disable writing
#define RDSR 0b00000101 // read status register
#define WRSR 0b00000001 // write status register
#define READ 0b00000011	// read instruction
#define WRITE 0b00000010 // write instruction
/**
 * @}
 */

/**
 * @defgroup Utilities
 * @{
 */
#define EEPROM_PAGE_LENGTH	32
#define EEPROM_SIZE 0xFA00 // 64KB = 64 000
/**
 * @}
 */

/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Initialisation functions ***************************************************/
/**	@defgroup Eeprom_Init Initialisation functions
 * @{
 */
void eeprom_init(void);
/**
 * @}
 */
/* Data transmission function *************************************************/
/**	@defgroup Eeprom_Trans Transmission functions
 * @{
 */
ErrorStatus eeprom_write(uint16_t address, uint8_t data);
uint8_t eeprom_read(uint16_t address);
ErrorStatus eeprom_write32Bytes(uint16_t baseAddress, uint8_t *data);
uint32_t eeprom_read4Bytes(uint16_t baseAddress);
ErrorStatus eeprom_writeNBytes(uint16_t baseAddress, uint8_t *data, uint16_t N);
ErrorStatus eeprom_write4Bytes(uint16_t baseAddress, uint8_t *data);
ErrorStatus eeprom_readNBytes(uint16_t baseAddress,uint8_t *data, uint16_t N);
void eeprom_clear(void);
/**
 * @}
 */
#endif /* NPSC_FRAMEWORK_EEPROM_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
