/**
  ******************************************************************************
  * @file    PC_bluetooth.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    01-March-2017
  * @brief	 This file provides firmware functions to manage the bluetooth
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "../inc/NPC_bluetooth.h"

/** @addtogroup NPC
  * @{
  */

/** @defgroup Bluetooth
  * @brief Bluetooth driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**	@defgroup Initialization Initialization and transmission handler functions
 * 	@brief	Bluetooth initialization functions
 *
@verbatim
 ===============================================================================
         ##### Bluetooth initialization functions #####
 ===============================================================================

 [..] This section provide functions allowing to initialize the bluetooth.

@endverbatim
  * @{
  */

/**
 * @brief	Initialize the bluetooth and set baudrate to 9600
 * @param 	None
 * @retval	None
 */
void bluetooth_init(void){
	// Enable RCC for USART1, GPIOB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD,ENABLE);

	// GPIO Configuration
	{
		GPIO_InitTypeDef GPIO_InitStructure;

		// Configure PD13 as output
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

		GPIO_Init(GPIOD,&GPIO_InitStructure);

		// Configure USART1 TX (PB6) as alternate function push-pull
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

		GPIO_Init(GPIOB,&GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1);

	}

	// NVIC Configuration
	{
		NVIC_InitTypeDef NVIC_InitStructure;

		NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

		NVIC_Init(&NVIC_InitStructure);
	}

	// USART Configuration
	{
		USART_InitTypeDef USART_InitStructure;

		USART_InitStructure.USART_BaudRate = 9600;//38400;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;

		USART_Init(USART1,&USART_InitStructure);

		// Enable USART1 receive and transmission complete interrupts
		USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

		USART_Cmd(USART1,ENABLE);

	}

	uint8_t welcome_str[] = "Welcome to NeoPixelClock!\r\n";
	bluetooth_send(welcome_str);
}

/**
 * @brief	USART1 Interrupt Handler
 * @param 	None
 * @retval	none
 */
void USART1_IRQHandler(void){
	// Wait until reception
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==RESET);
	uint8_t data = toupper(bluetooth_receive());
	if(data=='R'){
		pixel_color='R';
		bluetooth_send((uint8_t *)"Red\n\r");
	}
	else if(data=='G'){
		pixel_color='G';
		bluetooth_send((uint8_t *)"Green\n\r");
	}
	else if(data=='B'){
		pixel_color='B';
		bluetooth_send((uint8_t *)"Blue\n\r");
	}
	else if(data=='Y'){
		pixel_color='Y';
		bluetooth_send((uint8_t *)"Yellow\n\r");
	}
	else if(data=='M'){
		pixel_color='M';
		bluetooth_send((uint8_t *)"Magenta\n\r");
	}
	else if(data=='C'){
		pixel_color='C';
		bluetooth_send((uint8_t *)"Cyan\n\r");
	}
	else if(data=='D'){
		pixel_color='D';
		bluetooth_send((uint8_t *)"Dark\n\r");
	}
	else if(data=='W'){
		pixel_color='W';
		bluetooth_send((uint8_t *)"White\n\r");
	}
}

/**
 * @}
 */

/**	@defgroup Transmission Transmission functions
 * 	@brief	Bluetooth transmission functions
 *
@verbatim
 ===============================================================================
         ##### Bluetooth transmission functions #####
 ===============================================================================

 [..] This section provide functions allowing to transmit and receive data.

@endverbatim
  * @{
  */

/**
 * @brief 	send string to the hc-06
 * @param	data: string to be sent
 * @retval	None
 */
void bluetooth_send(uint8_t * data){
	uint32_t size = strlen((char *)data);
	while(size--){
		USART_SendData(USART1,(uint16_t)*data++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	}
}

/**
 * @brief	receive a byte from hc-06
 * @param	None
 * @retval	An uint8_t byte of data
 */
uint8_t bluetooth_receive(void){
	return USART_ReceiveData(USART1);
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
