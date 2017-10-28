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

#ifndef NPSC_APPLICATION_INSTRUCTIONS_H_
#define NPSC_APPLICATION_INSTRUCTIONS_H_

/* Includes ------------------------------------------------------------------*/
#include "bluetooth.h"
#include "nextion.h"
#include "rtc.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Application
 *
 */
/** @addtogroup Instructions
  * @{
  */


/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void instruction_execute(void);
void instruction_nextionStart(void);
void instruction_nextionStop(void);
void instruction_nextionSendInt(char *,int);
void instruction_nextionSendStr(char *,char *);
#endif /* NPSC_APPLICATION_INSTRUCTIONS_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
