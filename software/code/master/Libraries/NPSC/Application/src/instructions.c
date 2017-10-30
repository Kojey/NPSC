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
#include "alarm.h"

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
static bool b = true;
void instruction_execute(void){
	RTC_ClockTypeDef clock;
	AlarmTypeDef alarm;

	while(instruction_queue->size){
		// fecth instruction
		InstructionTypeDef _instruction = InstructionQueue_dequeue(instruction_queue);
		// decode and execute instruction
		switch(_instruction.instrution[0]){
		/* External RTC instructions */
		case 0x01:
			// set clock
			clock.date.RTC_Year=_instruction.instrution[1];
			clock.date.RTC_Month=_instruction.instrution[2];
			clock.date.RTC_Date=_instruction.instrution[3];
			clock.date.RTC_WeekDay=_instruction.instrution[4];
			clock.time.RTC_Hours=_instruction.instrution[5];
			clock.time.RTC_Minutes=_instruction.instrution[6];
			clock.time.RTC_Seconds=_instruction.instrution[7];
			clock.time.RTC_H12=RTC_H12_AM;
			rtc_setClockStruct(&clock);
			break;
		case 0x02:
			// get clock
			clock = rtc_getClockStruct();
				if(b){
					alarm_synchronize();
					b=false;
				}
 			instruction_nextionStart();
			instruction_nextionSendInt("home.n0.val=",clock.time.RTC_Hours);
			instruction_nextionSendInt("home.n1.val=",clock.time.RTC_Minutes);
			instruction_nextionSendStr("home.t1.txt=", rtc_dayToString(clock.date.RTC_WeekDay) );
			instruction_nextionSendInt("home.n3.val=",clock.date.RTC_Date);
			instruction_nextionSendStr("home.t2.txt=", rtc_monthToString(clock.date.RTC_Month) );
			instruction_nextionSendInt("home.n4.val=",2000+clock.date.RTC_Year);
			instruction_nextionStop();
  			break;
  		/* Alarm instructions */
		case 0x10:
			alarm = alarm_load(_instruction.instrution[1]);
			// set alarm time params
			//alarm.id=_instruction.instrution[1];
			alarm.alarm.RTC_AlarmTime.RTC_Hours=_instruction.instrution[2];
			alarm.alarm.RTC_AlarmTime.RTC_Minutes=_instruction.instrution[3];
			alarm.alarm.RTC_AlarmDateWeekDaySel=rtc_weekdaySelTo32Bits(_instruction.instrution[4]);
			alarm.alarm.RTC_AlarmDateWeekDay=_instruction.instrution[5];
			alarm.repeat=_instruction.instrution[6];
			alarm.alarm.RTC_AlarmMask=rtc_alarmMaskTo32Bits(_instruction.instrution[6]);
			alarm.alarm.RTC_AlarmTime.RTC_H12=RTC_H12_AM;
			alarm.alarm.RTC_AlarmTime.RTC_Seconds=0;
			break;
		case 0x11:
			// set alarm extra params
			alarm.ringtone=_instruction.instrution[2];
			alarm.pattern=_instruction.instrution[3];
			alarm.enable=_instruction.instrution[4];
			alarm.fetched=_instruction.instrution[5];
			break;
		case 0x12:
			// set alarm label
			// get string from instruction
			get_stringFromInstruction((char *)label_instruction, (char *)&_instruction.instrution[4],LABEL_INSTR_SIZE);
			if (_instruction.instrution[2]==0)
				strcpy(label,label_instruction);
			else {
				strcat(label,label_instruction);
				strcpy(alarm.label,label);
				// last instruction
				 if(_instruction.instrution[2]==2){
					 // save alarm
					 alarm_save(&alarm);
					 alarm_update(true);
				 }
			}
			break;
		case 0x13:
			// set alarm enable
			alarm = alarm_load(_instruction.instrution[1]);
			alarm.enable = _instruction.instrution[2];
			alarm_save(&alarm);
			break;
		case 0x14:
			// get alarm min params
			instruction_nextionStart();
			// update first alarm
			alarm = alarm_load(_instruction.instrution[1]);
			instruction_nextionSendInt("n0.val=",alarm.alarm.RTC_AlarmTime.RTC_Hours);
			instruction_nextionSendInt("n1.val=",alarm.alarm.RTC_AlarmTime.RTC_Minutes);
			instruction_nextionSendStr("t1.txt=",alarm.label);
			instruction_nextionSendInt("bt0.val=",alarm.enable);
			// update second alarm
			alarm = alarm_load(_instruction.instrution[2]);
			instruction_nextionSendInt("n2.val=",alarm.alarm.RTC_AlarmTime.RTC_Hours);
			instruction_nextionSendInt("n3.val=",alarm.alarm.RTC_AlarmTime.RTC_Minutes);
			instruction_nextionSendStr("t2.txt=",alarm.label);
			instruction_nextionSendInt("bt1.val=",alarm.enable);
			instruction_nextionStop();
			break;
		case 0x15:
			// get alarm  params
			instruction_nextionStart();
			alarm = alarm_load(_instruction.instrution[1]);
			instruction_nextionSendStr("t6.txt=",alarm_repeatToString(alarm.repeat));
			instruction_nextionSendStr("t7.txt=",alarm_ringToneToString(alarm.ringtone));
			instruction_nextionSendStr("t8.txt=",alarm_patternToString(alarm.pattern));
			instruction_nextionSendStr("t9.txt=",alarm.label);
			instruction_nextionSendInt("n0.val=",alarm.alarm.RTC_AlarmTime.RTC_Hours);
			instruction_nextionSendInt("n1.val=",alarm.alarm.RTC_AlarmTime.RTC_Minutes);
			instruction_nextionSendInt("bt0.val=",alarm.enable);
			instruction_nextionSendStr("t11.txt=",rtc_dayToString(alarm.alarm.RTC_AlarmDateWeekDay));
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
