#include <Exti.h>
#include <Exti_Types.h>

#include <atmega32_Reg.h>
#include <Bit_Math.h>

Exti_ISR isrs[3];

void Exti_Enable(Exti_SourceType source, Exti_SenseType sense, Exti_ISR isr){
	switch(source){
	case EXTI0:
		switch(sense){
		case SENSE_LOW:
			CLEAR_BIT(_MCUCR , 0);
			CLEAR_BIT(_MCUCR , 1);
			break;
		}
		break;
	case EXTI1:

		break;
	default:
		//EXTI2

		break;
	}
}

void Exti_Disable(Exti_SourceType source){
	switch(source){
	case EXTI0:
		CLEAR_BIT(_GICR , 6);
		break;
	case EXTI1:
		CLEAR_BIT(_GICR , 7);
		break;
	default:
		CLEAR_BIT(_GICR , 5);
	}
}

