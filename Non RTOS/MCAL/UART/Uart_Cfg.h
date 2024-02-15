#ifndef MCAL_UART_UART_CFG_H_
#define MCAL_UART_UART_CFG_H_

// Uart Mode
#define UART_ASYNCH 0
#define UART_SYNCH 1

#define UART_MODE UART_ASYNCH

// Uart Baudrate
#define Baud_2400	2400
#define Baud_4800	4800
#define Baud_9600	9600
#define Baud_14400	14400
#define Baud_19200	19200
#define Baud_28800	28800
#define Baud_38400	38400
#define Baud_57600	57600
#define Baud_76800	76800
#define Baud_115200	115200
#define Baud_230400	230400
#define Baud_250000	250000

#define UART_BAUDRATE Baud_9600

// Uart Character Size

#define CHAR_SIZE_5	0
#define CHAR_SIZE_6	1
#define CHAR_SIZE_7	2
#define CHAR_SIZE_8	3
#define CHAR_SIZE_9	7

#define UART_CHARSIZE	CHAR_SIZE_8

// Uart Stop bit
#define Stop_1Bit	0
#define Stop_2Bit	1

#define UART_STOP_BIT Stop_1Bit


// Uart Parity
#define NO_PARITY	1
#define EVEN_PARITY	2
#define ODD_PARITY	3

#define UART_PARITY	NO_PARITY


#define Enable_Polling		0
#define Enable_Interrupt 	1
#define Disable				2

#define UART_TRANSMISSION	Enable_Polling
#define UART_RECEIVING		Enable_Interrupt




#endif /* MCAL_UART_UART_CFG_H_ */
