#include <Dio.h>
#include <Dio_Cfg.h>
#include <Lcd.h>
#include <avr/io.h>
#include <FreeRTOS.h>
#include <task.h>
#include <FreeRTOSConfig.h>
#include <Uart.h>
#include <queue.h>


TaskHandle_t uart_Handle = NULL;
TaskHandle_t led_Handle = NULL;
TaskHandle_t button_Handle = NULL;
TaskHandle_t lcd_Handle = NULL;

QueueHandle_t uart_queue = NULL;
QueueHandle_t button_queue = NULL;

BaseType_t xHigherPriorityTaskWoken = pdFALSE;

void uart_callBack(uint8 data){
	xQueueSendFromISR( uart_queue, &data, &xHigherPriorityTaskWoken );
}

void vTask_UartReceive(void *param);
void vTask_LedChange(void *param);
void vTask_ButtonRead(void *param);
void vTask_LcdPrint(void *param);


#define UART_PRIO 3
#define LED_PRIO 3
#define BUTTON_PRIO 3
#define LCD_PRIO 3

int main(){

	// uart_queue = xQueueCreate( 20 , sizeof(uint8));
	// button_queue = xQueueCreate( 20 , sizeof(uint8));
	// // Warning Led
	// Dio_InitChannel(GROUPB , PB7 , OUTPUT);
	// Dio_WriteChannel(GROUPB , PB7 , LOW);
	// if(uart_queue == NULL){
	// 	Dio_WriteChannel(GROUPB , PB7 , HIGH);
	// 	while (1);		
	// }else if(button_queue == NULL){
	// 	Dio_WriteChannel(GROUPB , PB7 , HIGH);
	// 	while (1);			
	// }

	// xTaskCreate(vTask_UartReceive , "Uart_Read"	,85	,NULL,UART_PRIO,	&uart_Handle);
	// xTaskCreate(vTask_LedChange , "led_change"	,85	,NULL,LED_PRIO,	&led_Handle);
	// xTaskCreate(vTask_ButtonRead , "button_read"	,85	,NULL,BUTTON_PRIO,	&button_Handle);
	// xTaskCreate(vTask_LcdPrint , "lcd_read"	,85	,NULL,LCD_PRIO,	&lcd_Handle);


	// /*start Scheduler */
	// vTaskStartScheduler();

	Lcd_Init();	Dio_InitChannel(GROUPA , PA4 , OUTPUT);
	Dio_WriteChannel(GROUPA , PA4 , HIGH);
	Lcd_String("Test Lcd after O0");
	while (1);	
}


void vTask_UartReceive(void *param){
	portTickType Freq = 100;
	portTickType Start = xTaskGetTickCount();
	
	Uart_Init();
	Uart_SetReadCallback(uart_callBack);

	while(1){
		
		vTaskDelayUntil(&Start,Freq);
	}
}

void vTask_LedChange(void *param){
	portTickType Freq = 500;
	portTickType Start = xTaskGetTickCount();
	
	Dio_InitChannel(GROUPA , PA4 , OUTPUT);
	uint8 data;
	while(1){	
	if( xQueueReceive( button_queue,
                         &( data ),
                         ( TickType_t ) 10 ) == pdPASS )
      {
         /* data now contains a copy of xMessage. */
		 Dio_FlipChannel(GROUPA , PA4);
      }

		vTaskDelayUntil(&Start,Freq);

	}
}

void vTask_ButtonRead(void *param){
	portTickType Freq = 100;
	portTickType Start = xTaskGetTickCount();
	
	Dio_InitChannel(GROUPD , PD7 , INPUT_PULLUP);

	while(1){
		// if button is pressed
		if(Dio_ReadChannel(GROUPD , PD7) == LOW){
			vTaskDelay(20);
			uint8 pressed = 1;
			xQueueSend( /* The handle of the queue. */
               button_queue,
               /* The address of the xMessage variable.  sizeof( struct AMessage )
               bytes are copied from here into the queue. */
               ( void * ) &pressed,
               /* Block time of 0 says don't block if the queue is already full.
               Check the value returned by xQueueSend() to know if the message
               was sent to the queue successfully. */
               ( TickType_t ) 0 );

		}
		vTaskDelayUntil(&Start,Freq);
	}
}


void vTask_LcdPrint(void *param){
	portTickType Freq = 100;
	portTickType Start = xTaskGetTickCount();
	
	Lcd_Init();

	uint8 data =0;

	while(1){
		if( xQueueReceive( button_queue,&( data ), ( TickType_t ) 10 ) == pdPASS ){
			/* data now contains a copy of xMessage. */
			Lcd_Char(data);
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
