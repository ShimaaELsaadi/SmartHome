#ifndef _EEPROM_H_
#define _EEPROM_H_

#include <Std_Types.h>


uint8 EEPROM_Read(uint16 addr);
void EEPROM_Write(uint16 addr , uint8 data);




#endif

