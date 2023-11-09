/*
 * buzzer.c
 *
 * Created: 7/20/2023 11:40:50 AM
 *  Author: Adnan
 */ 
#include "buzzer.h"

void Buzzer_Init(DIO_PORT_ID port, DIO_PIN_ID pin)
{
	dio_pin_init(port, pin, OUTPUT);
}

void Buzzer_On(DIO_PORT_ID port, DIO_PIN_ID pin)
{
	dio_pin_write_value(port, pin, HIGH);
}

void Buzzer_Off(DIO_PORT_ID port, DIO_PIN_ID pin)
{
	dio_pin_write_value(port, pin, LOW);
}