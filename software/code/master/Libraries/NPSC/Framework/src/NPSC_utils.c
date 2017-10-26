/**
  ******************************************************************************
  * @file    NPSC_utils.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
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
#include "NPSC_utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
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
char nextion_instr_end[3]="ÿÿÿ"; // 0xFF 0xFF 0xFF
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


/** @defgroup queue
  * @brief methods to insert, delete and manage a queue
  * @{
  */
/**
 * @brief	Create the instruction queue
 */
struct InstructionQueue* InstructionQueue_createQueue(unsigned capacity){
    struct InstructionQueue* queue = (struct InstructionQueue*) malloc(sizeof(struct InstructionQueue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;  // This is important, see the enqueue
    queue->array = (InstructionTypeDef*) malloc(queue->capacity * sizeof(InstructionTypeDef));
    return queue;
}
/**
 * @brief	Check if the queue is full
 */
bool InstructionQueue_isFull(struct InstructionQueue * queue){
	return (queue->size == queue->capacity);
}
/**
 * @brief	Check if the queue is empty
 */
bool InstructionQueue_isEmpty(struct InstructionQueue* queue){
	return (queue->size == 0);
}
/**
 * @brief	Add an element to the queue
 */
void InstructionQueue_enqueue(struct InstructionQueue* queue, InstructionTypeDef* item){
	 if (InstructionQueue_isFull(queue))
	        return;
	 queue->rear = (queue->rear + 1)%queue->capacity;
	 queue->array[queue->rear] = *item;
	 queue->size = queue->size + 1;
}
/**
 * @brief	Remove an element to the queue
 */
InstructionTypeDef InstructionQueue_dequeue(struct InstructionQueue* queue){
    InstructionTypeDef item = queue->array[queue->front];
    queue->front = (queue->front + 1)%queue->capacity;
    queue->size = queue->size - 1;
    return item;
}
/**
 * @brief	Get front of queue
 */
int InstructionQueue_frontIndex(struct InstructionQueue* queue){
    if (InstructionQueue_isEmpty(queue))
        return INT_MIN;
    return queue->front;
}
/**
 * @brief	Get rear of queu
 */
int InstructionQueue_rearIndex(struct InstructionQueue* queue){
    if (InstructionQueue_isEmpty(queue))
        return INT_MIN;
    return queue->rear;
}
/**
 * @brief	Get front of queue
 */
InstructionTypeDef InstructionQueue_front(struct InstructionQueue* queue){
    return queue->array[queue->front];
}
/**
 * @brief	Get rear of queu
 */
InstructionTypeDef InstructionQueue_rear(struct InstructionQueue* queue){
    return queue->array[queue->rear];
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
