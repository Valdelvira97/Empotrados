/*
 * main.c
 *
 *  Created on: Mar 21, 2022
 *      Author: osboxes
 */

#include "leon3_uart.h"
#include "leon3_bprint.h"
#include "leon3_hw_irqs.h"
#include "leon3_ev_handling.h"

void device_hw_irq_level_1_handler(void){

leon3_print_string(“Device HW IRQ user handler \n”);

}
int main()

{
//Instalar como manejador del trap 0x83 la rutina
// que habilita las interrupciones
leon3_set_trap_handler(0x83,leon3_trap_handler_enable_irqs);
//Instalar el manejador del trap que 0x83 la rutina
// que deshabilita las interrupciones
leon3_set_trap_handler(0x84,leon3_trap_handler_disable_irqs);
//Llamada al sistema para deshabilitar las interrupciones
leon3_sys_call_disable_irqs();

leon3_install_handler(0x11, hw_irq_vector_0x11_handler);

leon3_unmask_irq(1);

leon3_sys_call_enable_irqs();

leon3_sparc_force_irq(1);

return 0;
}
