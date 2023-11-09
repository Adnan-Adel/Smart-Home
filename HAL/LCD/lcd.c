/*
 * lcd.c
 *
 * Created: 7/19/2023 6:35:32 PM
 *  Author: Adnan
 */ 
#include "lcd.h"
#define F_CPU	16000000
#include <util/delay.h>
#include <stdlib.h>

/* ----------------------------------- lcd_4bit_Helper_Functions Prototypes ----------------------------------- */
static void lcd_send_enable_signal();
static void lcd_send_4bit(uint8_t _data_command);


/* ----------------------------------- lcd_4bit_functions implementation ----------------------------------- */
void lcd_4bit_initialize()
{
	uint8_t index_i= 0;
	dio_pin_init(LCD_4BIT_CTRL_PORT, RS, OUTPUT);
	dio_pin_init(LCD_4BIT_CTRL_PORT, E, OUTPUT);
	
	for(index_i=4; index_i <= 7; index_i++)
	{
		dio_pin_init(LCD_4BIT_DATA_PORT, index_i, OUTPUT);
	}
	
	_delay_ms(40);
	lcd_4bit_send_command(0x02);
	lcd_4bit_send_command(0x28);
	lcd_4bit_send_command(0x0F);
	lcd_4bit_send_command(0x01);
	lcd_4bit_send_command(0x06);
}

void lcd_4bit_send_command(uint8_t command)
{
	dio_pin_write_value(LCD_4BIT_CTRL_PORT, RS, LOW);
	
	lcd_send_4bit(command >> 4);                   // Send 4 HIGH bits first
	
	// Sending Hight to Low transition on Enable Signal
	lcd_send_enable_signal();
	
	lcd_send_4bit(command);                       // Send 4 LOW bits
	
	// Sending Hight to Low transition on Enable Signal
	lcd_send_enable_signal();
}

void lcd_4bit_send_char_data(uint8_t data)
{
	dio_pin_write_value(LCD_4BIT_CTRL_PORT, RS, HIGH);
	
	lcd_send_4bit(data >> 4);                   // Send 4 HIGH bits first
	
	// Sending Hight to Low transition on Enable Signal
	lcd_send_enable_signal();
	
	lcd_send_4bit(data);                       // Send 4 LOW bits
	
	// Sending Hight to Low transition on Enable Signal
	lcd_send_enable_signal();
}

void lcd_4bit_send_string(uint8_t *str)
{
	while(*str)
	{
		lcd_4bit_send_char_data(*str);
		str++;
	}
}

void lcd_4bit_send_string_pos(uint8_t row, uint8_t col, uint8_t *str)
{
	lcd_4bit_set_cursor(row,col);
	lcd_4bit_send_string(str);
}

void lcd_4bit_clearscreen()
{
	lcd_4bit_send_command(_LCD_CLEAR);
}

void lcd_4bit_send_number(uint8_t num)
{
	uint8_t BUFF[16];
	itoa(num,BUFF,10);
	lcd_4bit_send_string(BUFF);

}

void lcd_4bit_set_cursor(uint8_t row, uint8_t col)
{
	col--;
	switch (row)
	{
		case ROW1:
		lcd_4bit_send_command(0x80 + col);
		break;
		
		case ROW2:
		lcd_4bit_send_command(0xc0 + col);
		break;
	}
}


/* ----------------------------------- lcd_4bit_Helper_Functions Prototypes ----------------------------------- */
static void lcd_send_enable_signal()
{
	dio_pin_write_value(LCD_4BIT_CTRL_PORT, E, HIGH);
	_delay_us(5);
	
	dio_pin_write_value(LCD_4BIT_CTRL_PORT, E, LOW);
}


static void lcd_send_4bit(uint8_t _data_command)
{
	dio_pin_write_value(LCD_4BIT_DATA_PORT, LCD_4BIT_D4, ((_data_command >> 0) & 0x01));
	dio_pin_write_value(LCD_4BIT_DATA_PORT, LCD_4BIT_D5, ((_data_command >> 1) & 0x01));
	dio_pin_write_value(LCD_4BIT_DATA_PORT, LCD_4BIT_D6, ((_data_command >> 2) & 0x01));
	dio_pin_write_value(LCD_4BIT_DATA_PORT, LCD_4BIT_D7, ((_data_command >> 3) & 0x01));
}
