/*
 * bluetooth.c
 *
 *  Created on: 01 Mar 2017
 *      Author: Kojey
 */


#include "../inc/bluetooth.h"

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

	uint8_t welcome_str[] = " Welcome to Bluetooth!\r\n";
	bluetooth_send(welcome_str);//,sizeof(welcome_str));
}


void USART1_IRQHandler(void){
	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE)==RESET);
	uint8_t data = USART_ReceiveData(USART1);
	if(data=='1'){
		GPIO_WriteBit(GPIOD,GPIO_Pin_13,SET);
		bluetooth_send((uint8_t *)"LED ON\n\r");//,sizeof("LED ON\n\r")-1);
	}
	else if(data=='0'){
		GPIO_WriteBit(GPIOD,GPIO_Pin_13,RESET);
		bluetooth_send((uint8_t *)"LED OFF\n\r");//,sizeof("LED OFF\n\r")-1);
	}
	else if(data=='?'){
		bluetooth_send((uint8_t *)"SEND '1' TO TURN LED ON\n\r");//,sizeof("SEND '1' TO TURN LED ON\n\r")-1);
		bluetooth_send((uint8_t *)"SEND '0' TO TURN LED OFF\n\r");//,sizeof("SEND '0' TO TURN LED OFF\n\r")-1);
	}
}



void bluetooth_send(uint8_t * data){
	uint32_t size = strlen((char *)data);
	while(size--){
		USART_SendData(USART1,(uint16_t)*data++);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
	}
}
