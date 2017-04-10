/**
  ******************************************************************************
  * @file    NPC_UART_communication.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    10-April-2017
  * @brief   This file contains all the configuration prototypes to setup
  * 			a UART communication
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_NPC_SLAVE_H_
#define NPC_INC_NPC_SLAVE_H_

/* Includes ------------------------------------------------------------------*/
#include "NPC_utils.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup UART
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*  Function used to initialize the bluetooth device and handle transmission *****/
/**	@defgroup UART_init
 * 	@{
 */
void uart_init(void);
void USART1_IRQHandler(void);
/**
 * @}
 */

/*	Function used to manage transmission between NPC and Phone Application*/
/**	@defgroup Bluetooth_Trans
 *  @{
 */
void uart_send(uint8_t * data);
uint8_t bluetooth_receive(void);
/**
 * @}
 */

#endif /* NPC_INC_NPC_SLAVE_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
