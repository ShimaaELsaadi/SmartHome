#include <Lcd.h>
#include <Dio.h>
#include <Dio_Cfg.h>
#include <util/delay.h>
#include <Std_Types.h>
#include <avr/io.h>

static uint8 _row =0;
static uint8 _col =-1;

static uint8 row_offset[] = {0x00 , 0x40 , 0x14 , 0x54};

#define D4 PB0
#define D5 PB1
#define D6 PB2
#define D7 PB4

#define D4_GROUP GROUPB
#define D5_GROUP GROUPB
#define D6_GROUP GROUPB
#define D7_GROUP GROUPB

#define RS PA3
#define EN PA2

#define RS_GROUP GROUPA
#define EN_GROUP GROUPA

void Lcd_Init(){
	// LCD Pins Inilization
	Dio_InitChannel(D4_GROUP , D4 , OUTPUT);
	Dio_InitChannel(D5_GROUP , D5 , OUTPUT);
	Dio_InitChannel(D6_GROUP , D6 , OUTPUT);
	Dio_InitChannel(D7_GROUP , D7 , OUTPUT);

	Dio_InitChannel(RS_GROUP , RS , OUTPUT);
	Dio_InitChannel(EN_GROUP , EN , OUTPUT);


	// Lcd Init
	Lcd_SendCommand(0x33);
	Lcd_SendCommand(0x32);
	Lcd_SendCommand(0x28);
	Lcd_SendCommand(0x0C);
	Lcd_SendCommand(0x06);
	Lcd_SendCommand(0x01);
}

void Lcd_SendData(uint8 data){
	// sending upper nipple
	Dio_WriteChannel(D4_GROUP , D4 , (data& 1<<4)>>4);
	Dio_WriteChannel(D5_GROUP , D5 , (data& 1<<5)>>5);
	Dio_WriteChannel(D6_GROUP , D6 , (data& 1<<6)>>6);
	Dio_WriteChannel(D7_GROUP , D7 , (data& 1<<7)>>7);

	// RS = 1 - Data Register
	Dio_WriteChannel(RS_GROUP , RS , HIGH);
	// enable pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP , EN , LOW);
	_delay_ms(30);

	// sending lower nipple
	Dio_WriteChannel(D4_GROUP , D4 , (data & 1<<0)>>0);
	Dio_WriteChannel(D5_GROUP , D5 , (data & 1<<1)>>1);
	Dio_WriteChannel(D6_GROUP , D6 , (data & 1<<2)>>2);
	Dio_WriteChannel(D7_GROUP , D7 , (data & 1<<3)>>3);

	// enable pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP , EN , LOW);
	_delay_ms(30);
}

void Lcd_SendCommand(uint8 command){
	// sending upper nipple
	Dio_WriteChannel(D4_GROUP , D4 , (command & 1<<4)>>4);
	Dio_WriteChannel(D5_GROUP , D5 , (command & 1<<5)>>5);
	Dio_WriteChannel(D6_GROUP , D6 , (command & 1<<6)>>6);
	Dio_WriteChannel(D7_GROUP , D7 , (command & 1<<7)>>7);

	// RS =0 - Command Register
	Dio_WriteChannel(RS_GROUP , RS , LOW);
	// Enable Pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP ,EN , LOW);
	_delay_us(30);

	// sending lower nipple
	Dio_WriteChannel(D4_GROUP , D4 , (command & 1<<0)>>0);
	Dio_WriteChannel(D5_GROUP , D5 , (command & 1<<1)>>1);
	Dio_WriteChannel(D6_GROUP , D6 , (command & 1<<2)>>2);
	Dio_WriteChannel(D7_GROUP , D7 , (command & 1<<3)>>3);

	// enable pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP , EN , LOW);
	_delay_ms(30);
}


void Lcd_Char(uint8 data){
	Lcd_SendData(data);
}

void Lcd_Clear(){
	Lcd_SendCommand(0x01);
	_delay_ms(2);
	Lcd_SendCommand(0x80);
	_delay_ms(2);
}

void Lcd_SetCurse(uint8* row,uint8* col){

}

void Lcd_String(char* str){
	int i=0;
	while(str[i] != '\0'){
		Lcd_Char(str[i++]);
	}
}
static char int_to_char(uint8 x){
	return x + '0';
}
void Lcd_int(int32 x){
	// TODO
}



