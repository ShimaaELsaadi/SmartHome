#include <Dio.h>
#include <Bit_Math.h>
#include <atmega32_Reg.h>
#include <Std_Types.h>

void Dio_InitChannel(Pin_Group group,Pin_Channel pin ,Pin_Channel_Direction dir){
	switch(group){
	case GROUPA:
		if (dir == OUTPUT){
			_DDRA |= 1<<pin;
		}else if(dir == INPUT){
			_DDRA &=~(1<<pin);
		}else if(INPUT_PULLUP){
			_DDRA &=~(1<<pin);
			_PORTA |= 1<<pin;
		}
		break;
	case GROUPB:
		if (dir == OUTPUT){
			_DDRB |= 1<<pin;
		}else if(dir == INPUT){
			_DDRB &=~(1<<pin);
		}else if(INPUT_PULLUP){
			_DDRB &=~(1<<pin);
			_PORTB |= 1<<pin;
		}
		break;
	case GROUPC:
		if (dir == OUTPUT){
			_DDRC |= 1<<pin;
		}else if(dir == INPUT){
			_DDRC &=~(1<<pin);
		}else if(INPUT_PULLUP){
			_DDRC &=~(1<<pin);
			_PORTC |= 1<<pin;
		}
		break;
	case GROUPD:
		if (dir == OUTPUT){
			_DDRD |= 1<<pin;
		}else if(dir == INPUT){
			_DDRD &=~(1<<pin);
		}else if(INPUT_PULLUP){
			_DDRD &=~(1<<pin);
			_PORTD |= 1<<pin;
		}
		break;
	default:
		break;
	}
	
}

void Dio_WriteChannel(Pin_Group group,Pin_Channel pin , Pin_Channel_State state){
	switch(group){
	case GROUPA:
		if(state){
			_PORTA |= 1<<pin;
		}else{
			_PORTA &=~(1<<pin);
		}
		break;
	case GROUPB:
		if(state){
			_PORTB |= 1<<pin;
		}else{
			_PORTB &=~(1<<pin);
		}
		break;
	case GROUPC:
		if(state){
			_PORTC |= 1<<pin;
		}else{
			_PORTC &=~(1<<pin);
		}
		break;
	case GROUPD:
		if(state){
			_PORTD |= 1<<pin;
		}else{
			_PORTD &=~(1<<pin);
		}
		break;
	default:
		break;
	}
}

uint8 Dio_ReadChannel(Pin_Group group,Pin_Channel pin){
	switch(group){
	case GROUPA:
		return (_PINA >> pin) & 0x01;
		break;
	case GROUPB:
		return (_PINB >> pin) & 0x01;
		break;
	case GROUPC:
		return (_PINC >> pin) & 0x01;
		break;
	case GROUPD:
		return (_PIND >> pin) & 0x01;
		break;
	default:
		break;
	}
	return 0;
}

uint8 Dio_FlipChannel(Pin_Group group,Pin_Channel pin){
	switch(group){
	case GROUPA:
		_PORTA ^= 1<<pin;
		return Dio_ReadChannel(group,pin);
		break;
	case GROUPB:
		_PORTB ^= 1<<pin;
		return Dio_ReadChannel(group,pin);
		break;
	case GROUPC:
		_PORTC ^= 1<<pin;
		return Dio_ReadChannel(group,pin);
		break;
	case GROUPD:
		_PORTD ^= 1<<pin;
		return Dio_ReadChannel(group,pin);
		break;
	default:
		break;
	}
	return 0;
}
