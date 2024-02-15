#ifndef MCAL_TWI_TWI_H_
#define MCAL_TWI_TWI_H_

#include <Std_Types.h>


void Twi_InitMaster();
void Twi_Start();
void Twi_RepetedStart();
void Twi_SendSlaveAddressWithWrite(uint8 slad);
void Twi_sendSlaveAddressWithRead(uint8 slad);
void Twi_MasterSendByte(uint8 data);
void Twi_MasterReadByte(uint8 data);



void Twi_Stop();


#endif

