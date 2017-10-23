/**
  ******************************************************************************
  * @file    instruction.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-Oct-2017
  * @brief   This file contains method for managing the instructions
  * 			received from the on-board touch screen and the bluetooth
  * 			device
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "instructions.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Application
 *  @{
 */
/** @defgroup Instructions
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Execute instructions from instruction queue
 */
void instruction_execute(void){
	while(instruction_queue->size){
		// fecth instruction
		InstructionTypeDef instruction = InstructionQueue_dequeue(instruction_queue);
		// decode and execute instruction
		switch(instruction.instrution[0]){
		case 0x00:
			//
			break;
		case 0x01:
			//
			break;
		case 0x02:
			//
			break;
		default:
			break;
		}
		// dequeue instruction
		InstructionQueue_dequeue(instruction_queue);
	}
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
