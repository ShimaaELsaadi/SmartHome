#include <Dio.h>
#include <Bit_Math.h>
#include <atmega32_Reg.h>
#include <Std_Types.h>

void Dio_InitChannel(Pin_Group group,Pin_Channel pin ,Pin_Channel_Direction dir){
	switch(group){
	case GROUPA:
		SET_BIT(_DDRA , pin);
		break;
	case GROUPB:
		SET_BIT(_DDRB , pin);
		break;
	case GROUPC:
		SET_BIT(_DDRC , pin);
		break;
	default:
		SET_BIT(_DDRD , pin);
		break;
	}
	
}

void Dio_WriteChannel(Pin_Group group,Pin_Channel pin , Pin_Channel_State state){
	switch(group){
	case GROUPA:
		if(state){
			SET_BIT(_PORTA , pin);
		}else{
			CLEAR_BIT(_PORTA, pin);
		}
		break;
	case GROUPB:
		if(state){
			SET_BIT(_PORTB , pin);
		}else{
			CLEAR_BIT(_PORTB, pin);
		}
		break;
	case GROUPC:
		if(state){
			SET_BIT(_PORTC , pin);
		}else{
			CLEAR_BIT(_PORTC , pin);
		}
		break;
	default:
		if(state){
			SET_BIT(_PORTD , pin);
		}else{
			CLEAR_BIT(_PORTD , pin);
		}
		break;
	}
}

uint8 Dio_ReadChannel(Pin_Group group,Pin_Channel pin){
	switch(group){
	case GROUPA:
		return GET_BIT(_PINA , pin);
		break;
	case GROUPB:
		return GET_BIT(_PINB , pin);
		break;
	case GROUPC:
		return GET_BIT(_PINC , pin);
		break;
	default:
		return GET_BIT(_PIND , pin);
		break;
	}
	return 0;
}

uint8 Dio_FlipChannel(Pin_Group group,Pin_Channel pin){
	switch(group){
	case GROUPA:
		TOGGLE_BIT(_PORTA , pin);
		return GET_BIT(_PINA , pin);
		break;
	case GROUPB:
		_PORTB ^= 1<<(pin%8);
		return GET_BIT(_PINB , pin);
		break;
	case GROUPC:
		TOGGLE_BIT(_PORTC , pin);
		return GET_BIT(_PINC , pin);
		break;
	default:
		TOGGLE_BIT(_PORTD , pin);
		return GET_BIT(_PIND , pin);
		break;
	}
	return 0;
}
