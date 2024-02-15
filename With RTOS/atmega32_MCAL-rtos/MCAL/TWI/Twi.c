#include <Twi.h>
#include <Twi_Cfg.h>
#include <atmega32_Reg.h>
#include <Std_Types.h>
#include <avr/interrupt.h>

void Twi_initMaster(){
	_TWBR = 12;
	_TWSR &=~(1<<0 | 1<< 1);
	_TWCR |= 1<<6;
	_TWCR |= 1<<2;
	_TWAR = TWI_ADDRESS;
}

void Twi_Start(){
	_TWCR |= 1<<7 | 1<< 5 | 1<<2;

	// Block on flag
	while((_TWCR & (1<<7)) == 0);
	if( (_TWSR & 0xf8) == SC_MT_START_SENT){
		// Done
		return;
	}
}
void Twi_SendSlaveAddressWithWrite(uint8 slad){
	_TWCR &=~(1<<5);

}














