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
	RTC_ClockTypeDef clock;
	char b[2]="as";
	while(instruction_queue->size){
		// fecth instruction
		InstructionTypeDef instruction = InstructionQueue_dequeue(instruction_queue);
		// decode and execute instruction
		switch(instruction.instrution[0]){
		/* External RTC instructions*/
		case 0x00:
			// set clock
			clock.date.RTC_Year=instruction.instrution[1];
			clock.date.RTC_Month=instruction.instrution[2];
			clock.date.RTC_Date=instruction.instrution[3];
			clock.date.RTC_WeekDay=instruction.instrution[4];
			clock.time.RTC_Hours=instruction.instrution[5];
			clock.time.RTC_Minutes=instruction.instrution[6];
			clock.time.RTC_Seconds=instruction.instrution[7];
			clock.time.RTC_H12=RTC_H12_AM;
			rtc_set_clock(&clock);
			break;
		case 0x01:
			// get clock
			// clock = rtc_get_clock()
			instruction_nextion_start();
			instruction_nextion_send_str("b0.txt=","Nice");
			instruction_nextion_stop();
  			break;
		case 0x02:
			instruction_nextion_start();
			instruction_nextion_send_int("n0.val=",12);
			instruction_nextion_stop();
			break;
		default:
			break;
		}
	}
}

/**
 * @brief	Send junk data to start communication with screen
 */
void instruction_nextion_start(void){
	// empty string
	memset(nextion_instr_string,0,strlen(nextion_instr_string));
	// write junk instruction
	strcat(nextion_instr_string,"code_c");
	// add end instruction
	strcat(nextion_instr_string,nextion_instr_end);
	// send junk data
	nextion_send((uint8_t *)nextion_instr_string);
}
/**
 * @brief	Send end of transmission signal
 */
void instruction_nextion_stop(void){
	// empty string
	memset(nextion_instr_string,0,strlen(nextion_instr_string));
	// write stop instruction
	strcat(nextion_instr_string,"com_stop");
	// add end instruction
	strcat(nextion_instr_string,nextion_instr_end);
	// send instruction
	nextion_send((uint8_t *)nextion_instr_string);
	// Inform nextion_buffer_update that the coming byte are to be discarded
	nextion_ack = true;
}
/**
 * @brief	Send an instruction requiring integer value
 * @param	instruction
 * @param	value
 */
void instruction_nextion_send_int(char* instruction ,uint8_t value){
	// clear nextion_instr_string
	memset(nextion_instr_string,0,strlen(nextion_instr_string));
	// append instruction
	strcat(nextion_instr_string,instruction);
	// convert value to string
	sprintf(nextion_instr_int,"%d",value);
	// append string value to instruction
	strcat(nextion_instr_string, nextion_instr_int);
	// append end of instruction
	strcat(nextion_instr_string,nextion_instr_end);
	// send instruction
	nextion_send((uint8_t*) nextion_instr_string);
}
/**
 * @brief	Send an instruction requiring string value
 * @param	instruction
 * @param	value
 */
void instruction_nextion_send_str(char* instruction,char * value){
	// clear nextion_instr_string
	memset(nextion_instr_string,0,strlen(nextion_instr_string));
	// append instruction
	strcat(nextion_instr_string,instruction);
	// surround text value with ""
	strcat(nextion_instr_string, "\"");
	// append string value to instruction
	strcat(nextion_instr_string, value);
	strcat(nextion_instr_string, "\"");
	// append end of instruction
	strcat(nextion_instr_string,nextion_instr_end);
	// send instruction
	nextion_send((uint8_t*) nextion_instr_string);
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
