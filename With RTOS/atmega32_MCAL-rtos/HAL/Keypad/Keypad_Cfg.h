#ifndef HAL_KEYPAD_KEYPAD_CFG_H_
#define HAL_KEYPAD_KEYPAD_CFG_H_

#define R1 PC5
#define R2 PC4
#define R3 PC3
#define R4 PC2

#define C1 PD7
#define C2 PD6
#define C3 PD5
#define C4 PD3

#define R1_GROUP GROUPC
#define R2_GROUP GROUPC
#define R3_GROUP GROUPC
#define R4_GROUP GROUPC

#define C1_GROUP GROUPD
#define C2_GROUP GROUPD
#define C3_GROUP GROUPD
#define C4_GROUP GROUPD

typedef enum {
	SW_1=0	,SW_2	,SW_3,	SW_4,
	SW_5	,SW_6	,SW_7,	SW_8,
	SW_9	,SW_10	,SW_11,	SW_12,
	SW_13	,SW_14	,SW_15,	SW_16,
	NONE
}Keypad_KeyCoodeType;



#endif /* HAL_KEYPAD_KEYPAD_CFG_H_ */
