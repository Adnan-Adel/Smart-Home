/*
 * uart.h
 *
 * Created: 7/12/2023 6:14:05 PM
 *  Author: Adnan
 */ 


#ifndef UART_H_
#define UART_H_

#include "../DIO/dio.h"

/* -------------------------------------- Functions Declarations -------------------------------------- */
void UART_Init();

void UART_Transmit(uint8_t data);

uint8_t UART_Receive();

void UART_ReceiveStr(uint8_t* str);
void UART_TransmitStr(uint8_t* str);


#endif /* UART_H_ */