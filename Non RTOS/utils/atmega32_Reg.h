#ifndef UTILS_ATMEGA32_REG_H_
#define UTILS_ATMEGA32_REG_H_

#include <Std_Types.h>

// TWI
#define	_TWDR (*(volatile uint8*)(0x23))
#define	_TWAR (*(volatile uint8*)(0x22))
#define	_TWSR (*(volatile uint8*)(0x21))
#define	_TWBR (*(volatile uint8*)(0x20))
#define	_TWCR (*(volatile uint8*)(0x56))



// SPI

#define	_SPCR (*(volatile uint8*)(0x2D))
#define	_SPSR (*(volatile uint8*)(0x2E))
#define	_SPDR (*(volatile uint8*)(0x2F))

// UART

#define _UBRRH (*(volatile uint8*)(0x40))
#define _UBRRL (*(volatile uint8*)(0x29))

#define _UCSRA (*(volatile uint8*)(0x2B))
#define _UCSRB (*(volatile uint8*)(0x2A))
#define _UCSRC (*(volatile uint8*)(0x40))
#define _UDR (*(volatile uint8*)(0x2C))

// DIO

#define _PORTA (*(volatile uint8*)(0x3B))
#define _DDRA (*(volatile uint8*)(0x3A))
#define _PINA (*(volatile const uint8*)(0x39))

#define _PORTB (*(volatile uint8*)(0x38))
#define _DDRB (*(volatile uint8*)(0x37))
#define _PINB (*(volatile const uint8*)(0x36))

#define _PORTC (*(volatile uint8*)(0x35))
#define _DDRC (*(volatile uint8*)(0x34))
#define _PINC (*(volatile const uint8*)(0x33))

#define _PORTD (*(volatile uint8*)(0x32))
#define _DDRD (*(volatile uint8*)(0x31))
#define _PIND (*(volatile const uint8*)(0x30))

// EXTI
#define _MCUCR	(*(volatile uint8*)(0x55))
#define _MCUCSR (*(volatile uint8*)(0x54))
#define _GICR	(*(volatile uint8*)(0x5B))
#define _GIFR	(*(volatile uint8*)(0x5A))

#define _DDRD (*(volatile uint8*)(0x31))
#define _DDRB (*(volatile uint8*)(0x37))

// GI
#define _SREG (*(volatile uint8*)(0x5F))

// WDT
#define _WDTCR (*(volatile uint8* )(0x41))

// TIMER 0
#define _TCCR0	*(volatile uint8*)(0x53)
#define _TCNT0	*(volatile uint8*)(0x52)
#define _OCR0	*(volatile uint8*)(0x5C)
#define _TIMSK	*(volatile uint8*)(0x59)
#define _TIFR	*(volatile uint8*)(0x58)


// TIMER 1
#define _TCCR1A	*(volatile uint8*)(0x4F)
#define _TCCR1B	*(volatile uint8*)(0x4E)

#define _TCNT1L	*(volatile uint8*)(0x4C)
#define _TCNT1H	*(volatile uint8*)(0x4D)

#define _OCR1AL	*(volatile uint8*)(0x4A)
#define _OCR1AH	*(volatile uint8*)(0x4B)

#define _OCR1BL	*(volatile uint8*)(0x48)
#define _OCR1BH	*(volatile uint8*)(0x49)

#define _ICR1L	*(volatile uint8*)(0x46)
#define _ICR1H	*(volatile uint8*)(0x47)

// TIMER 2
#define _TCCR2	*(volatile uint8*)(0x45)
#define _TCNT2	*(volatile uint8*)(0x44)
#define _OCR2	*(volatile uint8*)(0x43)


#endif /* UTILS_ATMEGA32_REG_H_ */
