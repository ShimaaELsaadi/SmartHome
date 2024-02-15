#ifndef MCAL_TIMER_TIMER_CFG_H_
#define MCAL_TIMER_TIMER_CFG_H_

//#define USE_TIMER0 0
#define USE_TIMER0 0
#define USE_TIMER1 1
#define USE_TIMER2 0

/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										utils													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/

#define Enable 	1
#define Disable 0


/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										Timer 0													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/

#if USE_TIMER0 == 1
	// Timer0 MODEs
	#define TIMER0_MODE_NORMAL			0
	#define TIMER0_MODE_CTC				1
	#define TIMER0_MODE_PWM_FAST		2
	#define TIMER0_MODE_PWM_PHASE		3

	#define TIMER0_MODE_SELECT TIMER0_MODE_CTC


	// Timer 0 Pre-Scaler
	#define TIMER0_PRESCALER_NO_CLOCK			0
	#define TIMER0_PRESCALER_NO_NOPRESCALING	1
	#define TIMER0_PRESCALER_8					2
	#define TIMER0_PRESCALER_64					3
	#define TIMER0_PRESCALER_256				4
	#define TIMER0_PRESCALER_1024				5
	// source clock from output
	#define TIMER0_PRESCALER_EXTERNAL_FALING	6
	#define TIMER0_PRESCALER_EXTERNAL_RISING	7

	// Wave Generation Mode
	#define COMP0_NORMAL			0
	#define COMP0_TOGGLE			1
	#define COMP0_NONINVERTED		2
	#define COMP0_INVERTED			3
	// How OC0 Handled in Timer 0
	#define TIMER0_COMP0_MODE	COMP0_INVERTED

	// Enable Interrupt
	#define TIMER0_OVF_INTERRUPT Disable
	#define TIMER0_OCR_INTERRUPT Disable

	#define TIMER0_PRESCALER_SELECT TIMER0_PRESCALER_1024
	// Timer Initial Value
	#define TIMER0_TCNT0		0
#endif


/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										Timer 1													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/


#if USE_TIMER1 == 1
	// Timer1 MODEs
	#define TIMER1_MODE_0	0
	#define TIMER1_MODE_1	1
	#define TIMER1_MODE_2	2
	#define TIMER1_MODE_3	3
	#define TIMER1_MODE_4	4
	#define TIMER1_MODE_5	5
	#define TIMER1_MODE_6	6
	#define TIMER1_MODE_7	7
	#define TIMER1_MODE_8	8
	#define TIMER1_MODE_9	9
	#define TIMER1_MODE_10	10
	#define TIMER1_MODE_11	11
	#define TIMER1_MODE_12	12
//	#define TIMER1_MODE_13	13	// Reserved
	#define TIMER1_MODE_14	14
	#define TIMER1_MODE_15	15

	// Timer 1 Pre-Scaler
	#define TIMER1_PRESCALER_NO_CLOCK			0
	#define TIMER1_PRESCALER_NO_NOPRESCALING	1
	#define TIMER1_PRESCALER_8					2
	#define TIMER1_PRESCALER_64					3
	#define TIMER1_PRESCALER_256				4
	#define TIMER1_PRESCALER_1024				5
	#define TIMER1_PRESCALER_EXTERNAL_FALING	6
	#define TIMER1_PRESCALER_EXTERNAL_RISING	7
	// Enable Interrupt
	#define TIMER1_OVF_INTERRUPT	0
	#define TIMER1_OCRA_INTERRUPT 	0
	#define TIMER1_OCRB_INTERRUPT 	0
	#define TIMER1_ICU_INTERRUPT 	0

	#define COMP1_NORMAL			0
	#define COMP1_TOGGLE			1
	#define COMP1_NONINVERTED	2
	#define COMP1_INVERTED		3

	#define TIMER1_COMPA_MODE	COMP1_NONINVERTED
	#define TIMER1_COMPB_MODE	COMP1_NORMAL

	// Timer 1 Mode Select
	#define TIMER1_MODE_SELECT TIMER1_MODE_14
	// Timer 1 Prescaler select
	#define TIMER1_PRESCALER_SELECT TIMER1_PRESCALER_64
	// Timer 1 Initial Value
	#define TIMER1_TCNT1		0

#endif


/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/
/*										Timer 2													 */
/*/////////////////////////////////////////////////////////////////////////////////////////////////////*/


#if USE_TIMER2 == 1
	// Timer2 MODEs
	#define TIMER2_MODE_NORMAL			0
	#define TIMER2_MODE_CTC				1
	#define TIMER2_MODE_PWM_FAST		2
	#define TIMER2_MODE_PWM_PHASE		3

	#define TIMER2_MODE_SELECT TIMER2_MODE_CTC


	// Timer 2 Pre-Scaler
	#define TIMER2_PRESCALER_NO_CLOCK			0
	#define TIMER2_PRESCALER_NO_NOPRESCALING	1
	#define TIMER2_PRESCALER_8					2
	#define TIMER2_PRESCALER_32					3
	#define TIMER2_PRESCALER_64					4
	#define TIMER2_PRESCALER_128				5
	#define TIMER2_PRESCALER_256				6
	#define TIMER2_PRESCALER_1024				7

	// Wave Generation Mode
	#define COMP2_NORMAL			0
	#define COMP2_TOGGLE			1
	#define COMP2_NONINVERTED		2
	#define COMP2_INVERTED			3
	// How OC0 Handled in Timer 0
	#define TIMER2_COMP2_MODE	COMP2_INVERTED

	// Enable Interrupt
	#define TIMER2_OVF_INTERRUPT 1
	#define TIMER2_OCR_INTERRUPT 0

	#define TIMER2_PRESCALER_SELECT TIMER2_PRESCALER_1024
	// Timer Initial Value
	#define TIMER2_TCNT0		0
#endif

#endif
