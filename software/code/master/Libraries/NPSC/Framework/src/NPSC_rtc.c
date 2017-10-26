/**
  ******************************************************************************
  * @file    NPSC_rtc.c
  * @author  Othniel Konan (Kojey)
  * @version V1.1.0
  * @date    23-OCt-2017
  * @brief	This file provides firmware functions to manage data transmission
  * 		to the rtc
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT </center></h2>
  *
  ******************************************************************************
  */

/* Includes -----------------------------------------------------------------*/
#include "NPSC_rtc.h"
#include "unitTest.h"

/** @addtogroup NPSC
  * @{
  */
/** @addtogroup Framework
  * @{
  */
/** @defgroup Rtc
  * @brief Rtc framework
  * @{
  */


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 uint8_t rtc_am_pm = RTC_H12_AM;
/* Private functions ---------------------------------------------------------*/


/******************************************************
 * 					INTIALISATION
 */

/**	@defgroup Rtc_Init Initialisation functions
 * 	@brief	Rtc initialisation functions
 * @{
 */
/**
 * @brief Initialise communication to the rtc
 * @param None
 * @retval None
 */
void rtc_init(void){
	/* RCC Configuration */
	RCC_AHB1PeriphClockCmd(RTC_RCC_GPIOX, ENABLE);
	RCC_APB1PeriphClockCmd(RTC_RCC_I2C, ENABLE);

	/* GPIO Configuration */
	//  SDL(B6), SDA(B7)
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Pin = RTC_PIN_SCL | RTC_PIN_SDA;
	GPIO_Init(RTC_GPIOX, &GPIO_InitStruct);

	GPIO_PinAFConfig(RTC_GPIOX, RTC_PINSOURCE_SCL, RTC_AF);
	GPIO_PinAFConfig(RTC_GPIOX, RTC_PINSOURCE_SDA, RTC_AF);

	/* I2C Configuration */
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_ClockSpeed = 50000; // 50kHz
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStruct.I2C_OwnAddress1 = 0x00;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Disable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_DeInit(RTC_I2CX);
	I2C_Init(RTC_I2CX, &I2C_InitStruct);
	I2C_Cmd(RTC_I2CX, ENABLE);

}

/**
 * @}
 */

/**	@defgroup Rtc_Trans RTC transmission functions
 * 	@brief	Low level interaction wih RTC using I2C
 *
 * @{
 */

/**
 * @brief	Start the I2C communication
 */
void rtc_transmission_start(uint8_t direction){
	// wait until I2C1 is not busy anymore
	while(I2C_GetFlagStatus(RTC_I2CX, I2C_FLAG_BUSY));
	// Send I2C1 START condition
	I2C_GenerateSTART(RTC_I2CX, ENABLE);
	// wait for I2C1 EV5 --> Slave has acknowledged start condition
	while(!I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_MODE_SELECT));
	// Send slave Address for write
	I2C_Send7bitAddress(RTC_I2CX, RTC_ADDRESS<<1, direction);//address, direction);
	/* wait for I2C1 EV6, check if
	 * either Slave has acknowledged Master transmitter or
	 * Master receiver mode, depending on the transmission
	 * direction
	 */
	if(direction == I2C_Direction_Transmitter){
		while(!I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
	}
	else if(direction == I2C_Direction_Receiver){
		while(!I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
	}
	/*I2C_SendData(RTC_I2CX,address);
	while(!I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED));*/
}

/**
 * @brief	Write one byte to the slave
 */
void rtc_transmission_write(uint8_t data)
{
	I2C_SendData(RTC_I2CX, data);
	while(!I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
}


/**
 * @brief	Read one byte from slave and acknowledge
 * 			the byte (request another byte)
 */
uint8_t rtc_transmission_read_ack(void){
	// enable acknowledge of recieved data
	I2C_AcknowledgeConfig(RTC_I2CX, ENABLE);
	// wait until one byte has been received
	while( !I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(RTC_I2CX);
	return data;
}

/**
 * @brief	Read one byte from the slave and
 * 			do not acknowledge the byte (end
 * 			transmission)
 */
uint8_t rtc_transmission_read_nack(void){
	// disabe acknowledge of received data
	// nack also generates stop condition after last byte received
	// see reference manual for more info
	I2C_AcknowledgeConfig(RTC_I2CX, DISABLE);
	I2C_GenerateSTOP(RTC_I2CX, ENABLE);
	// wait until one byte has been received
	while( !I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_BYTE_RECEIVED) );
	// read data from I2C data register and return data byte
	uint8_t data = I2C_ReceiveData(RTC_I2CX);
	return data;
}

/**
 * @brief	Stop the transmission
 */
void rtc_transmission_stop(){
	// Send I2C1 STOP Condition
	I2C_GenerateSTOP(RTC_I2CX, ENABLE);
}
/**
 * @}
 */

/******************************************************
 * 					DATA TRANSMISSIO
 */

/**	@defgroup Rtc_Data Data transmission
 * 	@brief	Byte transmission between master and RTC
 * @{
 */

/**
 * @brief	Write a byte to a slave
 * @param	address: address of slave
 * @param 	data
 */
void rtc_write(uint8_t address, uint8_t data){
	rtc_transmission_start(I2C_Direction_Transmitter);
	I2C_SendData(RTC_I2CX,address);
	while(!I2C_CheckEvent(RTC_I2CX, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
	rtc_transmission_write(data);
	rtc_transmission_stop();
}
/**
 * @brief	Read a byte from a slave
 * @param	address
 * @retval	data: byte of data from slave at the given address
 */
uint8_t rtc_read(uint8_t address){
	rtc_transmission_start(I2C_Direction_Receiver);
	return rtc_transmission_read_nack();
}

void rtc_get(uint8_t number){
	rtc_transmission_start(I2C_Direction_Receiver);
	int i;
	for(i=0; i<number-1; i++)
		rtc_transmission_read_ack();
	rtc_transmission_read_nack();
}
/**
 * @}
 */

/******************************************************
 * 						CLOCK
 */
/**	@defgroup Rtc_Clock Alarm/Clock
 * 	@brief	Set/Get time information
 * @{
 */

/**
 * @brief	Read the seconds
 * @return 	seconds
 */
uint8_t rtc_get_seconds(){
	uint8_t data = rtc_read(RTC_ADDRESS_SECONDS);
	uint8_t units = (RTC_MASK_LOW & data);
	uint8_t tens = (RTC_MASK_HIGH & data)>>4;
	uint8_t seconds = tens*10+units;
	return seconds;
}
/**
 * @brief	Read the minutes
 * @return	minutes
 */
uint8_t rtc_get_minutes(){
	uint8_t data = rtc_read(RTC_ADDRESS_MINUTES);
	uint8_t units = (RTC_MASK_LOW & data);
	uint8_t tens = (RTC_MASK_HIGH & data)>>4;
	uint8_t minutes= tens*10+units;
	return minutes;
}
/**
 * @brief	Read the hours
 * @return	hours
 */
uint8_t rtc_get_hours(){
	uint8_t data = rtc_read(RTC_ADDRESS_HOURS);
	// TODO extract the hours from data
	uint8_t units = (RTC_MASK_LOW & data);
	uint8_t tens = (0b00110000 & data)>>4;
	rtc_am_pm = (0b0100000 & data);
	uint8_t hours = tens*10+units;
	return hours;
}
/**
 * @brief	Read the day
 * @return 	day
 */
uint8_t rtc_get_day(){
	uint8_t data = rtc_read(RTC_ADDRESS_DAY);
	uint8_t day = (RTC_MASK_LOW & data);
	return day;
}
/**
 * @brief	Read the date
 * @return	date
 */
uint8_t rtc_get_date(){
	uint8_t data = rtc_read(RTC_ADDRESS_DATE);
	uint8_t units = (RTC_MASK_LOW & data);
	uint8_t tens = (RTC_MASK_HIGH & data)>>4;
	uint8_t date = tens*10+units;
	return date;
}
/**
 * @brief	Read the month
 * @return	month
 */
uint8_t rtc_get_month(){
	uint8_t data = rtc_read(RTC_ADDRESS_MONTH);
	uint8_t units = (RTC_MASK_LOW & data);
	uint8_t tens = (RTC_MASK_HIGH & data)>>4;
	uint8_t month = tens*10+units;
	return month;
}
/**
 * @brief	Read the year
 * @return	year
 */
uint8_t rtc_get_year(){
	uint8_t data = rtc_read(RTC_ADDRESS_YEAR);
	uint8_t units = (RTC_MASK_LOW & data);
	uint8_t tens = (RTC_MASK_HIGH & data)>>4;
	uint8_t year = tens*10+units;
	return year;
}
/**
 * @brief	Read the date information
 * @return	RTC_DateTypeDef
 */
RTC_DateTypeDef rtc_get_theDate(){
	RTC_DateTypeDef RTC_DateStruct;
	RTC_DateStruct.RTC_WeekDay= rtc_get_day();
	RTC_DateStruct.RTC_Date = rtc_get_date();
	RTC_DateStruct.RTC_Month = rtc_get_month();
	RTC_DateStruct.RTC_Year = rtc_get_year();
	return RTC_DateStruct;
}
/**
 * @brief	Read the time information
 * @return	RTC_TimeTypeDef
 */
RTC_TimeTypeDef rtc_get_theTime(){
	RTC_TimeTypeDef RTC_TimeStruct;
	RTC_TimeStruct.RTC_Seconds = rtc_get_seconds();
	RTC_TimeStruct.RTC_Minutes = rtc_get_minutes();
	RTC_TimeStruct.RTC_Hours = rtc_get_hours();
	// rtc_am_pm is updated after rtc_get_hours()
	RTC_TimeStruct.RTC_H12 = rtc_am_pm;
	return RTC_TimeStruct;
}
/**
 * @brief	Read clock information
 * @return	RTC_Clock_TypeDef
 */
RTC_ClockTypeDef rtc_get_clock(){
	// set pointer to the end of the RAM
	rtc_write(RTC_ADDRESS_RAM_END,0x00);
	RTC_ClockTypeDef RTC_ClockStruct;
	RTC_ClockStruct.time.RTC_Seconds = rtc_get_seconds();
	RTC_ClockStruct.time.RTC_Minutes = rtc_get_minutes();
	RTC_ClockStruct.time.RTC_Hours = rtc_get_hours();
	RTC_ClockStruct.date.RTC_WeekDay= rtc_get_day();
	RTC_ClockStruct.date.RTC_Date = rtc_get_date();
	RTC_ClockStruct.date.RTC_Month = rtc_get_month();
	RTC_ClockStruct.date.RTC_Year = rtc_get_year();
	return RTC_ClockStruct;
}
/**
 * @brief	Set the seconds
 */
ErrorStatus rtc_set_seconds(uint8_t seconds){
	if(!assertInRange(seconds,0,59)) return ERROR;
	uint8_t units = seconds%10;
	uint8_t tens = (seconds-units)/10;
	uint8_t data = (tens << 4) | units;
	rtc_write(RTC_ADDRESS_SECONDS, data);
	return SUCCESS;
}
/**
 * @brief	Set the minutes
 */
ErrorStatus rtc_set_minutes(uint8_t minutes){
	if(!assertInRange(minutes,0,59)) return ERROR;
	uint8_t units = minutes%10;
	uint8_t tens = (minutes-units)/10;
	uint8_t data = (tens << 4) | units;
	rtc_write(RTC_ADDRESS_MINUTES, data);
	return SUCCESS;
}
/**
 * @brief	Set the hours
 */
ErrorStatus rtc_set_hours(uint8_t hours){
	if(!assertInRange(hours,0,23)) return ERROR;
	uint8_t units = hours%10;
	uint8_t tens = (hours-units)/10;
	uint8_t data = (tens << 4) | units;
	rtc_write(RTC_ADDRESS_HOURS, data);
	return SUCCESS;
}
/**
 * @brief	Set the day
 */
ErrorStatus rtc_set_day(uint8_t day){
	if(!assertInRange(day,1,7)) return ERROR;
	rtc_write(RTC_ADDRESS_DAY, day);
	return SUCCESS;
}
/**
 * @brief	Set the date
 */
ErrorStatus rtc_set_date(uint8_t date){
	if(!assertInRange(date,1,31)) return ERROR;
	uint8_t units = date%10;
	uint8_t tens = (date-units)/10;
	uint8_t data = (tens << 4) | units;
	rtc_write(RTC_ADDRESS_DATE, data);
	return SUCCESS;
}
/**
 * @brief	Set the month
 */
ErrorStatus rtc_set_month(uint8_t month){
	if(!assertInRange(month,1,12)) return ERROR;
	uint8_t units = month%10;
	uint8_t tens = (month-units)/10;
	uint8_t data = (tens << 4) | units;
	rtc_write(RTC_ADDRESS_MONTH, data);
	return SUCCESS;
}
/**
 * @brief	Set the year
 */
ErrorStatus rtc_set_year(uint8_t year){
	if(!assertInRange(year,0,99)) return ERROR;
	uint8_t units = year%10;
	uint8_t tens = (year-units)/10;
	uint8_t data = (tens << 4) | units;
	rtc_write(RTC_ADDRESS_YEAR, data);
	return SUCCESS;
}

/**
 * @brief	Set the time
 */
ErrorStatus rtc_set_theTime(RTC_TimeTypeDef * time){
	if( !assertInRange(time->RTC_Seconds,0,59) ||
			!assertInRange(time->RTC_Minutes,0,59) ||
			!assertInRange(time->RTC_Hours,0,23))
		return ERROR;
	rtc_set_seconds(time->RTC_Seconds);
	rtc_set_minutes(time->RTC_Minutes);
	rtc_set_hours(time->RTC_Hours);
	return SUCCESS;
}
/**
 * @brief	Set the date
 */
ErrorStatus rtc_set_theDate(RTC_DateTypeDef * date){
	if( !assertInRange(date->RTC_WeekDay,1,7) ||
			!assertInRange(date->RTC_Date,1,31) ||
			!assertInRange(date->RTC_Month,1,12) ||
			!assertInRange(date->RTC_Year,0,99))
		return ERROR;
	rtc_set_day(date->RTC_WeekDay);
	rtc_set_date(date->RTC_Date);
	rtc_set_month(date->RTC_Month);
	rtc_set_year(date->RTC_Year);
	return SUCCESS;
}
/**
 * @brief	Set the clock
 */
ErrorStatus rtc_set_clock(RTC_ClockTypeDef * clock){
	if( !assertInRange(clock->time.RTC_Seconds,0,59) ||
			!assertInRange(clock->time.RTC_Minutes,0,59) ||
			!assertInRange(clock->time.RTC_Hours,0,23) ||
			!assertInRange(clock->date.RTC_WeekDay,1,7) ||
			!assertInRange(clock->date.RTC_Date,1,31) ||
			!assertInRange(clock->date.RTC_Month,1,0x12) ||
			!assertInRange(clock->date.RTC_Year,0,99))
		return ERROR;
	rtc_set_seconds(clock->time.RTC_Seconds);
	rtc_set_minutes(clock->time.RTC_Minutes);
	rtc_set_hours(clock->time.RTC_Hours);
	rtc_set_day(clock->date.RTC_WeekDay);
	rtc_set_date(clock->date.RTC_Date);
	rtc_set_month(clock->date.RTC_Month);
	rtc_set_year(clock->date.RTC_Year);
	return SUCCESS;
}

/**
 * @}
 */


/**	@defgroup Rtc_String
 * 	@brief	Get string from int month or weekday
 * @{
 */
char * rtc_get_day_string(uint8_t day){
	switch (day) {
		case 0x01:	return "Monday"; break;
		case 0x02:	return "Tuesday"; break;
		case 0x03:	return "Wednesday";	break;
		case 0x04:	return "Thursday"; break;
		case 0x05: return "Friday"; break;
		case 0x06: return "Saturday"; break;
		case 0x07: return "Sunday"; break;
		default: return "Error"; break;
	}
}
/**
 * @brief	Return the string equivalent of the month
 */
char * rtc_get_month_string(uint8_t month){
	switch (month) {
		case 1:	return "January"; break;
		case 2:	return "February"; break;
		case 3:	return "March";	break;
		case 4:	return "April"; break;
		case 5: return "May"; break;
		case 6: return "June"; break;
		case 7: return "July"; break;
		case 8:	return "August"; break;
		case 9:	return "September"; break;
		case 10:return "October";	break;
		case 11:return "November"; break;
		case 12:return "December"; break;
		default:return "Error"; break;
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
