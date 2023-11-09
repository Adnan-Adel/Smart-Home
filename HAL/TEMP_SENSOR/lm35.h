/*
 * lm35.h
 *
 * Created: 7/19/2023 7:04:19 PM
 *  Author: Adnan
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "../../MCAL/ADC/adc.h"
#include "../LCD/lcd.h"

#define LM35_PORT		PORTC_INDEX
#define LM35_PIN		pin2

void lm35_init(void);
void lm35_get_value(void);


#endif /* LM35_H_ */