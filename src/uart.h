/*******************************************************************************
 *
 * File    : uart.h
 *
 * Author  : Dante999
 * Date    : 28.12.2018
 *
 * Tabsize : 4
 * License : GNU GPL v2
 *
 * writes to the uart serial interface
 *
 *
 ******************************************************************************/
#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define UART_BUFFER_SIZE 50

void    uart_init();
void    uart_putc(char c);
void    uart_puts(char *s);
void    uart_putsln(char *s);
void    uart_puti(uint8_t i);
void    uart_copy_buffer(char *buffer);
uint8_t uart_is_complete();

#endif // UART_H
