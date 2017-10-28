/**
  ******************************************************************************
  * @file    application.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-Oct-2017
  * @brief   This file contains method for managing the application
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
#include "application.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Application
 *  @{
 */
/** @defgroup Application
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
 * @brief	Initialise all shared variables
 */
void parameters_init(void){
	// Initialise the instruction queue
	instruction_queue = InstructionQueue_createQueue((unsigned)INSTRUCTION_QUEUE_SIZE);

	nextion_instr_int = malloc(NEXTION_INT);
	nextion_instr_string = malloc(NEXTION_STRING);
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
