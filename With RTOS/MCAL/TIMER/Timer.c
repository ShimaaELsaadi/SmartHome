#include <Timer.h>
#include <Timer_Cfg.h>
#include <atmega32_Reg.h>
#include <Bit_Math.h>
#include <avr/interrupt.h>

/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										Timer 0													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/

#if USE_TIMER0==1

Timer_Interrupt_P2F _timer0_ovf_isr;
Timer_Interrupt_P2F _timer0_ocr_isr;

static void Timer0_Enable_OVF_Interrupt(){
	_TIMSK |= 1<<0;// enable overflow interrupt
}

static void Timer0_Enable_OCR_Interrupt(){
	_TIMSK |= 1<<1;// enable overflow interrupt
}

void Timer_SetTimer0_OVF_Callback(Timer_Interrupt_P2F timer0_OVF_ISR){
	_timer0_ovf_isr =timer0_OVF_ISR;
}

void Timer_SetTimer0_OCR_Callback(Timer_Interrupt_P2F timer0_OCR_ISR){
	_timer0_ocr_isr =timer0_OCR_ISR;
}

void Timer_SetTCNT0(uint8 tcnt0){
	_TCNT0 = tcnt0;
}

void Timer_SetOCR0(uint8 ocr0){
	_OCR0 = ocr0;
}

static void Timer0_init(){
	// Enabling Over Flow interrupt for Timer 0
	#if TIMER0_OVF_INTERRUPT == 1
		Timer0_Enable_OVF_Interrupt();
	#endif

	// Enabling Output Capture interrupt for Timer 0
	#if TIMER0_OCR_INTERRUPT == 1
		Timer0_Enable_OCR_Interrupt();
	#endif
	// setting up Timer0 TCNT0 Register
	Timer_SetTCNT0(TIMER0_TCNT0);

	// Select Timer 0 Mode
	#if		TIMER0_MODE_SELECT == TIMER0_MODE_NORMAL
		_TCCR0 &=~(1<<6);
		_TCCR0 &=~(1<<3);
	#elif 	TIMER0_MODE_SELECT == TIMER0_MODE_PWM_PHASE
		_TCCR0 |= (1<<6);
		_TCCR0 &=~(1<<3);
	#elif 	TIMER0_MODE_SELECT == TIMER0_MODE_CTC
		_TCCR0 &=~(1<<6);
		_TCCR0 |= (1<<3);
	#elif	TIMER0_MODE_SELECT == TIMER0_MODE_PWM_FAST
		_TCCR0 |= (1<<6);
		_TCCR0 |= (1<<3);
	#endif

	// wave generation mode
	switch(TIMER0_COMP0_MODE){
		case COMP1_NORMAL:
			_TCCR0 &=~(1<<4);
			_TCCR0 &=~(1<<5);
			break;
		case COMP1_TOGGLE:
			_TCCR0 |= (1<<4);
			_TCCR0 &=~(1<<5);
			break;
		case COMP1_INVERTED:
			_TCCR0 &=~(1<<4);
			_TCCR0 |= (1<<5);
			break;
		case COMP1_NONINVERTED:
			_TCCR0 |= (1<<4);
			_TCCR0 |= (1<<5);
			break;
		default:
			break;
		}
	// Set Pre-Scaler for Timer0 and enable the timer
	_TCCR0  &=~(1<<0 | 1<<1 | 1<<2);
	_TCCR0 |= TIMER0_PRESCALER_SELECT;

}

ISR(TIMER0_OVF_vect){
	if(_timer0_ovf_isr !=0)
		_timer0_ovf_isr();
	_TCNT0 = 0x00;
}

ISR(TIMER0_COMP_vect){
	if(_timer0_ocr_isr != 0)
		_timer0_ocr_isr();
	_TCNT0 = 0x00;
}

#endif

/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										Timer 1													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/

#if USE_TIMER1 == 1

Timer_Interrupt_P2F _timer1_ovf_isr;
Timer_Interrupt_P2F _timer1_ocra_isr;
Timer_Interrupt_P2F _timer1_ocrb_isr;
Timer_Interrupt_P2F _timer1_icu_isr;

static void Timer1_Enable_OVF_Interrupt(){
	_TIMSK |= 1<<2;// enable overflow interrupt
}

static void Timer1_Enable_OCRA_Interrupt(){
	_TIMSK |= 1<<4;// enable overflow interrupt
}

static void Timer1_Enable_OCRB_Interrupt(){
	_TIMSK |= 1<<3;// enable overflow interrupt
}

static void Timer1_Enable_ICU_Interrupt(){
	_TIMSK |= 1<<5;// enable overflow interrupt
}

void Timer_SetTimer1_OVF_Callback(Timer_Interrupt_P2F timer1_OVF_ISR){
	_timer1_ovf_isr =timer1_OVF_ISR;
}

void Timer_SetTimer1_OCRA_Callback(Timer_Interrupt_P2F timer1_OCRA_ISR){
	_timer1_ocra_isr =timer1_OCRA_ISR;
}

void Timer_SetTimer1_OCRB_Callback(Timer_Interrupt_P2F timer1_OCRB_ISR){
	_timer1_ocrb_isr =timer1_OCRB_ISR;
}

void Timer_SetTimer1_ICU_Callback(Timer_Interrupt_P2F timer1_ICU_ISR){
	_timer1_icu_isr =timer1_ICU_ISR;
}

void Timer_SetTCNT1(uint16 tcnt1){
	_TCNT1L = tcnt1;
	_TCNT1H =(uint8)(tcnt1 >> 8);
}

void Timer_SetOCR1A(uint16 ocr){
	_OCR1AL = ocr;
	_OCR1AH =(uint8)(ocr >> 8);
}

void Timer_SetOCR1B(uint16 ocr){
	_OCR1BL = ocr;
	_OCR1BH =(uint8)(ocr >> 8);
}

void Timer_SetICR1(uint16 icr){
	_ICR1L = icr;
	_ICR1H =(uint8)(icr >> 8);
}

static void Timer1_init(){
	Timer_SetTCNT1(TIMER1_TCNT1);

	#if TIMER1_OVF_INTERRUPT == 1
		Timer1_Enable_OVF_Interrupt();
	#endif

	#if TIMER1_OCRA_INTERRUPT == 1
		Timer1_Enable_OCRA_Interrupt();
	#endif

	#if TIMER1_OCRB_INTERRUPT == 1
		Timer1_Enable_OCRB_Interrupt();
	#endif

	#if TIMER1_ICU_INTERRUPT == 1
		Timer1_Enable_ICR_Interrupt();
	#endif
	// setting up mode
	for(int i=TIMER1_MODE_0 ; i<=TIMER1_MODE_15 ; i++){
		if(i == TIMER1_MODE_SELECT){
			// clear Bit 1 and bit 0 in TCCR1A
			_TCCR1A &=~(1<< 0 | 1<<1);
			_TCCR1A |= (i & (1 << 0 | 1<< 1) );
			// clear bit 3 and 4 in TCCR1B
			_TCCR1B &=~(1<<3 | 1<<4);
			_TCCR1B |= (i & (1 << 2 | 1<< 3) ) << 2;
		}
	}

	// setting up compare mode for Timer1A
	switch(TIMER1_COMPA_MODE){
	case COMP1_NORMAL:
		_TCCR1A &=~(1<<6);
		_TCCR1A &=~(1<<7);
		break;
	case COMP1_TOGGLE:
		_TCCR1A |= (1<<6);
		_TCCR1A &=~(1<<7);
		break;
	case COMP1_INVERTED:
		_TCCR1A |= (1<<6);
		_TCCR1A &=~(1<<7);
		break;
	case COMP1_NONINVERTED:
		_TCCR1A |= (1<<6);
		_TCCR1A |= (1<<7);
		break;
	default:
		break;
	}

	// setting up compare mode Timer1B
	switch(TIMER1_COMPB_MODE){
		case COMP1_NORMAL:
			_TCCR1A &=~(1<<4);
			_TCCR1A &=~(1<<5);
			break;
		case COMP1_TOGGLE:
			_TCCR1A |= (1<<4);
			_TCCR1A &=~(1<<5);
			break;
		case COMP1_INVERTED:
			_TCCR1A &=~(1<<4);
			_TCCR1A |= (1<<5);
			break;
		case COMP1_NONINVERTED:
			_TCCR1A |= (1<<6);
			_TCCR1A |= (1<<7);
			break;
		default:
			break;
	}
	// Set Pre-Scaler for Timer1 And enable the timer
	_TCCR1A  &=~(1<<0 | 1<<1 | 1<<2);
	_TCCR1A |= TIMER1_PRESCALER_SELECT;
}

ISR(TIMER1_OVF_vect){
	if(_timer1_ovf_isr != 0)
		_timer1_ovf_isr();
	_TCNT1L =0;
	_TCNT1H =0;
}

ISR(TIMER1_COMPA_vect){
	if(_timer1_ocra_isr != 0)
		_timer1_ocra_isr();
	_TCNT1L =0;
	_TCNT1H =0;
}

ISR(TIMER1_COMPB_vect){
	if(_timer1_ocrb_isr != 0)
		_timer1_ocrb_isr();
	_TCNT1L =0;
	_TCNT1H =0;

}

ISR(TIMER1_CAPT_vect){
	if(_timer1_icu_isr != 0)
		_timer1_icu_isr();
	_TCNT1L =0;
	_TCNT1H =0;

}

#endif
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										Timer 2													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/

#if USE_TIMER2 == 1


Timer_Interrupt_P2F _timer2_ovf_isr;
Timer_Interrupt_P2F _timer2_ocr_isr;

static void Timer2_Enable_OVF_Interrupt(){
	_TIMSK |= 1<<6;// enable overflow interrupt
}

static void Timer2_Enable_OCR_Interrupt(){
	_TIMSK |= 1<<7;// enable overflow interrupt
}

void Timer_SetTimer2_OVF_Callback(Timer_Interrupt_P2F timer2_OVF_ISR){
	_timer2_ovf_isr =timer2_OVF_ISR;
}

void Timer_SetTimer2_OCR_Callback(Timer_Interrupt_P2F timer2_OCR_ISR){
	_timer2_ocr_isr =timer2_OCR_ISR;
}

void Timer_SetTCNT2(uint8 tcnt2){
	_TCNT2 = tcnt2;
}

void Timer_SetOCR2(uint8 ocr2){
	_OCR2 = ocr2;
}

void Timer2_init(){
	// Enabling Over Flow interrupt for Timer 0
	#if TIMER2_OVF_INTERRUPT == 1
		Timer2_Enable_OVF_Interrupt();
	#endif

	// Enabling Output Capture interrupt for Timer 0
	#if TIMER2_OCR_INTERRUPT == 1
		Timer2_Enable_OCR_Interrupt();
	#endif
	// setting up Timer0 TCNT0 Register
	Timer_SetTCNT2(TIMER2_TCNT0);

	// Select Timer 0 Mode
	#if		TIMER2_MODE_SELECT == TIMER2_MODE_NORMAL
		_TCCR2 &= ~(1<<3);
		_TCCR2 &= ~(1<<6);
	#elif 	TIMER2_MODE_SELECT == TIMER2_MODE_PWM_PHASE
		_TCCR2 |=  (1<<3);
		_TCCR2 &= ~(1<<6);
	#elif 	TIMER2_MODE_SELECT == TIMER2_MODE_CTC
		_TCCR2 |=  (1<<6);
		_TCCR2 &= ~(1<<3);
	#elif	TIMER2_MODE_SELECT == TIMER2_MODE_PWM_FAST
		_TCCR2 |=  (1<<3);
		_TCCR2 |=  (1<<6);
	#endif

	// wave generation mode
	switch(TIMER2_COMP2_MODE){
		case COMP2_NORMAL:
				_TCCR2 &=~(1<<4);
				_TCCR2 &=~(1<<5);
			break;
		case COMP2_TOGGLE:
				_TCCR2 |= (1<<4);
				_TCCR2 &=~(1<<5);
			break;
		case COMP2_INVERTED:
				_TCCR2 &=~(1<<4);
				_TCCR2 |= (1<<5);
			break;
		case COMP2_NONINVERTED:
				_TCCR2 |= (1<<4);
				_TCCR2 |= (1<<5);
			break;
		default:
			break;
		}
	// Set Pre-Scaler for Timer0 and enable the timer
	_TCCR2  &=~(1<<0 | 1<<1 | 1<<2);
	_TCCR2 |= TIMER2_PRESCALER_SELECT;
}

ISR(TIMER2_OVF_vect){
	if(_timer2_ovf_isr !=0)
		_timer2_ovf_isr();
	_TCNT2 = 0x00;
}

ISR(TIMER2_COMP_vect){
	if(_timer2_ocr_isr != 0)
		_timer2_ocr_isr();
	_TCNT2 = 0x00;
}

#endif
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										Timer initialization													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/


void Timer_init(){

	#if USE_TIMER0 == 1
		Timer0_init();
	#endif // TIMER-0

	#if USE_TIMER1 == 1
		Timer1_init();
	#endif

	#if USE_TIMER2 == 1
		Timer2_init();
	#endif
}

