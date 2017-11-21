/**
  ******************************************************************************
  * @file    utils.c
  * @author  Othniel Konan (Kojey)
  * @version V1.2.0
  * @date    23-February-2017
  * @brief   This file provides utility functions to the NPSC clock
  *
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <utils.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Utilities
  * @{
  */
/** @defgroup Utils
  * @brief utils driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t DMA_RX_Buffer[DMA_RX_BUFFER_SIZE];
uint8_t INSTRUCTION_BUFFER[INSTRUCTION_SIZE] = {0};

Instruction_lock instruction_lock_owner = instruction_no_lock;

bool nextion_ack = false;

char* nextion_instr_int;
char* nextion_instr_string;
/* all instruction end with nextion_instr_end*/
char nextion_instr_end[3]={0xFF,0XFF,0XFF}; // 0xFF 0xFF 0xFF

char * label;
char * label_instruction;

bool digit_pixels[VISUAL_TIME_DIGIT_SIZE]={false};

/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Find max between a, b, and c
 * @param	a: First value
 * @param	b: second value
 * @param	c: Third value
 * @retval	uint32_t of the maximum value
 */
uint32_t max(uint32_t a, uint32_t b, uint32_t c){
	return a>b?(a>c?a:c):(b>c?b:c);
}

/**
 * @brief	delay for the number of microsecond
 * @note 	TODO use RTOS delay instead
 * @param	microseconds
 * @retval	None
 */
void delay(uint32_t microseconds) {
  /* Hangs for specified number of microseconds. */
  volatile uint32_t counter = 0;
  microseconds *= 4;
  for(; counter<microseconds; counter++);
}

/**
 * @brief	Append byte of instruction to the string
 */
void get_stringFromInstruction(char* string,char* instruction, int size){
	memset(string,0,strlen(string));
	strncat(string,instruction,size);
}


bool instruction_valid(uint8_t code){
	return code==0x00?false:true;
}
bool instruction_ack(uint8_t * cmd){
	bool result = cmd[1]==0xFF;
	result &= cmd[2]==0xFF;
	result &= cmd[3]==0xFF;
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
