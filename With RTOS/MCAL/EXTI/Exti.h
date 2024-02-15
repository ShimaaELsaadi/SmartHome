#ifndef MCAL_EXTI_EXTI_H_
#define MCAL_EXTI_EXTI_H_

#include <Exti_Types.h>

void Exti_Enable(Exti_SourceType source, Exti_SenseType sense, Exti_ISR isr);
void Exti_Disable(Exti_SourceType source);


#endif /* MCAL_EXTI_EXTI_H_ */
