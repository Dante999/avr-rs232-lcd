#include "avr/interrupt.h"
#include "interpreter.h"
#include "lcd.h"
#include "led.h"
#include "timer0.h"
#include "uart.h"
#include <avr/io.h>
#include <util/delay.h>

#define PRESCALER 64

/*******************************************************************************
 * initializes all modules
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
void init()
{
	led_init();
	uart_init();

	lcd_init(LCD_DISP_ON);
	lcd_clrscr();
}

/*******************************************************************************
 * the main function
 *
 * @param   none
 *
 * @return  none
 ******************************************************************************/
int main()
{
	char uart_buffer[UART_BUFFER_SIZE] = "";

	init();

	uart_puts("init done!");
	lcd_puts("Ready!");

	sei();

	while (1) {

		if (uart_is_complete()) {
			uart_copy_buffer(uart_buffer);
			interprete(uart_buffer);
		}
	}

	return 0;
}
