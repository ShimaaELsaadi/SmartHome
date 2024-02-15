#include <Dio.h>
#include <Lcd.h>
#include <Uart.h>
#include <Keypad.h>
#include <Adc.h>

#include <FreeRTOS.h>
#include <task.h>
#include <FreeRTOSConfig.h>
#include <queue.h>
#include <semphr.h>


TaskHandle_t keypad_Handle = NULL;
TaskHandle_t lcd_Handle = NULL;
TaskHandle_t main_handle = NULL;
TaskHandle_t login_handle = NULL;
TaskHandle_t adc_motor_handle = NULL;


QueueHandle_t keypad_queue = NULL;
QueueHandle_t lcd_queue = NULL;

void vTask_AdcMotor(void *param);
void vTask_KeypadRead(void *param);
void vTask_LcdPrint(void *param);
void vTask_MainTask(void *param);
void vTask_login(void *param);

#define KEYPAD_PRIO 	3
#define LCD_PRIO 		3
#define MAIN_PRIO		3
#define LOG_PRIO		3	
#define AM_PRIO			4

volatile uint8 need_login =1;

int main(){
	// Warning Led
	Dio_InitChannel(GROUPB , PB7 , OUTPUT);
	Dio_WriteChannel(GROUPB , PB7 , LOW);

	// queue definition
	keypad_queue = xQueueCreate( 20 , sizeof(uint8));
	lcd_queue = xQueueCreate( 20 , sizeof(uint16));
	
	if(keypad_queue == NULL){
		Dio_WriteChannel(GROUPB , PB7 , HIGH);
		while (1);			
	}else if(lcd_queue == NULL){
		Dio_WriteChannel(GROUPB , PB7 , HIGH);
		while (1);	
	}


	// task creation
	xTaskCreate(vTask_AdcMotor 	, "vTask_AdcMotor"		,85	,NULL,AM_PRIO		,	&adc_motor_handle);
	xTaskCreate(vTask_KeypadRead, "vTask_KeypadRead",85	,NULL,KEYPAD_PRIO	,	&keypad_Handle);
	xTaskCreate(vTask_LcdPrint 	, "vTask_LcdPrint"	,85	,NULL,LCD_PRIO		,	&lcd_Handle);
	xTaskCreate(vTask_login 	, "vTask_login"		,85	,NULL,LOG_PRIO		,	&login_handle);
	//xTaskCreate(vTask_MainTask 	, "vTask_MainTask"	,85	,NULL,MAIN_PRIO		,	&main_handle);

	/*start Scheduler */
	vTaskStartScheduler();
	while (1);

}


void vTask_KeypadRead(void *param){
	portTickType Freq = 100;
	portTickType Start = xTaskGetTickCount();
	
	Keypad_Init();
	uint8 key;
	while(1){
		key = Keypad_GetKey();
		if(key != NONE){
			xQueueSend(keypad_queue,( void * ) &key,portMAX_DELAY );
		}
		vTaskDelayUntil(&Start,Freq);
	}
}


void vTask_LcdPrint(void *param){
	portTickType Freq = 50;
	portTickType Start = xTaskGetTickCount();
	
	Lcd_Init();
	
	uint16 qdata =0;

	while(1){
		if( xQueueReceive( lcd_queue, &( qdata), portMAX_DELAY) == pdPASS ){
			uint8 command = qdata >> 8;
			uint8 data = (uint8)qdata;
			switch (command)
			{
				case 0x00:// print directly
					Lcd_Char(data);
					break;
				case 0x01: // clear screen
					Lcd_Clear();
					break;
				case 0x03:
					Lcd_Clear();
					Lcd_String("SMart_Home	:");
					vTaskDelay(1000);
					Lcd_Clear();
					break;
				case 0x04:
					// password screen
					Lcd_Clear();
					Lcd_String("Enter Password	:");
					break;
				case 0x05:
					Lcd_Clear();
					Lcd_String("Welcom Home	:");
					break;
				case 0xfe:
					// password screen
					Lcd_Clear();
					Lcd_String("Re-loging	:");
					break;
				case 0xff:
					// password screen
					Lcd_Clear();
					Lcd_String("Wrong Password	:");
					break;
				default:
					break;
				}
		}
		vTaskDelayUntil(&Start,Freq);
	}
}

uint8 pass_arry[]={'1','1','5'};
#define PASS_LENGTH 3


void vTask_login(void *param){
	if(main_handle != NULL){
		vTaskDelete(main_handle);
		main_handle = NULL;
	}

	Dio_InitChannel(GROUPC , PC6 , OUTPUT);
	Dio_WriteChannel(GROUPC , PC6 , LOW);
	uint8 keypad_data;
	uint16 lcd_data;
	uint8 counter =0;
	
	lcd_data = 0x0300;
	xQueueSend(lcd_queue , &lcd_data , portMAX_DELAY );

	lcd_data = 0x0400;
	xQueueSend(lcd_queue , &lcd_data , portMAX_DELAY );

	while (1)
	{
		if(xQueueReceive( keypad_queue, &( keypad_data), portMAX_DELAY) == pdPASS){
			if(pass_arry[counter] == Keypad_KeyCodeToChar(keypad_data)){
				lcd_data = '*';
				while(xQueueSend(lcd_queue , &lcd_data , (TickType_t) 0 ) != pdPASS);
				counter++;
				if(counter == PASS_LENGTH){
					xTaskCreate(vTask_MainTask 	, "vTask_MainTask"	,85	,NULL,MAIN_PRIO		,	&main_handle);
					while (1)
					{
						vTaskDelay(1000);
					}
				}
			}else{
				// wrong password
				Dio_WriteChannel(GROUPB , PB7 , LOW);
				lcd_data = 0xff00;
				while(xQueueSend(lcd_queue , &lcd_data , (TickType_t) 0 ) != pdPASS);
				while(1){
					Dio_FlipChannel(GROUPC , PC6);
					Dio_FlipChannel(GROUPB , PB7);
					vTaskDelay(200);
				}
			}
		}
	}
}

void vTask_MainTask(void *param){
	if(login_handle != NULL){
		vTaskDelete(login_handle);
		login_handle = NULL;
	}
	portTickType Freq = 50;
	portTickType Start = xTaskGetTickCount();

	uint8 keypad_data =0;
	uint16 lcd_data = 0x0500;
	while(xQueueSend(lcd_queue , &(lcd_data) , portMAX_DELAY) != pdPASS);


	Dio_InitChannel(GROUPA , PA6 , OUTPUT);
	Dio_WriteChannel(GROUPA , PA6 , LOW);

	while(1){
		if( xQueueReceive( keypad_queue, &( keypad_data), ( TickType_t ) 10 ) == pdPASS ){
			switch(keypad_data){
				case SW_1 : 
					{
						lcd_data = 'a';
						while(xQueueSend(lcd_queue , &(lcd_data) , 20 ) != pdPASS);
						Dio_FlipChannel(GROUPA , PA6);
					}
				break;
				case SW_2 : 
					{
						lcd_data= 0x0100;
						while(xQueueSend(lcd_queue , &(lcd_data) , 20 ) != pdPASS);
					}
				break;
				case SW_3 : 
				{
						lcd_data = 0x0300;
						while(xQueueSend(lcd_queue , &(lcd_data) , 20 ) != pdPASS);
					}
				break;
				case SW_4 : break;
				case SW_5 : break;
				case SW_6 : break;
				case SW_7 : break;
				case SW_8 : break;
				case SW_9 : break;
				case SW_10: break;
				case SW_11: break;
				case SW_12: break;
				case SW_13: break;
				case SW_14: break;
				case SW_15: break;
				case SW_16: 
					// re-login
					lcd_data = 0xfe00;
					while(xQueueSend(lcd_queue , &(lcd_data) , 20 ) != pdPASS);
					xTaskCreate(vTask_login 	, "vTask_login"		,85	,NULL,LOG_PRIO		,	&login_handle);
					while (1)
					{
						vTaskDelay(1000);
					}
					
				break;
				default:
				break;
			}
		}
		vTaskDelayUntil(&Start,Freq);
	}
}


void vTask_AdcMotor(void *param){
	portTickType Freq = 70;
	portTickType Start = xTaskGetTickCount();
	Dio_InitChannel(GROUPA , PA1 , INPUT);
	Dio_InitChannel(GROUPA , PA5 , OUTPUT);
	
	Adc_Init();
	uint16 adc_data =0;
	while(1){
		adc_data = Adc_Read() * 0.25f;
		if(adc_data > 10){
			Dio_WriteChannel(GROUPA , PA5 , HIGH);
		}

		vTaskDelayUntil(&Start,Freq);
	}
}

void vApplicationIdleHook(){
	while (1)
	{
		/* code */
	}
	
}
