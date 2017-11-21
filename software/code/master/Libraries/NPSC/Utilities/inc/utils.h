/**
  ******************************************************************************
  * @file    utils.h
  * @author  Othniel Konan (Kojey)
  * @version V1.2.0
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

#ifndef NPSC_UTILITIES_UTILS_H_
#define NPSC_UTILITIES_UTILS_H_

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

#define WS2812_RESET							(0)
#define MAX_8BIT								(255)
#define NEOPIXEL_FREQ							(8E5) 			// it is fixed: WS2812 require 800kHz
#define NEOPIXEL_RESET_SLOTS_BEGIN				(50)
#define NEOPIXEL_RESET_SLOTS_END				(50)
#define NEOPIXEL_WS2812_LAST_SLOT				(1)


#define NEOPIXEL_COLOURS				3
#define NEOPIXEL_COLOUR_CODE			8
#define VISUAL_WEEKDAY_SIZE				7
#define VISUAL_TIME_DIGIT_SIZE			13
#define VISUAL_TIME_SIZE				(VISUAL_TIME_DIGIT_SIZE*4+2)
#define VISUAL_RING_SIZE				60*3

#define INSTRUCTION_SIZE            	8
#define DMA_MAX_INSTRUCTION				7
#define DMA_RX_BUFFER_SIZE          	INSTRUCTION_SIZE*DMA_MAX_INSTRUCTION

#define INSTRUCTION_QUEUE_SIZE			6

/* Exported types ------------------------------------------------------------*/
// boolean true false definition
typedef enum {false = 0, true = !false} bool;

// intruction_lock definition
typedef enum {
	instruction_no_lock = 1 ,
	instruction_bluetooth_lock = 2,
	instruction_nextion_lock = 3
} Instruction_lock;

// Ring tone
typedef enum {
	tone1 = 1,
	tone2 = 2,
	tone3 = 3
} Ringtone;

// Ring tone
typedef enum {
	Never = 1,
	Daily = 2,
	Weekly = 3
} Alarm_repeat;

// Pattern
typedef enum {
	pattern1 = 1,
	pattern2 = 2,
	pattern3 = 3,
	pattern4 = 4,
	pattern5 = 5,
	Hour_Minute_Second = 6
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

char * label;
char * label_instruction;

extern bool digit_pixels[VISUAL_TIME_DIGIT_SIZE];

extern uint8_t visual_weeksayBuffer[VISUAL_WEEKDAY_SIZE];
extern uint8_t visual_timeBuffer[VISUAL_TIME_SIZE];
extern uint8_t visual_ringBuffer[VISUAL_RING_SIZE];

/* Exported macro ------------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
uint32_t max(uint32_t a, uint32_t b, uint32_t c);
void delay(uint32_t microseconds);
void get_stringFromInstruction(char*,char*,int);
bool instruction_valid(uint8_t);
bool instruction_ack(uint8_t *);

#endif /* NPSC_UTILITIES_UTILS_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
