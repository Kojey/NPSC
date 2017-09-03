Author  : Othniel KONAN
Version : 2017/03/03
Title   : HC-06 explanation

****************************** BRIEF DESCRIPTION ******************************
The HC06 is a bluetooth module which communicates via UART.
Its UART parameters are the following:
Baudrate:	9600
StopBit:	1
Word length:	8 bits
Parity bit:	No
It was decided that for now only one bit will be used to communicate via the bluetooth.
 
******************************* PERIPHERALS USED *******************************
BOARD: STM32F4_Discovery
UART:	USART1
TX:	PB6
RX:	PB7
