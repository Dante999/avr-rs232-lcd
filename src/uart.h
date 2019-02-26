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
#include <avr/io.h>

#ifndef UART_H_
#define UART_H_

    #define UART_BUFFER_SIZE 50

    extern void uart_init();
    extern void uart_putc(char c);
    extern void uart_puts(char *s);
    extern void uart_putsln(char *s);
    extern void uart_puti(uint8_t i);
    extern void uart_read_buffer(char *buffer);
    extern uint8_t uart_is_complete();
#endif
