#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_

#include <Std_Types.h>

void Uart_Init();

void Uart_WritePolling(uint8);
uint8 Uart_ReadPolling();
void Uart_SetReadCallback(void (*ptrf)(uint8));
void Uart_SetWriteCallback(void (*ptrf)(void));
void Uart_SetEmptyCallback(void (*ptrf)(void));

#endif /* MCAL_UART_UART_H_ */
