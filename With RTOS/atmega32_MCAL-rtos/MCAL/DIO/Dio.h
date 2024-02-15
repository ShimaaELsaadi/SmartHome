#ifndef DIO_H_
#define DIO_H_

#include <Dio_Types.h>
#include <Std_Types.h>

void Dio_InitChannel(Pin_Group group, Pin_Channel pin ,Pin_Channel_Direction dir);
void Dio_WriteChannel(Pin_Group group,Pin_Channel pin ,Pin_Channel_State state);
uint8 Dio_ReadChannel(Pin_Group group,Pin_Channel pin);
uint8 Dio_FlipChannel(Pin_Group group,Pin_Channel pin);

#endif

