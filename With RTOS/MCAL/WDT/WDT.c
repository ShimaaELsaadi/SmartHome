#include <Std_Types.h>
#include <WDT.h>
#include <atmega32_Reg.h>


#define WDT_16_3_ms		0
#define WDT_32_5_ms		1
#define WDT_65_3_ms		2
#define WDT_0_13_s		3
#define WDT_0_26_s		4
#define WDT_0_52_ms		5
#define WDT_1_0_s		6
#define WDT_2_1_ms		7

#define WDT_TIME WDT_2_1_ms

void WDT_Off(){
	_WDTCR = (1<<3) | (1<<4);
	_WDTCR = 0x00;
}

void WDT_On(){
	_WDTCR &=~(0xF8);
	_WDTCR |= WDT_TIME;
	_WDTCR |= 1<<3;
}
