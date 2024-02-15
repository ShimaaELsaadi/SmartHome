#ifndef MCAL_TIMER_TIMER_H_
#define MCAL_TIMER_TIMER_H_

#include <Timer_Types.h>
#include <Std_Types.h>

void Timer_init();

void Timer_SetTimer0_OVF_Callback(Timer_Interrupt_P2F);
void Timer_SetTimer0_OCR_Callback(Timer_Interrupt_P2F);

void Timer_SetOCR0(uint8);
void Timer_SetTCNT0(uint8);

void Timer_SetTimer0_OVF_Callback(Timer_Interrupt_P2F);
void Timer_SetTimer0_OCR_Callback(Timer_Interrupt_P2F);

void Timer_SetTimer1_OVF_Callback(Timer_Interrupt_P2F);
void Timer_SetTimer1_OCRA_Callback(Timer_Interrupt_P2F);
void Timer_SetTimer1_OCRB_Callback(Timer_Interrupt_P2F);
void Timer_SetTimer1_ICU_Callback(Timer_Interrupt_P2F);


void Timer_SetTCNT1(uint16);
void Timer_SetOCR1A(uint16);
void Timer_SetOCR1B(uint16);
void Timer_SetICR1(uint16);

#endif
