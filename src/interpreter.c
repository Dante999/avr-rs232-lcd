#include <avr/io.h>
#include <string.h>
#include "led.h"
#include "uart.h"
#include "lcd.h"
/**
 * commands:
 * -write (0|1) <string>
 * -clear (0|1)
 * -led (0|1)
**/


#define CMD_WRITE "-write"
#define CMD_CLEAR "-clear"
#define CMD_LED   "-led"


static uint8_t is_command(const char *buffer, const char *cmd) {

    if( strncmp(buffer, cmd, strlen(cmd)) == 0 ) {
        return 1;
    }
    else {
        return 0;
    }
}


static void handle_cmd_led(const char *command) {
    uint8_t value_index = strlen(CMD_LED)+1;

    if( command[value_index] == '1' ) {
        led_set_on();
    }
    else {
        led_set_off();
    }
}

static void handle_cmd_clear(const char *command) {
    uint8_t value_index = strlen(CMD_CLEAR)+1;

    if( command[value_index] == '0' ) {
        lcd_gotoxy(0,0);
    }
    else if( command[value_index] == '1' ) {
        lcd_gotoxy(0, 1);
    }
    else {
        return;
    }

    for( uint8_t i=0; i < LCD_DISP_LENGTH; i++) {
        lcd_putc(' ');
    }
}

static void handle_cmd_write(const char *command) {
    uint8_t index_line = strlen(CMD_WRITE)+1;
    uint8_t index_content = index_line+2;

    if( command[index_line] == '0' ) {
        lcd_gotoxy(0,0);
    }
    else if( command[index_line] == '1' ) {
        lcd_gotoxy(0, 1);
    }

    const char *value = &command[index_content];

    lcd_puts(value);
}


void interprete(const char *command) {


    if( is_command(command, CMD_LED) ) {
        handle_cmd_led(command);
    }
    else if( is_command(command, CMD_CLEAR)) {
        handle_cmd_clear(command);
    }
    else if( is_command(command, CMD_WRITE)) {
        handle_cmd_write(command);
    }
    else {
        uart_putsln(">unknown command!");
    }

}
