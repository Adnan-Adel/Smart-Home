/*
 * uart.c
 *
 * Created: 7/12/2023 6:13:54 PM
 *  Author: Adnan
 */ 
#include "uart.h"

void UART_Init()
{
	//Baud Rate
	UBRRL = 103;

	//Normal Speed
	CLEAR_BIT(UCSRA,1);
	
	//frame -> parity,stopbits, databits
	/*parity even*/
	SET_BIT(UCSRC,5);
	CLEAR_BIT(UCSRC,4);
	/*1 stop bit*/
	CLEAR_BIT(UCSRC,3);
	/*data bits*/
	SET_BIT(UCSRC,1);
	SET_BIT(UCSRC,2);
	CLEAR_BIT(UCSRB,2);
	
	//mode default Asynchronous
	//enable RX
	SET_BIT(UCSRB,4);
	//enable TX
	SET_BIT(UCSRB,3);
}

void UART_Transmit(uint8_t data)
{
	while(! READ_BIT(UCSRA,5));
	UDR = data;
}


uint8_t UART_Receive()
{
	while(! READ_BIT(UCSRA,7));
	return UDR;
}

void UART_ReceiveStr(uint8_t* str)
{
	uint8_t data =  UART_Receive();
	uint8_t i = 0;
	str[i] = data;
	i++;
	while(data != '\r') //continue receive until Enter
	{
		data =  UART_Receive();
		str[i] = data;
		i++;
	}
	str[i] = '\0';
}

void UART_TransmitStr(uint8_t* str)
{
	uint8_t i = 0;
	while(str[i] != '\0')
	{
		while(! READ_BIT(UCSRA,5));
		UDR = str[i];
		i++;
	}
	
}