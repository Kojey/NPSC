/**
  ******************************************************************************
  * @file    NPCS_nextion.h
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    12 Oct-2017
  * @brief   This file contains all the configuration prototypes used by the
  * 			nextion firmware
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  *
  ******************************************************************************
  */

#ifndef NPC_INC_NPSC_nextion_H_
#define NPC_INC_NPSC_nextion_H_

/* Includes ------------------------------------------------------------------*/
#include "NPC_utils.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @addtogroup nextion
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/**
 * @defgroup nextion_Constants
 * @brief	define nextion constant
 * @{
 */
#define NEXTION_PERIPH_USARTX			RCC_APB1Periph_USART2
#define NEXTION_PERIPH_GPIOX			RCC_AHB1Periph_GPIOA
#define NEXTION_GPIOX					GPIOA
#define NEXTION_TX_PIN					GPIO_Pin_2
#define NEXTION_RX_PIN					GPIO_Pin_3
#define NEXTION_TX_PINSOURCE			GPIO_PinSource2
#define NEXTION_RX_PINSOURCE			GPIO_PinSource3
#define NEXTION_AF_USART				GPIO_AF_USART2
#define NEXTION_USARTX					USART2
#define NEXTION_USARTX_IRQ				USART2_IRQn
#define NEXTION_BAUDRATE				9600
/**
 * @}
 */
/* Exported variables --------------------------------------------------------*/
size_t nextion_write, nextion_read;
/* Exported macro ------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/*  Function used to initialize the nextion device and handle transmission *****/
/**	@defgroup nextion_Init
 * 	@{
 */
void nextion_init(void);
void USART2_IRQHandler(void);
void DMA1_Stream5_IRQHandler(void);
/**
 * @}
 */

/*	Function used to manage transmission between NPC and Phone Application*/
/**	@defgroup nextion_Trans
 *  @{
 */
void nextion_send(uint8_t * data);

/**
 * @}
 */

#endif /* NPC_INC_NPC_nextion_H_ */

/**
 * 	@}
 */
/**
 * @}
 */
/**
 * @}
 */
