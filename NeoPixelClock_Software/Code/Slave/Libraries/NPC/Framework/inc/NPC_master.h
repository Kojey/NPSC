/**
  ******************************************************************************
  * @file    NPC_master.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    11-April-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			master microcontroller
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_NPC_MASTER_H_
#define NPC_INC_NPC_MASTER_H_

/* Includes ------------------------------------------------------------------*/
#include "NPC_utils.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup Master
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @defgroup Master_Constants
 * @brief	define master constant
 * @{
 */
#define MASTER_PERIPH_USARTX			RCC_APB1Periph_USART2
#define MASTER_PERIPH_GPIOX			RCC_AHB1Periph_GPIOA
#define MASTER_GPIOX				GPIOA
#define MASTER_TX_PIN				GPIO_Pin_2
#define MASTER_RX_PIN				GPIO_Pin_3
#define MASTER_TX_PINSOURCE			GPIO_PinSource2
#define MASTER_RX_PINSOURCE			GPIO_PinSource3
#define MASTER_AF_USART				GPIO_AF_USART2
#define MASTER_USARTX				USART2
#define MASTER_USARTX_IRQ			USART2_IRQn
#define MASTER_BAUDRATE				9600
/**
 * @}
 */
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*  Function used to initialize the MASTER device and handle transmission *****/
/**	@defgroup MASTER_Init
 * 	@{
 */
void master_init(void);
void USART2_IRQHandler(void);
/**
 * @}
 */

/*	Function used to manage transmission between NPC and Phone Application*/
/**	@defgroup MASTER_Trans
 *  @{
 */
void master_send(uint8_t * data);
uint8_t master_receive(void);
/**
 * @}
 */

#endif /* NPC_INC_NPC_MASTER_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
