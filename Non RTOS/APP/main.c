#include <Dio_Cfg.h>
#include <Dio.h>
#include <atmega32_Reg.h>
#include <util/delay.h>

int main(){
    _DDRB |= 1<<0;
    _PORTB |= 1<<0;
    while(1);
    return 0;
}
