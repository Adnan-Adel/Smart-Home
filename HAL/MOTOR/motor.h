/*
 * motor.h
 *
 * Created: 2/24/2023 4:41:19 PM
 *  Author: LAP TECH
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#include "../../MCAL/DIO/dio.h"

#define MOTOR_PORT				PORTB_INDEX

#define MOTOR_IN1				pin1
#define MOTORA_IN2				pin2

void motor_init(DIO_PORT_ID port1, DIO_PIN_ID pin1_Number,DIO_PORT_ID port2, DIO_PIN_ID pin2_Number);
void motor_move_CW(DIO_PORT_ID port1, DIO_PIN_ID pin1_Number,DIO_PORT_ID port2, DIO_PIN_ID pin2_Number);
void motor_move_CCW(DIO_PORT_ID port1, DIO_PIN_ID pin1_Number,DIO_PORT_ID port2, DIO_PIN_ID pin2_Number);
void motor_stop(DIO_PORT_ID port1, DIO_PIN_ID pin1_Number,DIO_PORT_ID port2, DIO_PIN_ID pin2_Number);


#endif /* MOTOR_H_ */