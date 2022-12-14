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
	
	int i = 0;
	while(str[i] != '0'){
		leon3_putchar(str[i]);
		i++;
	}
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
