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
			rtc_setClockStruct(&clock);
			break;
		case 0x01:
			// get clock
			clock = rtc_getClockStruct();
 			instruction_nextionStart();
			instruction_nextionSendInt("home.n0.val=",clock.time.RTC_Hours);
			instruction_nextionSendInt("home.n1.val=",clock.time.RTC_Minutes);
			instruction_nextionSendStr("home.t1.txt=", rtc_dayToString(clock.date.RTC_WeekDay) );
			instruction_nextionSendInt("home.n3.val=",clock.date.RTC_Date);
			instruction_nextionSendStr("home.t2.txt=", rtc_MonthToString(clock.date.RTC_Month) );
			instruction_nextionSendInt("home.n4.val=",2000+clock.date.RTC_Year);
			instruction_nextionStop();
  			break;
		case 0x02:
			instruction_nextionStart();
			instruction_nextionSendInt("n0.val=",12);
			instruction_nextionStop();
			break;
		default:
			break;
		}
	}
}

/**
 * @brief	Send junk data to start communication with screen
 */
void instruction_nextionStart(void){
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
void instruction_nextionStop(void){
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
void instruction_nextionSendInt(char* instruction ,int value){
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
void instruction_nextionSendStr(char* instruction,char * value){
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
