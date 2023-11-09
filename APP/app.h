/*
 * app.h
 *
 * Created: 7/19/2023 6:34:08 PM
 *  Author: Adnan
 */ 


#ifndef APP_H_
#define APP_H_

#include "../HAL/LED/led.h"
#include "../HAL/BUTTON/button.h"
#include "../HAL/MOTOR/motor.h"
#include "../HAL/LCD/lcd.h"
#include "../HAL/TEMP_SENSOR/lm35.h"
#include "../HAL/BUZZER/buzzer.h"

#include "../MCAL/INTERRUPT/ext_interrupt.h"
#include "../MCAL/UART/uart.h"


void app_init(void);
void app_start(void);

#endif /* APP_H_ */