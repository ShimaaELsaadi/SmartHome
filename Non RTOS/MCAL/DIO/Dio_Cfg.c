#include <Dio_Cfg.h>


#define NUM_OF_DIO 2

Pin_Config_t Pin_Configs[]={
		{GROUPB,PB0  , OUTPUT},
		{GROUPD,PD5  , OUTPUT}
};

void Dio_Init(){
	int i=0;
	for (int i = 0; i < NUM_OF_DIO; i++) {
		Dio_InitChannel(Pin_Configs[i].GROUP ,Pin_Configs[i].PORT ,Pin_Configs[i].DDR );
	}
}
