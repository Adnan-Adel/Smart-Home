/*
 * led.h
 *
 * Created: 3/16/2023 11:05:03 PM
 *  Author: LAP TECH
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../MCAL/DIO/dio.h"

#define LED_BLUE_PORT				PORTD_INDEX
#define LED_BLUE_PIN				pin0

#define LED_BUZZER_PORT				PORTC_INDEX
#define LED_BUZZER_PIN				pin3

#define OPEN_DOOR_LED_PORT			PORTB_INDEX
#define OPEN_DOOR_LED_PIN			pin3

#define CLOSE_DOOR_LED_PORT			PORTB_INDEX
#define CLOSE_DOOR_LED_PIN			pin4


void led_init(char port, char pin);
void led_turn_on(char port, char pin);
void led_turn_off(char port, char pin);
void led_toggle(char port, char pin);


#endif /* LED_H_ */