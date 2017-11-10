/**
  ******************************************************************************
  * @file    nextion.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    12-October-2017
  * @brief	 This file provides firmware functions to manage the nextion
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <nextion.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup nextion
  * @brief nextion driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
bool nextion_instruction = false;
/* Private functions ---------------------------------------------------------*/

/**	@defgroup nextion_Init Initialization and transmission handler functions
 * 	@brief	nextion initialization functions
 *  @{
 */

/**
 * @brief	Initialize the nextion and set baudrate to 9600
 * @param 	None
 * @retval	None
 */
void nextion_init(void) {

    /* Init GPIO pins for UART */
	RCC_APB1PeriphClockCmd(NEXTION_PERIPH_USARTX,ENABLE);
	RCC_AHB1PeriphClockCmd(NEXTION_PERIPH_GPIOX | RCC_AHB1ENR_DMA1EN ,ENABLE);


    /* Init GPIO pins */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_PinAFConfig(NEXTION_GPIOX, NEXTION_TX_PINSOURCE, NEXTION_AF_USART);
	GPIO_PinAFConfig(NEXTION_GPIOX, NEXTION_RX_PINSOURCE, NEXTION_AF_USART);
	GPIO_InitStruct.GPIO_Pin = NEXTION_TX_PIN | NEXTION_RX_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(NEXTION_GPIOX, &GPIO_InitStruct);

    /* Configure UART setup */
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = NEXTION_BAUDRATE;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(NEXTION_USARTX,&USART_InitStruct);

    /* Enable global interrupts for USART */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = NEXTION_USARTX_IRQ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

    /* Enable USART */
    USART_Cmd(NEXTION_USARTX, ENABLE);
    USART_DMACmd(NEXTION_USARTX, USART_DMAReq_Rx, ENABLE);
    /* Enable IDLE line detection for DMA processing */
    USART_ITConfig(NEXTION_USARTX, USART_IT_IDLE, ENABLE);

    /* Configure DMA for USART RX, DMA1, Stream5, Channel4 */

    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.DMA_Channel = DMA_Channel_4;
    DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)DMA_RX_Buffer;
    DMA_InitStruct.DMA_BufferSize = DMA_RX_BUFFER_SIZE;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_Init(DMA1_Stream5, &DMA_InitStruct);

    /* Enable global interrupts for DMA stream */
    NVIC_InitStruct.NVIC_IRQChannel = DMA1_Stream5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    /* Enable transfer complete interrupt */
    DMA_ITConfig(DMA1_Stream5, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA1_Stream5, ENABLE);

}

/**
 * @brief       Global interrupt handler for USART2
 */
void USART2_IRQHandler(void) {
    /* Check for IDLE flag */
    if (USART2->SR & USART_FLAG_IDLE) {         /* We want IDLE flag only */
        /* This part is important */
        /* Clear IDLE flag by reading status register first */
        /* And follow by reading data register */
        volatile uint32_t tmp;                  /* Must be volatile to prevent optimizations */
        tmp = USART2->SR;                       /* nextion_read status register */
        tmp = USART2->DR;                       /* nextion_read data register */
        (void)tmp;                              /* Prevent compiler warnings */
        DMA1_Stream5->CR &= ~DMA_SxCR_EN;       /* Disabling DMA will force transfer complete interrupt if enabled */
    }
}

/**
 * @brief       Global interrupt handler for DMA1 stream5
 */
void DMA1_Stream5_IRQHandler(void) {
	if (DMA1->HISR & DMA_FLAG_TCIF5) {
        DMA1->HIFCR = DMA_FLAG_TCIF5; 		/*  Clear transfer complete flag  */

        nextion_instruction = true;

////    	if(nextion_instruction){
//    	    /* Extract all instruction from DMA */
//    	    for(uint8_t index=0; index<DMA_MAX_INSTRUCTION; ++index){
//    	    	/* Check for validity of instruction  */
//    	    	if(instruction_valid(DMA_RX_Buffer[index*INSTRUCTION_SIZE])
//    	    			&& !instruction_ack(&DMA_RX_Buffer[index*INSTRUCTION_SIZE])){
//    				InstructionTypeDef newInstruction;
//    				for(int i=0; i<INSTRUCTION_SIZE; i++){
//    					newInstruction.instrution[i]=DMA_RX_Buffer[index*INSTRUCTION_SIZE+i];
//    					// clear DMA_RX_Buffer
//    					DMA_RX_Buffer[index*INSTRUCTION_SIZE+i]=0;
//    				}
//    				newInstruction.excecuted=false;
//    				// add it to the queue
//    				InstructionQueue_enqueue(instruction_queue,&newInstruction);
//    	    	}
//    	    }
////    	    nextion_instruction= false;
////    	}

        /*Prepare DMA for next transfer
		Important! DMA stream won't start if all flags are not cleared first */
        DMA1->HIFCR = DMA_FLAG_DMEIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_HTIF5 | DMA_FLAG_TCIF5 | DMA_FLAG_TEIF5;
        DMA1_Stream5->M0AR = (uint32_t)DMA_RX_Buffer;   /* Set memory address for DMA again */
        DMA1_Stream5->NDTR = DMA_RX_BUFFER_SIZE;    /* Set number of bytes to receive */
        DMA1_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
    }
}

/**
 *
 */
void nextion_instructionUpdate(void){
	if(nextion_instruction){
	    /* Extract all instruction from DMA */
	    for(uint8_t index=0; index<DMA_MAX_INSTRUCTION; ++index){
	    	/* Check for validity of instruction  */
	    	if(instruction_valid(DMA_RX_Buffer[index*INSTRUCTION_SIZE])
	    			&& !instruction_ack(&DMA_RX_Buffer[index*INSTRUCTION_SIZE])){
				InstructionTypeDef newInstruction;
				for(int i=0; i<INSTRUCTION_SIZE; i++){
					newInstruction.instrution[i]=DMA_RX_Buffer[index*INSTRUCTION_SIZE+i];
					// clear DMA_RX_Buffer
					DMA_RX_Buffer[index*INSTRUCTION_SIZE+i]=0;
				}
				newInstruction.excecuted=false;
				// add it to the queue
				InstructionQueue_enqueue(instruction_queue,&newInstruction);
	    	}
	    }
	    nextion_instruction= false;
	}
}
/**
 * @}
 */

/**	@defgroup nextion_Trans Transmission functions
 * 	@brief	nextion transmission functions
 * @{
 */

/**
 * @brief 	send string to the hc-06
 * @param	data: string to be sent
 * @retval	None
 */
void nextion_send(uint8_t * data){
	uint32_t size = strlen((char *)data);
	while(size--){
		USART_SendData(NEXTION_USARTX,(uint16_t)*data++);
		while(USART_GetFlagStatus(NEXTION_USARTX,USART_FLAG_TC)==RESET);
	}
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
