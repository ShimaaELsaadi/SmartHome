#ifndef MCAL_DIO_DIO_CFG_H_
#define MCAL_DIO_DIO_CFG_H_

#include <Dio.h>

typedef struct{
	Pin_Channel PORT;
	Pin_Group GROUP;
	Pin_Channel_Direction DDR;
}Pin_Config_t;

void Dio_Init();


#endif /* MCAL_DIO_DIO_CFG_H_ */
