/**
  ******************************************************************************
  * @file    bluetooth.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    12-October-2017
  * @brief	 This file provides firmware functions to manage the bluetooth
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include <bluetooth.h>

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup bluetooth
  * @brief bluetooth driver modules
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**	@defgroup bluetooth_Init Initialization and transmission handler functions
 * 	@brief	bluetooth initialization functions
 *  @{
 */

/**
 * @brief	Initialize the bluetooth and set baudrate to 9600
 * @param 	None
 * @retval	None
 */
void bluetooth_init(void) {

    /* Init GPIO pins for UART */
	RCC_APB2PeriphClockCmd(BLUETOOTH_PERIPH_USARTX,ENABLE);
	RCC_AHB1PeriphClockCmd(BLUETOOTH_PERIPH_GPIOX | RCC_AHB1ENR_DMA2EN ,ENABLE);


    /* Init GPIO pins */
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_PinAFConfig(BLUETOOTH_GPIOX, BLUETOOTH_TX_PINSOURCE, BLUETOOTH_AF_USART);
	GPIO_PinAFConfig(BLUETOOTH_GPIOX, BLUETOOTH_RX_PINSOURCE, BLUETOOTH_AF_USART);
	GPIO_InitStruct.GPIO_Pin = BLUETOOTH_TX_PIN | BLUETOOTH_RX_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(BLUETOOTH_GPIOX, &GPIO_InitStruct);

    /* Configure UART setup */
	USART_InitTypeDef USART_InitStruct;
	USART_InitStruct.USART_BaudRate = BLUETOOTH_BAUDRATE;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	USART_Init(BLUETOOTH_USARTX,&USART_InitStruct);

    /* Enable global interrupts for USART */
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = BLUETOOTH_USARTX_IRQ;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);

    /* Enable USART */
    USART_Cmd(BLUETOOTH_USARTX, ENABLE);
    USART_DMACmd(BLUETOOTH_USARTX, USART_DMAReq_Rx, ENABLE);
    /* Enable IDLE line detection for DMA processing */
    USART_ITConfig(BLUETOOTH_USARTX, USART_IT_IDLE, ENABLE);

    /* Configure DMA for USART RX, DMA2, Stream5, Channel4 */

    DMA_InitTypeDef DMA_InitStruct;
    DMA_StructInit(&DMA_InitStruct);
    DMA_InitStruct.DMA_Channel = DMA_Channel_4;
    DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)DMA_RX_Buffer;
    DMA_InitStruct.DMA_BufferSize = DMA_RX_BUFFER_SIZE;
    DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
    DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_Init(DMA2_Stream5, &DMA_InitStruct);

    /* Enable global interrupts for DMA stream */
    NVIC_InitStruct.NVIC_IRQChannel = DMA2_Stream5_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 4;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
    NVIC_Init(&NVIC_InitStruct);

    /* Enable transfer complete interrupt */
    DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);
    DMA_Cmd(DMA2_Stream5, ENABLE);

}

/**
 * MUST BE A TASK
 */
void bluetooth_bufferUpdate(void){
    /**
     * Loop data back to UART data register
     */
    while (bluetooth_read != bluetooth_write) {                 /* Do it until buffer is empty */
    	// lock this step
    	if(instruction_lock_owner==instruction_no_lock || instruction_lock_owner==instruction_bluetooth_lock){
    		USART1->DR = INSTRUCTION_BUFFER[bluetooth_read++];   /* Start byte transfer */
    		if(instruction_lock_owner==instruction_no_lock)instruction_lock_owner=instruction_bluetooth_lock;

			while (!(USART1->SR & USART_SR_TXE));   /* Wait till finished */
			if (bluetooth_read == INSTRUCTION_SIZE) {     /* Check buffer overflow */
				bluetooth_read = 0;
				bluetooth_write = 0;
				// create new instruction
				InstructionTypeDef newInstruction;
				int i;
				for(i=0; i<INSTRUCTION_SIZE; i++)
					newInstruction.instrution[i]=INSTRUCTION_BUFFER[i];
				newInstruction.excecuted=false;
				// add it to the queue
				InstructionQueue_enqueue(instruction_queue,&newInstruction);
				// release the lock
				instruction_lock_owner = instruction_no_lock;
			}
    	}
    }
}

/**
 * \brief       Global interrupt handler for USART1
 */
void USART1_IRQHandler(void) {
    /* Check for IDLE flag */
    if (USART1->SR & USART_FLAG_IDLE) {         /* We want IDLE flag only */
        /* This part is important */
        /* Clear IDLE flag by reading status register first */
        /* And follow by reading data register */
        volatile uint32_t tmp;                  /* Must be volatile to prevent optimizations */
        tmp = USART1->SR;                       /* bluetooth_read status register */
        tmp = USART1->DR;                       /* bluetooth_read data register */
        (void)tmp;                              /* Prevent compiler warnings */
        DMA2_Stream5->CR &= ~DMA_SxCR_EN;       /* Disabling DMA will force transfer complete interrupt if enabled */
    }
}

/**
 * \brief       Global interrupt handler for DMA2 stream5
 * \note        Except memcpy, there is no functions used to
 */
void DMA2_Stream5_IRQHandler(void) {

//    neopixel_setAllPixelRGB(0,0,1);
//    /* Check transfer complete flag */
    if (DMA2->HISR & DMA_FLAG_TCIF5) {
        DMA2->HIFCR = DMA_FLAG_TCIF5;           /* Clear transfer complete flag */
//
//        /* Calculate number of bytes actually transfered by DMA so far */
//        /**
//         * Transfer could be completed by 2 events:
//         *  - All data actually transfered (NDTR = 0)
//         *  - Stream disabled inside USART IDLE line detected interrupt (NDTR != 0)
//         */
//        len = DMA_RX_BUFFER_SIZE - DMA2_Stream5->NDTR;
//        tocopy = INSTRUCTION_SIZE - bluetooth_write;      /* Get number of bytes we can copy to the end of buffer */
//
//        /* Check how many bytes to copy */
//        if (tocopy > len) {
//            tocopy = len;
//        }
//
//        /* bluetooth_write received data for UART main buffer for manipulation later */
//        ptr = DMA_RX_Buffer;
//        memcpy(&INSTRUCTION_BUFFER[bluetooth_write], ptr, tocopy);   /* Copy first part */
//
//        /* Correct values for remaining data */
//        bluetooth_write += tocopy;
//        len -= tocopy;
//        ptr += tocopy;
//
//        /* If still data to write for beginning of buffer */
//        if (len) {
//            memcpy(&INSTRUCTION_BUFFER[0], ptr, len);      /* Don't care if we override bluetooth_read pointer now */
//            bluetooth_write = len;
//        }

        /* Prepare DMA for next transfer */
        /* Important! DMA stream won't start if all flags are not cleared first */
        DMA2->HIFCR = DMA_FLAG_DMEIF5 | DMA_FLAG_FEIF5 | DMA_FLAG_HTIF5 | DMA_FLAG_TCIF5 | DMA_FLAG_TEIF5;
        DMA2_Stream5->M0AR = (uint32_t)DMA_RX_Buffer;   /* Set memory address for DMA again */
        DMA2_Stream5->NDTR = DMA_RX_BUFFER_SIZE;    /* Set number of bytes to receive */
        DMA2_Stream5->CR |= DMA_SxCR_EN;            /* Start DMA transfer */
    }
}


/**
 * @}
 */

/**	@defgroup bluetooth_Trans Transmission functions
 * 	@brief	bluetooth transmission functions
 * @{
 */

/**
 * @brief 	send string to the hc-06
 * @param	data: string to be sent
 * @retval	None
 */
void bluetooth_send(uint8_t * data){
	uint32_t size = strlen((char *)data);
	// send junk first
	USART_SendData(BLUETOOTH_USARTX,0);
	while(USART_GetFlagStatus(BLUETOOTH_USARTX,USART_FLAG_TC)==RESET);
	while(size--){
		USART_SendData(BLUETOOTH_USARTX,(uint16_t)*data++);
		while(USART_GetFlagStatus(BLUETOOTH_USARTX,USART_FLAG_TC)==RESET);
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
