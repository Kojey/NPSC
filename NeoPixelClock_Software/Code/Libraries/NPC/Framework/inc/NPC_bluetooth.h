/**
  ******************************************************************************
  * @file    NPC_bluetooth.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    01-March-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			bluetooth firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_NPC_BLUETOOTH_H_
#define NPC_INC_NPC_BLUETOOTH_H_

/* Includes ------------------------------------------------------------------*/
#include "NPC_utils.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Bluetooth
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*  Function used to initialize the bluetooth device and handle transmission *****/
void bluetooth_init(void);
void USART1_IRQHandler(void);
/*	Function used to manage transmission between NPC and Phone Application*/
void bluetooth_send(uint8_t * data);
uint8_t bluetooth_receive(void);

#endif /* NPC_INC_NPC_BLUETOOTH_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
