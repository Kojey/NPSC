/*
 * Bluetooth.h
 *
 *  Created on: 01 Mar 2017
 *      Author: Kojey
 */

#ifndef NPC_INC_BLUETOOTH_H_
#define NPC_INC_BLUETOOTH_H_

#include "stm32f4xx.h"
#include <string.h>

void USART1_IRQHandler(void);
void bluetooth_init(void);
void bluetooth_send(uint8_t * data);

#endif /* NPC_INC_BLUETOOTH_H_ */
