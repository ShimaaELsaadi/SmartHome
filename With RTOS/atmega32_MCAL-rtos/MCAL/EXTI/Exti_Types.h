#ifndef _EXTI_TYPES_H_
#define _EXTI_TYPES_H_

typedef enum{
	EXTI0 ,	// PD2
	EXTI1 , // PD3
	EXTI2	// PB2
}Exti_SourceType;

typedef enum{
	SENSE_RISING , SENSE_FAILING , SENSE_LOW , SENSE_HIGH , SENSE_ANY
}Exti_SenseType;

typedef void (*Exti_ISR)(void);

#endif
