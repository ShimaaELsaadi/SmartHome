#include <Spi.h>
#include <Spi_Cfg.h>
#include <avr/interrupt.h>
#include <atmega32_Reg.h>

void (*ptrf)(uint8) = 0;

void Spi_Init(){
	switch(SPI_MODE){
	case SPI_MASTER:
			_SPCR |= 1<<4;
			// setting pin to output

		break;
	case SPI_SLAVE:
			_SPCR &=~(1<<4);
			// setting pin to input
			// done in dio module
		break;
	}

	switch(SPI_DORD){
	case MSB_FIRST:
			_SPCR &=~(1<<5);
		break;
	case LSB_FIRST:
			_SPCR |= (1<<5);
		break;
	}


	switch(SPI_MODE){
	case SPI_SAMPLE_0:
			_SPCR &=~(1<< 3);
			_SPCR &=~(1<<2);
		break;
	case SPI_SAMPLE_1:
			_SPCR &=~(1<<3);
			_SPCR |= 1<<2;
		break;
	case SPI_SAMPLE_2:
			_SPCR |= (1<<3);
			_SPCR &=~(1<<2);
		break;
	case SPI_SAMPLE_3:
			_SPCR |= 1<<3;
			_SPCR |= 1<<2;
		break;
	}

	// setting clock
	if(SPI_CLOCK > 3 ){
		_SPCR &= ~(1<<0 | 1<<1);
		_SPCR |= (SPI_CLOCK - 3);
		_SPSR |= 1<<0;
	}else{
		_SPCR &= ~(1<<0 | 1<<1);
		_SPCR |= (SPI_CLOCK - 3);
	}
	// enable interrupt
	#if SPI_INTERRUPT ==1
		_SPCR |= 1<<7;
	#endif
	// enable spi
	_SPCR |= 1<<6;
}

void Spi_Write(uint8 data){
	_SPDR = data;
}

uint8 Spi_Transive(uint8 data){
	_SPDR = data;
	while(!(_SPSR & (1<<7)));	/* Wait till transmission complete */
	uint8 i = _SPDR;
	return i;
}


void Spi_SetEndOfTtransmissionCallBack(void(*_ptrf)(uint8)){
	ptrf = _ptrf;
}

ISR(SPI_STC_vect){
	uint8 data = _SPDR;
	if(ptrf !=0)
		ptrf(data);
}
