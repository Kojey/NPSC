/**
  ******************************************************************************
  * @file    queue.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    08-Nov-2017
  * @brief   This file contains all the utility functions prototypes used by
  * 			the NPSC
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPSC_UTILITIES_QUEUE_H_
#define NPSC_UTILITIES_QUEUE_H_

/* Includes ------------------------------------------------------------------*/
#include "utils.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Utilities
  * @{
  */
/** @addtogroup Queue
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

/** @defgroup queue
  * @brief methods to insert, delete and manage a queue
  * @note Inspired from http://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
  * @{
  */
struct InstructionQueue* InstructionQueue_createQueue(unsigned );
bool InstructionQueue_isFull(struct InstructionQueue * queue);
bool InstructionQueue_isEmpty(struct InstructionQueue* queue);
void InstructionQueue_enqueue(struct InstructionQueue* queue, InstructionTypeDef* item);
InstructionTypeDef InstructionQueue_dequeue(struct InstructionQueue* queue);
int InstructionQueue_frontIndex(struct InstructionQueue* queue);
int InstructionQueue_rearIndex(struct InstructionQueue* queue);
InstructionTypeDef InstructionQueue_front(struct InstructionQueue* queue);
InstructionTypeDef InstructionQueue_rear(struct InstructionQueue* queue);
/**
 * @}
 */
#endif /* NPSC_UTILITIES_QUEUE_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
