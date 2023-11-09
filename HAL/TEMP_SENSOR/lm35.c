/*
 * lm35.c
 *
 * Created: 7/19/2023 7:04:09 PM
 *  Author: Adnan
 */ 
#include "lm35.h"
#define F_CPU	16000000
#include <util/delay.h>

void lm35_init(void)
{
	dio_pin_init(LM35_PORT, LM35_PIN, OUTPUT);
}

void lm35_get_value(void)
{

}