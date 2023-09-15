#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "main.h"

void USART_Init(void);
void USART0_IRQHandler(void);
void USART1_IRQHandler(void);
void USART6_IRQHandler(void);
void USART7_IRQHandler(void);

void Uart0_Transmit(u8 * string);
void Uart1_Transmit(u8 * string);
void Uart6_Transmit(u8 * string);
void Uart7_Transmit(u8 * string);

#endif


