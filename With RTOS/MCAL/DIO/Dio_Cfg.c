#include <Dio_Cfg.h>


#define NUM_OF_DIO 3

Pin_Config_t Pin_Configs[NUM_OF_DIO]={
		{GROUPB,PB7  , OUTPUT},		// Red
		{GROUPA,PA5  , OUTPUT},		// Blue
		{GROUPA,PA4  , OUTPUT}		// Green
};

void Dio_Init(){
	volatile int i=0;
	for (i = 0; i < NUM_OF_DIO; i++) {
		Dio_InitChannel(Pin_Configs[i].GROUP ,Pin_Configs[i].PORT ,Pin_Configs[i].DDR );
	}
}
