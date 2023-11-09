/*
 * app.c
 *
 * Created: 7/19/2023 6:34:00 PM
 *  Author: Adnan
 */ 
#include "app.h"
#define F_CPU	16000000
#include <util/delay.h>

void Default_InterruptHandler(void);
uint8_t flag= 0;
volatile uint8_t rec_command[20];

void app_init(void)
{
	led_init(LED_BLUE_PORT, LED_BLUE_PIN);
	led_init(LED_BUZZER_PORT, LED_BUZZER_PIN);
	led_init(OPEN_DOOR_LED_PORT, OPEN_DOOR_LED_PIN);
	led_init(CLOSE_DOOR_LED_PORT, CLOSE_DOOR_LED_PIN);
	motor_init(MOTOR_PORT, MOTOR_IN1, MOTOR_PORT, MOTORA_IN2);
	Buzzer_Init(BUZZER_PORT, BUZZER_PIN);
	lcd_4bit_initialize();
	lm35_init();
	
	ADC_Init(ADC_CONVERSION_CLOCK_FOSC_DIV_128, ADC_VOLTAGE_REF_AVCC, ADC_RESULT_RIGHT_ADJUSTMENT);
	Interrupt_INTx_Init(INTERRUPT_EXTERNAL_INT0, INTERRUPT_RISING_EDGE, Default_InterruptHandler);
	UART_Init();
}

void app_start(void)
{
	lcd_4bit_send_string("Welcome to the ");
	lcd_4bit_set_cursor(2, 1);
	lcd_4bit_send_string("IEEEian Helper!");
	_delay_ms(70);
	lcd_4bit_clearscreen();

	while(1)
	{
		lcd_4bit_send_string_pos(1, 1, "What do u need?");
		UART_ReceiveStr((uint8_t *)rec_command);
		
		if(rec_command[0] == 'L' && rec_command[1] == 'O')
		{
			led_turn_on(LED_BLUE_PORT, LED_BLUE_PIN);
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "Led Blue is ON.");
		}
		else if(rec_command[0] == 'L' && rec_command[1] == 'F')
		{
			led_turn_off(LED_BLUE_PORT, LED_BLUE_PIN);
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "Led Blue is OFF.");
		}
		else if(rec_command[0] == 'D' && rec_command[1] == 'O')
		{
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "opening the door...");
			motor_move_CW(MOTOR_PORT, MOTOR_IN1, MOTOR_PORT, MOTORA_IN2);
			led_turn_on(OPEN_DOOR_LED_PORT, OPEN_DOOR_LED_PIN);
			_delay_ms(50);
			motor_stop(MOTOR_PORT, MOTOR_IN1, MOTOR_PORT, MOTORA_IN2);
			led_turn_off(OPEN_DOOR_LED_PORT, OPEN_DOOR_LED_PIN);
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "Door Opened!");
		}
		else if(rec_command[0] == 'D' && rec_command[1] == 'C')
		{
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "Closing the door...");
			motor_move_CCW(MOTOR_PORT, MOTOR_IN1, MOTOR_PORT, MOTORA_IN2);
			led_turn_on(CLOSE_DOOR_LED_PORT, CLOSE_DOOR_LED_PIN);
			_delay_ms(50);
			motor_stop(MOTOR_PORT, MOTOR_IN1, MOTOR_PORT, MOTORA_IN2);
			led_turn_off(CLOSE_DOOR_LED_PORT, CLOSE_DOOR_LED_PIN);
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "Door Closed!");
		}
		else if(rec_command[0] == 'D' && rec_command[1] == 'T')
		{
			uint16 lm35_res_1, lm35_res_1_Celsius_mv = 0;
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "Temp: ");
			while(rec_command[0] == 'D' && rec_command[1] == 'T')
			{
				flag= 0;
				ADC_Blocking_GetConversion(ADC_CHANNEL_AN2, &lm35_res_1, ADC_RESULT_RIGHT_ADJUSTMENT);
				lm35_res_1_Celsius_mv = lm35_res_1 * 4.88f; // 5000(mv) / 1024(10-Bit) => 4.88
				lm35_res_1_Celsius_mv /= 10; // The sensitivity of LM35 is 10 mV/degree Celsius
				lcd_4bit_set_cursor(1,6);
				lcd_4bit_send_number(lm35_res_1_Celsius_mv);
				_delay_ms(100);
				while((0 == flag) && (100 >= lm35_res_1_Celsius_mv))
				{
					lcd_4bit_send_string("Fire ");
					Buzzer_On(BUZZER_PORT, BUZZER_PIN);
					led_toggle(LED_BUZZER_PORT, LED_BUZZER_PIN);
					_delay_us(10);
				}
			}
		}
		else
		{
			lcd_4bit_clearscreen();
			lcd_4bit_send_string_pos(1, 1, "Wrong Input.");
		}
	}
}

void Default_InterruptHandler(void)
{
	flag= 1;
	Buzzer_Off(BUZZER_PORT, BUZZER_PIN);
	led_turn_off(LED_BUZZER_PORT, LED_BUZZER_PIN);
	lcd_4bit_clearscreen();
	lcd_4bit_send_string_pos(1, 1, "Fire is Over");
}