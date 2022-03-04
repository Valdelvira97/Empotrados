/*
 * leon3_bprint.c
 *
 *  Created on: Feb 25, 2022
 *      Author: David
 */

#include "leon3_uart.h"
#include "leon3_bprint.h"

int8_t leon3_print_string(char* str){
	
	int i = 0;
	while(str[i] != '0'){
		leon3_putchar(str[i]);
		i++;
	}
}
