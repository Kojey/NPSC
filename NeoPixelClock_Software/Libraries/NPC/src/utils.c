/*
 * utils.c
 *
 *  Created on: Feb 23, 2017
 *      Author: Kojey
 */

#include "../Inc/utils.h"

uint8_t pixel_color;
/**
 * @brief find max between a and b
 */
uint32_t max(uint32_t a, uint32_t b, uint32_t c){
	return a>b?(a>c?a:c):(b>c?b:c);
}

