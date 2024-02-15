#include <Std_Types.h>
#include <avr/io.h>
#include <Adc.h>
#include <Bit_Math.h>

void Adc_Init()
{
    SET_BIT(ADMUX,REFS0);
    SET_BIT(ADMUX,REFS1);
    SET_BIT(ADCSRA,ADEN);
    SET_BIT(ADCSRA,ADPS0);
    SET_BIT(ADCSRA,ADPS1);
    SET_BIT(ADCSRA,ADPS2);
    SET_BIT(ADMUX,0);
    CLEAR_BIT(ADMUX,1);
    CLEAR_BIT(ADMUX,2);
}

uint16 Adc_Read()
{
	uint16 ADC_VALUE;
	SET_BIT(ADCSRA,ADSC);
	while(GET_BIT(ADCSRA,ADIF)==0);
	SET_BIT(ADCSRA,ADIF);
	ADC_VALUE=ADC;
	return ADC_VALUE;
}
