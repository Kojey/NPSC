/**
  ******************************************************************************
  * @file    queue.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    08-November-2017
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
#include "queue.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Utilities
  * @{
  */
/** @defgroup Queue
  * @brief
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


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
