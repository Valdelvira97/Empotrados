/*int main(){

	leon3_putchar('P');
	leon3_putchar('2');
	leon3_putchar('\n');

	while(!leon3_uart_tx_fifo_is_empty())
		;
		return 0;

}*/

int main(){
	char * pchar="cadena\n0"; //0 al final para que solo imprima "cadena"
	leon3_print_string(pchar);
	leon3_print_uint8(3); leon3_putchar('\n');
	leon3_print_uint8(43); leon3_putchar('\n');
	leon3_print_uint8(108); leon3_putchar('\n');
	leon3_putchar('\n');
	return 0;
}

























