#include <Std_Types.h>
#include <Dio.h>
#include <SRV.h>
#include <Timer.h>

void SRV_Init(void)
{
	Timer_init();
}

void SRV_setAngle(uint8 angle)
{
	uint8 duty = (Max_duty*angle/Max_angle)+Min_duty;

	if(duty>Max_duty)
	{
		duty=Max_duty;
	}
	Timer_SetOCR1A(duty);
}

