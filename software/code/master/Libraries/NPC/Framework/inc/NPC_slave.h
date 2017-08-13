/**
  ******************************************************************************
  * @file    NPC_slave.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    10-April-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			slave microcontroller
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
/** @addtogroup Slave
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @defgroup Slave_Constants
 * @brief	define slave constant
 * @{
 */
#define SLAVE_PERIPH_USARTX			RCC_APB1Periph_USART2
#define SLAVE_PERIPH_GPIOX			RCC_AHB1Periph_GPIOA
#define BLUETTOTH_GPIOX				GPIOA
#define SLAVE_TX_PIN				GPIO_Pin_2
#define SLAVE_RX_PIN				GPIO_Pin_3
#define SLAVE_TX_PINSOURCE			GPIO_PinSource2
#define SLAVE_RX_PINSOURCE			GPIO_PinSource3
#define SLAVE_AF_USART				GPIO_AF_USART2
#define SLAVE_USARTX				USART2
#define SLAVE_USARTX_IRQ			USART2_IRQn
#define SLAVE_BAUDRATE				9600
/**
 * @}
 */
/* Exported variables --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*  Function used to initialize the SLAVE device and handle transmission *****/
/**	@defgroup SLAVE_Init
 * 	@{
 */
void slave_init(void);
void USART2_IRQHandler(void);
/**
 * @}
 */

/*	Function used to manage transmission between NPC and Phone Application*/
/**	@defgroup SLAVE_Trans
 *  @{
 */
void slave_send(uint8_t * data);
uint8_t slave_receive(void);
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
