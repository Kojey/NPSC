/**
  ******************************************************************************
  * @file    queue_test.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-Oct2017
  * @brief	 This file contains the unit test implementation for the
  * 			queue
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <queue_test.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup UnitTest
 *  @{
 */
/** @defgroup queue_test
  * @brief
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int capacity = 3;
struct InstructionQueue* my_queue;
/* Private functions ---------------------------------------------------------*/
bool queue_create(void){
	my_queue = InstructionQueue_createQueue(capacity);
	return assertEqual(my_queue->capacity,capacity)
			&& assertEqual(my_queue->size, 0)
			&& assertEqual(my_queue->front, 0)
			&& assertEqual(my_queue->rear, capacity-1);
}
bool queue_enque(void){
	InstructionTypeDef my_instruction;
	my_instruction.excecuted = false;
	int i;
	for(i=0; i<INSTRUCTION_SIZE; i++)
		my_instruction.instrution[i]=i;
	InstructionQueue_enqueue(my_queue,&my_instruction);
	InstructionTypeDef instr = InstructionQueue_front(my_queue);
	bool same_instruction = true;
	for(i=0; i<INSTRUCTION_SIZE; i++)
		same_instruction &= assertEqual(instr.instrution[i], my_instruction.instrution[i]);
	return assertEqual(instr.excecuted, my_instruction.excecuted)
			&& same_instruction
			&& assertEqual(my_queue->size,1);
}
bool queue_dequeue(void){
	InstructionQueue_dequeue(my_queue);
	return assertNotEqual(my_queue->size, 1);
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
