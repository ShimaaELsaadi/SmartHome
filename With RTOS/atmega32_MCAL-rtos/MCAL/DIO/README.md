# Digital Input Output Module

## Methods

This module is reposnible for handling and configuration of all input/output pins on the microcontroller
we are using post-compilation concept to configuer dio module throw Pin_Configs array in Dio_Cfg.h file

## Major Function : 
- **void Dio_init();**
    This function is reposible for initializing All configured pin in Dio_Cfg.c file.
- **void Dio_WriteChannel(Pin_Channel pin, Pin_Channel_State state);**
    This function is used to write a digital value to a pin whether _HIGH_ or _LOW_
- **void Dio_ReadChannel()**
    This function is used to read pin state and return either _HIGH_ or _LOW_
- **void DIO_Init_Channel(Pin_Channel pin ,Pin_Channel_Direction dir);**
    This function is used to re-initialize pin in runtime by passing pin number and direction . 

## How to use Dio module 
This module depends on **atmega32_REG.h** , **Std_Types.h** and **Bit_Math.h** files in utils directory

## Depends 
This module depend on :
* **atmega32_REG**
* **Bit_Math.h**
* **Std_Types.h** 

