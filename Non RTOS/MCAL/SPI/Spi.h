#ifndef MCAL_SPI_SPI_H_
#define MCAL_SPI_SPI_H_

#include <Std_Types.h>

void Spi_Init();
void Spi_Write(uint8);
uint8 Spi_Transive(uint8);

void Spi_SetEndOfTtransmissionCallBack(void(*_ptrf)(uint8));

#endif

