#include <Keypad.h>
#include <Dio.h>

void Keypad_Init(){
	Dio_WriteChannel(R1_GROUP , R1, HIGH);
	Dio_WriteChannel(R2_GROUP , R2, HIGH);
	Dio_WriteChannel(R3_GROUP , R3, HIGH);
	Dio_WriteChannel(R4_GROUP , R4, HIGH);
}

Keypad_KeyCoodeType key_codes[5][4] ={	{SW_1	,SW_2	,SW_3,	SW_4},
										{SW_5	,SW_6	,SW_7,	SW_8},
										{SW_9	,SW_10	,SW_11,	SW_12},
										{SW_13	,SW_14	,SW_15,	SW_16},
										{NONE 	,NONE	,NONE ,	NONE}};

Keypad_KeyCoodeType Keypad_GetKey(){
	uint8 row_counter=0,col_counter=0;
	uint8 rows[] = {R1 , R2 , R3 , R4};
	uint8 cols[] = {C1 , C2 , C3 , C4};
	uint8 rows_g[] = {R1_GROUP , R2_GROUP , R3_GROUP , R4_GROUP};
	uint8 cols_g[] = {C1_GROUP , C2_GROUP , C3_GROUP , C4_GROUP};

	for(;row_counter < 4 ;row_counter++){
		Dio_WriteChannel(rows_g[row_counter],rows[row_counter] , LOW);
		for(col_counter =0;col_counter < 4; col_counter++){
			uint8 val = Dio_ReadChannel(cols_g[col_counter] , cols[col_counter]);
			if(val == LOW){
				while(Dio_ReadChannel(cols_g[col_counter] , cols[col_counter]) == LOW);
				return key_codes[row_counter][col_counter];
			}

		}
		Dio_WriteChannel(rows_g[row_counter] , rows[row_counter] , HIGH);
	}
	return key_codes[4][0];
}

/*
 *
 *			{	1	,	 2	,	3	,	+	},
 *			{	4	,	 5	,	6	,	-	},
 *			{	7	,	 8	,	9	,	*	},
 **			{	CE	,	 0	,	=	,	/	},
 * */

char Keypad_KeyCodeToChar(Keypad_KeyCoodeType kc){
	char c;
	switch(kc){
		case SW_1 : c = '1';break;
		case SW_2 : c = '2';break;
		case SW_3 : c = '3';break;
		case SW_4 : c = '+';break;
		case SW_5 : c = '4';break;
		case SW_6 : c = '5';break;
		case SW_7 : c = '6';break;
		case SW_8 : c = '-';break;
		case SW_9 : c = '7';break;
		case SW_10: c = '8';break;
		case SW_11: c = '9';break;
		case SW_12: c = '*';break;
		case SW_13: c = 'C';break;
		case SW_14: c = '0';break;
		case SW_15: c = '=';break;
		case SW_16: c = '/';break;
	default:
		c='n';
	break;
	}

	return c;
}

uint8 Keypad_CharToInt(char kc){
	uint8 c;
	switch(kc){
		case '1': c = 1;  break;
		case '2': c = 2;  break;
		case '3': c = 3;  break;
		case '+': c = 4;  break;
		case '4': c = 5;  break;
		case '5': c = 6;  break;
		case '6': c = 7;  break;
		case '-': c = 8;  break;
		case '7': c = 9;  break;
		case '8': c = 10; break;
		case '9': c = 11; break;
		case '*': c = 12; break;
		case 'C': c = 13; break;
		case '0': c = 14; break;
		case '=': c = 15; break;
		case '/': c = 16; break;
	default:
		c=0xff;
	break;
	}

	return c;
}
