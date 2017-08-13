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
/**
 * @defgroup BLUETOOTH_Constants
 * @brief	define bluetooth constant
 * @{
 */
#define BLUETOOTH_PERIPH_USARTX			RCC_APB2Periph_USART1
#define BLUETOOTH_PERIPH_GPIOX			RCC_AHB1Periph_GPIOB
#define BLUETOOTH_GPIOX					GPIOB
#define BLUETOOTH_TX_PIN				GPIO_Pin_6
#define BLUETOOTH_RX_PIN				GPIO_Pin_7
#define BLUETOOTH_TX_PINSOURCE			GPIO_PinSource6
#define BLUETOOTH_RX_PINSOURCE			GPIO_PinSource7
#define BLUETOOTH_AF_USART				GPIO_AF_USART1
#define BLUETOOTH_USARTX				USART1
#define BLUETOOTH_USARTX_IRQ			USART1_IRQn
#define BLUETOOTH_BAUDRATE				9600
/**
 * @}
 */
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*  Function used to initialize the bluetooth device and handle transmission *****/
/**	@defgroup Bluetooth_Init
 * 	@{
 */
void bluetooth_init(void);
void USART1_IRQHandler(void);
/**
 * @}
 */

/*	Function used to manage transmission between NPC and Phone Application*/
/**	@defgroup Bluetooth_Trans
 *  @{
 */
void bluetooth_send(uint8_t * data);
uint8_t bluetooth_receive(void);
/**
 * @}
 */

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
