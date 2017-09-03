Author  : Othniel KONAN
Version : 2017/02/24
Title   : WS2812 explanation

****************************** BRIEF DESCRIPTION ******************************
The MCUs have a data line of 800kbps. The WS2812 MCUs are connected in serial connection. Each MCU uses 24 bytes which represent the colors Green,Red, and Blue respectively. When a stream of bytes is transmitted, the first MCU takes the first 24 bytes and transmits the other bytes to the next MCU. This process is stopped when a code reset is sent.
Each byte is an encoded version of a single bit used to represent each color. It uses NRZ @ 800kHz.
Each bit is transmitted at a period of 1.25us and is encoded using a pulse described bellow:
code 0:  1/3 High 2/3 Low
code 1:  2/3 High 1/3 Low
code reset:  40 cycle => 50us Low
If one MCU has the color G: 255       R:  0           B:  0
then in bits             G: 1111 1111 R:  0000 0000   B:  0000 0000
after NEZ encoding       G: xxxx xxxx R:  yyyy yyyy   B:  yyyy yyyy
x and y being 8bit number generating a code 1 and code 0 pulse respectively.
PS: refer to the datasheet for more details.

******************************* PERIPHERALS USED *******************************
In order to generate the pulse, we made use of PWM using data from the DMA.
The STM32F407VGTx was used for this project so the configuration were made as followed:
Port: GPIPA, Pin5, AF1, TIM2
DMA:  DMA_Channel3_Stream5  (connected to TIM2)
DMA NIVC: DMA1_Channel3_IRQ
