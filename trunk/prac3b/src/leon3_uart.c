/*
 * leon3_uart.c
 *
 *  Created on: Feb 19, 2022
 *      Author: David
 */


#include "leon3_uart.h"

//Estructura de datos que permite acceder a los registros de la
//UART de LEON3
struct UART_regs
{
/** \brief UART Data Register */
volatile uint32_t Data; /* 0x80000100 */
/** \brief UART Status Register */
volatile uint32_t Status; /* 0x80000104 */
/** \brief UART Control Register */
volatile uint32_t Ctrl; /* 0x80000108 */
/** \brief UART Scaler Register */
volatile uint32_t Scaler; /* 0x8000010C */
};

//! LEON3 UART A Transmit FIFO is FULL
#define LEON3_UART_TFF (0x200)
//! LEON3 UART A Transmit FIFO is EMPTY
#define LEON3_UART_TFE (0x4)

//EDEL: añado aqui los defines
//********************************************************
//CTRL REGISTER MASKS

//!LEON3 UART CTRL RX ENABLE MASK
#define LEON3_UART_CTRL_RX_ENABLE (0x001)

//!LEON3 UART CTRL RX IRQ ENABLE MASK
#define LEON3_UART_CTRL_RX_IRQ_ENABLE (1 << 2)

//!LEON3 UART SET_LOOP_BACK MASK
#define LEON3_UART_CTRL_SET_LOOP_BACK  (0x080)


struct UART_regs * const pLEON3_UART_REGS= (struct UART_regs *)0x80000100;


#define leon3_UART_TF_IS_FULL() (pLEON3_UART_REGS->Status & LEON3_UART_TFF)

int8_t leon3_putchar(char c)
{
	uint32_t write_timeout=0;
	while(leon3_UART_TF_IS_FULL()&&(write_timeout < 0xAAAAA))
		{
			write_timeout++;
		} //Espera mientras la cola de transmisión esté llena
	if(write_timeout < 0xAAAAA){
		//COMPLETAR. Escribir el carácter en el registro Data
		pLEON3_UART_REGS-> Data =c;
		}
	return (write_timeout == 0xAAAAA);
}
int8_t leon3_uart_tx_fifo_is_empty(){
//COMPLETAR.
	int result;
	if(pLEON3_UART_REGS->Status & LEON3_UART_TFF){
		result = 0;
	}else{
		result = 1;
	}
	return result;
}

char leon3_getchar(){

	uint8_t i = (uint8_t) pLEON3_UART_REGS -> Data;

	return i;
}

void leon3_uart_ctrl_rx_enable(){
	uint32_t bit = (1 << 0);
  // EDEL: mismo comentario que en las siguientes
	if ((pLEON3_UART_REGS -> Ctrl & bit) == 0){
		pLEON3_UART_REGS -> Ctrl = ((pLEON3_UART_REGS -> Ctrl) | bit);
	}
}


void leon3_uart_ctrl_rx_irq_enable(){
	uint32_t bit = (1 << 2);

  //EDEL: Mejora, esto hace lo mismo.
	//pLEON3_UART_REGS->Ctrl |= LEON3_UART_CTRL_RX_IRQ_ENABLE;

	if ((pLEON3_UART_REGS -> Ctrl & bit) == 0){
		pLEON3_UART_REGS -> Ctrl = ((pLEON3_UART_REGS -> Ctrl) | bit);
	}
}

void leon3_uart_ctrl_config_rxtx_loop(uint8_t set_rxtxloop){
	uint32_t bit = (1 << 7);
	uint32_t loop_back = pLEON3_UART_REGS -> Ctrl;

	if (set_rxtxloop == 0){
		//Mejora:  pLEON3_UART_REGS -> Ctrl = (pLEON3_UART_REGS -> Ctrl & ~bit);
		//Mejora: es mejor usar una macro como máscara
		pLEON3_UART_REGS->Ctrl |= LEON3_UART_CTRL_SET_LOOP_BACK;
	}else if (set_rxtxloop == 1){
    //Mejora: pLEON3_UART_REGS -> Ctrl = (pLEON3_UART_REGS -> Ctrl | bit);
		//Mejora: es mejor usar una macro como máscara
		pLEON3_UART_REGS->Ctrl &= ~LEON3_UART_CTRL_SET_LOOP_BACK;
	}else {
		leon3_putchar("Error");
	}
}
