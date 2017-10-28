/**
  ******************************************************************************
  * @file    utils.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-Oct-2017
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

#ifndef NPSC_FRAMEWORK_UTILS_H_
#define NPSC_FRAMEWORK_UTILS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Utils
  * @{
  */

/* Exported constants --------------------------------------------------------*/
#define INSTRUCTION_SIZE            	8
#define DMA_RX_BUFFER_SIZE          	8

#define INSTRUCTION_QUEUE_SIZE			4

/* Exported types ------------------------------------------------------------*/
// boolean true false definition
typedef enum {false = 0, true = !false} bool;

// intruction_lock definition
typedef enum {
	instruction_no_lock = 0 ,
	instruction_bluetooth_lock = 1,
	instruction_nextion_lock = 2
} Instruction_lock;

// Ring tone
typedef enum {
	none = 0,
	ring1 = 1,
	ring2 = 2
} Ringtone;

// Ring tone
typedef enum {
	never = 0,
	daily = 1,
	weekly = 2
} Alarm_repeat;

// Pattern
typedef enum {
	Sunrise = 0,
	Simple = 1,
	Hour_Minute_Second = 2,
	Disco = 3,
	Crazy = 4
} Pattern;


// Clock type definition
typedef struct {
	RTC_TimeTypeDef time;
	RTC_DateTypeDef date;
} RTC_ClockTypeDef;

// Instruction type definition
typedef struct {
	uint8_t instrution[INSTRUCTION_SIZE]; // instruction
	bool excecuted;	// status of instruction
} InstructionTypeDef;

// Queue Type definition
struct InstructionQueue {
	int front, rear, size;
	unsigned capacity;
	InstructionTypeDef * array;// array of instruction
} ;

/* Exported variables --------------------------------------------------------*/

extern uint8_t DMA_RX_Buffer[DMA_RX_BUFFER_SIZE];
extern uint8_t INSTRUCTION_BUFFER[INSTRUCTION_SIZE];

extern Instruction_lock instruction_lock_owner;

struct InstructionQueue* instruction_queue;

extern bool nextion_ack;

extern char* nextion_instr_int;
extern char* nextion_instr_string;
extern char nextion_instr_end[3];
/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint32_t max(uint32_t a, uint32_t b, uint32_t c);
void delay(uint32_t microseconds);


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
#endif /* NPSC_FRAMEWORK_UTILS_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
