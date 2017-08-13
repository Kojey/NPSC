/**
  ******************************************************************************
  * @file    NPC_slave.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    10-April-2017
  * @brief	 This file provides firmware functions to manage the slave
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "../inc/NPC_slave.h"

/** @addtogroup NPC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup Slave
  * @brief Slave driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**	@defgroup Slave Initialization and transmission handler functions
 * 	@brief	Slave initialization functions
 *  @{
 */

/**
 * @brief	Initialize the slave and set baudrate to 9600
 * @param 	None
 * @retval	None
 */
void slave_init(void){
	// Enable RCC for USART2, GPIOA
	RCC_APB1PeriphClockCmd(SLAVE_PERIPH_USARTX,ENABLE);
	RCC_AHB1PeriphClockCmd(SLAVE_PERIPH_GPIOX,ENABLE);

	// GPIO Configuration
	{
		GPIO_InitTypeDef GPIO_InitStructure;

		// Configure USART1 TX (PB6) as alternate function push-pull
		GPIO_InitStructure.GPIO_Pin = SLAVE_TX_PIN | SLAVE_RX_PIN;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

		GPIO_Init(BLUETTOTH_GPIOX, &GPIO_InitStructure);

		GPIO_PinAFConfig(BLUETTOTH_GPIOX, SLAVE_TX_PINSOURCE, SLAVE_AF_USART);
		GPIO_PinAFConfig(BLUETTOTH_GPIOX, SLAVE_RX_PINSOURCE, SLAVE_AF_USART);

	}

	// NVIC Configuration
	{
		NVIC_InitTypeDef NVIC_InitStructure;

		NVIC_InitStructure.NVIC_IRQChannel = SLAVE_USARTX_IRQ;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStructure);
	}

	// USART Configuration
	{
		USART_InitTypeDef USART_InitStructure;

		USART_InitStructure.USART_BaudRate = SLAVE_BAUDRATE;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;

		USART_Init(SLAVE_USARTX,&USART_InitStructure);

		// Enable USART1 receive and transmission complete interrupts
		USART_ITConfig(SLAVE_USARTX,USART_IT_RXNE,ENABLE);

		USART_Cmd(SLAVE_USARTX,ENABLE);

	}
}

/**
 * @brief	USART2 Interrupt Handler
 * @param 	None
 * @retval	none
 */
void USART2_IRQHandler(void){
	// Wait until reception
	while(USART_GetFlagStatus(SLAVE_USARTX, USART_FLAG_RXNE)==RESET);
	slave_receive();
}

/**
 * @}
 */

/**	@defgroup Slave_Trans Transmission functions
 * 	@brief	Slave transmission functions
 * @{
 */

/**
 * @brief 	send string to the slave
 * @param	data: string to be sent
 * @retval	None
 */
void slave_send(uint8_t * data){
	uint32_t size = strlen((char *)data);
	while(size--){
		USART_SendData(SLAVE_USARTX,(uint16_t)*data++);
		while(USART_GetFlagStatus(SLAVE_USARTX,USART_FLAG_TC)==RESET);
	}
}

/**
 * @brief	receive a byte from slave
 * @param	None
 * @retval	An uint8_t byte of data
 */
uint8_t slave_receive(void){
	return USART_ReceiveData(SLAVE_USARTX);
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
/**
 * @}
 */
