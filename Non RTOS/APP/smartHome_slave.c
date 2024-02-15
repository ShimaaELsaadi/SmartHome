#include <Dio_Cfg.h>
#include <Dio.h>
#include <Lcd.h>
#include <Keypad.h>
#include <Uart.h>
#include <EEPROM.h>
#include <Std_Types.h>
#include <util/delay.h>
#include <SRV.h>

uint8 uart_data = 0xff;
void uart_read(uint8 y){
    uart_data = y;
}

void light_on(){
    Dio_WriteChannel(GROUPB , PB0 , HIGH);
}

void light_off(){
    Dio_WriteChannel(GROUPB , PB0 , LOW);
}

uint8 read(){
    uint8 x =0xff;
    // check if key is pressed
    x = Keypad_CharToInt(Keypad_KeyCodeToChar(Keypad_GetKey()));
    if(x != 0xff){
        return x;
    }else if(uart_data != 0xff){
        x = uart_data;
        uart_data = 0xff; // reset uart data
        return x;
    }
    // if we reach here we return 0xff -> no value
    return x;
}

int main(){
    Lcd_Init();
    Keypad_Init();
    SRV_Init();
    Uart_Init();
    Uart_SetReadCallback(uart_read);
    while (1){
        uint8 state = read();
        if(state == 200){
            // admin mode
            // waiting for admin commands
        }else if(state != 0xff){
            // execute feature
            feature(state);
        }
    }
    return 0;
}


void feature(uint8 x){
    switch (x)
    {
    case 0:     // light on 
        light_on();
        break;
    case 1:     // light off
        light_off();
        break;
    case 2:     // open door
        SRV_setAngle(0);
        break;
    case 3:     // open door
        SRV_setAngle(180);
        break;

    
    default:
        break;
    }
}