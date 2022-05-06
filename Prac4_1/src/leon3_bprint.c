/*
 * leon3_bprint.c
 *
 *  Created on: Feb 25, 2022
 *      Author: David
 */

#include "leon3_uart.h"
#include "leon3_bprint.h"

char uni_char, dec_char, cent_char;	//cadena de caracteres para unidades, decenas y centenas

int8_t leon3_print_string(char* str){
	
	int8_t error = 0;
	int i = 0;
	while(*str != '\0'){
		error = leon3_putchar(*str);
		str++;
	}

	while(!leon3_uart_tx_fifo_is_empty());
	return error;
}

int8_t leon3_print_uint8(uint8_t i){

	int uni,dec,cent;	//unidades, decenas y centenas

	if(i<9){	//imprimir numeros del 0 al 9(unidades)

		//valor de la unidad
		uni_char = i + '0';
		leon3_putchar(uni_char);

	}

	if((i>9)&&(i<99)){	//imprimir numeros del 10 al 99 (decenas y unidades)

		//valor de la decena
		dec = i/10;
		dec_char = dec + '0';
		leon3_putchar(dec_char);

		//valor de la unidad
		uni = i%10;
		uni_char = uni + '0';
		leon3_putchar(uni_char);

	}

	if((i>99)&&(i<999)){	//imprimir numeros del 100 al 999 (centenas, decenas y unidades)

		//valor de la centena
		cent = i/100;
		cent_char = cent + '0';
		leon3_putchar(cent_char);

		//valor de la decena
		dec = i%10;
		dec_char = dec + '0';
		leon3_putchar(dec_char);

		//valor de la unidad
		uni = i%1;
		uni_char = uni + '0';
		leon3_putchar(uni_char);

	}

}

/*int8_t leon3_print_uint32(uint32_t i){
	int8_t p1,p2,p3,p4;
	p1 = i/1000000000;
	p2 = (i-p1*1000000000)/1000000;
	p3 = (i-p2*1000000-p1*1000000000)/1000;
	p4 = i-p3*1000-p2*1000000-p1*1000000000;
	leon3_print_uint8(p1);
	leon3_print_uint8(p2);
	leon3_print_uint8(p3);
	leon3_print_uint8(p4);
	leon3_print_string("\n");
	return 0;
}*/


int8_t leon3_print_uint32(uint32_t i){
	
	int8_t error=0;
	uint32_t aux;
	int8_t first_digit=0;
	aux=1000000000;

	if(i==0)
		leon3_putchar('0');
	else{
		while(aux&&(!error)){
			uint8_t digit;

			digit=i/aux;
			i-=aux*digit;
			aux=aux/10;
			if(first_digit||digit){
				error=leon3_putchar('0'+digit);
				first_digit=1;
			}
		}
	}
	return error;
	
}
