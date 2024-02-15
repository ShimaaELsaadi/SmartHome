#include <GI.h>
#include <Bit_Math.h>

#include <atmega32_Reg.h>

void GI_Enable(){
	SET_BIT(_SREG , 7);
}
void GI_Disable(){
	CLEAR_BIT(_SREG , 7);
}
