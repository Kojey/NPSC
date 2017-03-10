Author  : Othniel KONAN
Version : 2017/03/03
Title   : TFT Screen explanation

****************************** BRIEF DESCRIPTION ******************************


******************************* PERIPHERALS USED *******************************
HY32D-ILI9325	|	TFT LCD	|	DESCRIPTION				|	PORT	|	FUNCTION
5V 		|	5V	|	5V power supply 			|	+5	|	VWhen powered from 5V supply,Pin 1 & Pin 2 as power input, Pin 33 & Pin 34 provide 3.3V output
GND 		|	GND	|	Ground 					|	GND	|	Power Ground 
D0 		|	DB0	|	Data lines 				|	PE0 	|
D1 		|	DB1	|		 				|		|
D2 		|	DB2	|			 			| 		|
D3  		|	DB3	|						|		|	
D4  		|	DB4	|						|		|
D5  		|	DB5	|						|		|	
D6  		|	DB6	|						|		|
D7  		|	DB7	|						|		|
D8  		|	DB8	|						|		|
D9  		|	DB9	|						|		|
D10  		|	DB10	|						|		|
D11  		|	DB11	|						|		|
D12  		|	DB12	|						|		|
D13  		|	DB13	|						|		|
D14  		|	DB14	|						|		|
D15  		|	DB15	|						|		|
CS 		|	CS	|	LCD chip select 			|	PD14 	|	Low active
RS 		|	RS	|	Instruction/Data 			|	PD15 	|	RS = 1 : Instruction Register RS = 0 : Data Register 
WR 		|	WR	|	Write 					|	PD12 	|	WR=0 RD=1
RD 		|	RD	|	Read 					|	PD13 	|	WR=1 RD=0
RESET 		|	RSET	|	Reset the controller chip 		|	PD11 	|	Low active
NC 		|		|	Not connected	 			|		|	Not connected	 
BLVCC 		|		|	5V or 3.3V 				|	+5V 	|	Backlight VCC
BLGND 		|		|	Ground 					|	GND 	| 	Backlight GND
BLCNT 		|		|	Backlight brightness adjustment 	|	PA0 	|	Control the backlight brightness via PWM
TP_IRQ 		|	T_IRQ	|	Touch screen interrupt 			|	PC8 	|	Low level while the touch screen detects pressing
TP_CS 		|	T_CS	|	Touch screen chip select 		|	PC9 	|	Low active
TP_SCK 		|	T_CLK	|	Touch screen SPI clock 			|	PC10 	|	Connect to SPI SCK
TP_SI 		|	T_DIN	|	Touch screen data input 		|	PC12 	|	Connect to SPI MOSI
TP_SO 		|	T_DOUT	|	Touch screen data output 		|	PC11 	| 	Connect to SPI MISO
3.3V 		|		|	3.3V Power supply			|		|	When powered from 3.3V supply,Pin 33 & Pin 34 as power input, Pin 1 & Pin 2 keep NC.	 
GND 		|		|	Ground 					|	GND 	|	Power Ground
