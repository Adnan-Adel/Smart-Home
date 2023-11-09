/*
 * buzzer.h
 *
 * Created: 7/20/2023 11:41:01 AM
 *  Author: Adnan
 */ 


#ifndef BUZZER_H_
#define BUZZER_H_

#include "../../MCAL/DIO/dio.h"

#define BUZZER_PORT		PORTC_INDEX
#define BUZZER_PIN		pin3

void Buzzer_Init(DIO_PORT_ID port, DIO_PIN_ID pin);
void Buzzer_On(DIO_PORT_ID port, DIO_PIN_ID pin);
void Buzzer_Off(DIO_PORT_ID port, DIO_PIN_ID pin);



#endif /* BUZZER_H_ */