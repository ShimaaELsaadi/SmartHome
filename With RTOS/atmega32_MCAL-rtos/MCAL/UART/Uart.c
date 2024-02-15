#include <Uart.h>
#include <Uart_Cfg.h>
#include <avr/interrupt.h>
#include <Std_Types.h>
#include <atmega32_Reg.h>

void (*_read_ptrf)(uint8) = 0;
void (*_empty_ptrf)(void) = 0;
void (*_write_ptrf)(void) = 0;

#define UART_F_CPU 16000000

void Uart_Init(){
	// UBRR
	uint32 ubbr;
	ubbr = (uint32)( ( ( UART_F_CPU ) / ( 16 * ( (uint32) UART_BAUDRATE ) ) ) - 1 );
	_UBRRL =( ubbr & 0x0000007F );
	_UBRRH = (ubbr & 0x0000ff00) >> 8;

	// UART Mode
	switch(UART_MODE){
	case UART_ASYNCH:
			_UCSRC |= 1<<7 | 1<<6;
		break;
	case UART_SYNCH:
			_UCSRC |= (1<<7) & (~(1<<6));  // 0b1000 0000  (  --> 1000 0000)
		break;
	}

	// UART Stop Bit
	switch(UART_STOP_BIT){
	case Stop_1Bit:
			_UCSRC |= 1<<7 | 1<<3;
		break;
	case Stop_2Bit:
			_UCSRC |= (1<<7) & (~(1<<3));  // 0b1000 0000  (  --> 1000 0000)
		break;
	}

	// UART Parity Bit
	switch(UART_PARITY){
	case NO_PARITY:
			_UCSRC |= (1<<7) & (~(1<<5)) & (~(1<<4));
		break;
	case ODD_PARITY:
			_UCSRC |= (1<<7) | (1<<5) | (1<<4);
		break;
	case EVEN_PARITY:
			_UCSRC |= ( (1<<7) | (1<<5) ) & (~(1<<4));
		break;
	}

	switch(UART_CHARSIZE){
	case CHAR_SIZE_5:	// SEL		//CS0		//CS1
			_UCSRC |= ( (1<<7) & (~(1<<1)) & (~(1<<2) ) );
						// CS2
			_UCSRB &=~(1<<2);
			break;
	case CHAR_SIZE_6:
		_UCSRC |= ( ( (1<<7) | (1<<1) )& ( ~ ( 1<<2 )  ) );
					// CS2
		_UCSRB &=~(1<<2);
		break;
	case CHAR_SIZE_7:
		_UCSRC |= ( ( (1<<7) | (1<<2) )& ( ~ ( 1<<1 )  ) );
					// CS2
		_UCSRB &=~(1<<2);
		break;
	case CHAR_SIZE_8:
		_UCSRC |= ( (1<<7) | (1<<1) | ( 1<<2 ) );
					// CS2
		_UCSRB &=~(1<<2);
		break;
	case CHAR_SIZE_9:
		_UCSRC |= ( (1<<7) | (1<<1) | ( 1<<2 ) );
					// CS2
		_UCSRB |= (1<<2);
		break;
	}

	// Transmission
	switch(UART_TRANSMISSION){
	case Enable_Polling:
		// enable transmission
		_UCSRB |= 1<<3;
		break;
	case Enable_Interrupt:
		// enable transmission and interrupt
		_UCSRB |= 1 <<3 | 1<<6;
		break;
	case Disable:
		_UCSRB &=~(1<< 3 | 1<< 6);
		break;
	}

	// Reciving
	switch(UART_RECEIVING){
	case Enable_Polling:
		// enable transmission
		_UCSRB |= 1<<4;
		break;
	case Enable_Interrupt:
		// enable transmission and interrupt
		_UCSRB |= 1 <<4 | 1<<7;
		break;
	case Disable:
		_UCSRB &=~(1<< 4 | 1<< 7);
		break;
	}


}

void Uart_WritePolling(uint8 data){
	while(!(_UCSRA & 1<<5));
	_UDR = data;
}

uint8 Uart_ReadPolling(){
	while(!(_UCSRA & 1<<5));
	return _UDR;
}

void Uart_SetEmptyCallback(void (*ptrf)(void)){
	_empty_ptrf = ptrf;
}

void Uart_SetReadCallback(void (*ptrf)(uint8)){
	_read_ptrf = ptrf;
}

void Uart_SetWriteCallback(void (*ptrf)(void)){
	_write_ptrf = ptrf;
}

ISR(USART_RXC_vect){
	uint8 data = _UDR;
	if(_read_ptrf != 0){
		_read_ptrf(data);
	}
}

ISR(USART_TXC_vect){
	if(_write_ptrf != 0){
		_write_ptrf();
	}
}


ISR(USART_UDRE_vect){
	if(_empty_ptrf != 0)
		_empty_ptrf();
}
