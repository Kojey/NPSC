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

#ifndef NPSC_APPLICATION_INC_INSTRUCTIONS_H_
#define NPSC_APPLICATION_INC_INSTRUCTIONS_H_

/* Includes ------------------------------------------------------------------*/
#include "NPSC_nextion.h"
#include "NPSC_bluetooth.h"
#include "NPSC_rtc.h"

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
void instruction_nextion_start(void);
void instruction_nextion_stop(void);
void instruction_nextion_send_int(char *,int);
void instruction_nextion_send_str(char *,char *);
#endif /* NPSC_APPLICATION_INC_INSTRUCTIONS_H_ */

/**
 * @}
 */
/**
 * @}
 */
/**
 * @}
 */
