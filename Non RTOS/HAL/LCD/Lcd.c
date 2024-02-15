#include <Lcd.h>
#include <Dio.h>
#include <Dio_Cfg.h>
#include <util/delay.h>
#include <Std_Types.h>

static uint8 _row =0;
static uint8 _col =-1;

static uint8 row_offset[] = {0x00 , 0x40 , 0x14 , 0x54};

void Lcd_Init(){
	Dio_Init();

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

	// RS =0
	Dio_WriteChannel(RS_GROUP , RS , HIGH);
	// enable pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP , EN , LOW);
	_delay_us(200);

	// sending lower nipple
	Dio_WriteChannel(D4_GROUP , D4 , (data & 1<<0)>>0);
	Dio_WriteChannel(D5_GROUP , D5 , (data & 1<<1)>>1);
	Dio_WriteChannel(D6_GROUP , D6 , (data & 1<<2)>>2);
	Dio_WriteChannel(D7_GROUP , D7 , (data & 1<<3)>>3);

	// enable pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP , EN , LOW);
	_delay_ms(2);
}

void Lcd_SendCommand(uint8 command){
	// sending upper nipple
	Dio_WriteChannel(D4_GROUP , D4 , (command & 1<<4)>>4);
	Dio_WriteChannel(D5_GROUP , D5 , (command & 1<<5)>>5);
	Dio_WriteChannel(D6_GROUP , D6 , (command & 1<<6)>>6);
	Dio_WriteChannel(D7_GROUP , D7 , (command & 1<<7)>>7);

	// RS =0
	Dio_WriteChannel(RS_GROUP , RS , LOW);
	// enable pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP ,EN , LOW);
	_delay_us(200);

	// sending lower nipple
	Dio_WriteChannel(D4_GROUP , D4 , (command & 1<<0)>>0);
	Dio_WriteChannel(D5_GROUP , D5 , (command & 1<<1)>>1);
	Dio_WriteChannel(D6_GROUP , D6 , (command & 1<<2)>>2);
	Dio_WriteChannel(D7_GROUP , D7 , (command & 1<<3)>>3);

	// enable pulse
	Dio_WriteChannel(EN_GROUP , EN , HIGH);
	_delay_us(1);
	Dio_WriteChannel(EN_GROUP , EN , LOW);
	_delay_ms(2);
}


void Lcd_Char(uint8 data){
	_col++;
	if(_col>19){
		_col =0;
		_row++;
		if(_row > 4 ){
			_row =0;
		}
	}
	uint8 address = ( 0x80 | ( (row_offset[_row]) + _col) );
	// reset to next line
	Lcd_SendCommand(address);
	Lcd_SendData(data);
}

void Lcd_Clear(){
	Lcd_SetCurse(0,0);
	Lcd_SendCommand(0x01);
	_delay_ms(2);
	Lcd_SendCommand(0x80);
}

void Lcd_SetCurse(uint8* row,uint8* col){
	_col = *col;
	_row = *row;
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



