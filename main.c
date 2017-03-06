/*	Included Project Files		*/
#include <avr/interrupt.h>
#include "IR_Sensors/IR_Config.h"
#include "toStr/toStr_Config.h"
#include "ADC/ADC_Config.h"
#include "UART/UART_Config.h"
#include "LCD/LCD_Config.h"
#include "GPS/GPS_Config.h"
#include "SIM900/SIM900_Config.h"

/*      Tasks and functions declaration     */
void System_Init	( void );

/*	 Global Variables        	    */
extern GPS_Frames GPS;

int main(void){
	/*	System Initialization	*/
	System_Init();

	/*	 Local Variables	*/
	u8 Emergency_Flag = 0;
	u32 ADC_TempRead  = 0;
	u8 Temprature [5] = {0};
		
	/*	 While Loop		*/
	while (1){
		ADC_TempRead = ADC_Scan(0);
		ADC_TempRead = (ADC_TempRead * 1000) / 2048;
		toStr(ADC_TempRead, Temprature, 4);
		LCD_Print(0, 0, Temprature);
		if (ADC_TempRead >= 65){
			Emergency_Flag ='F';
			GPS_Update();
			SIM900_Send (Emergency_Flag, GPS.Longitude, GPS.Latitude, GPS.Altitude, GPS.Time);
		}
		else if(Accident_Check()){
			Emergency_Flag ='A';
			GPS_Update();
			SIM900_Send (Emergency_Flag, GPS.Longitude, GPS.Latitude, GPS.Altitude, GPS.Time);
		}
	}
}

void System_Init( void ){
	/*		USART Initialization			*/
	Struct_USART USART_Init_Struct;
	USART_Init_Struct.BuadRate	=	9600;
	USART_Init_Struct.Operation_Mode=	Asynchronous_Normal_Speed;
	USART_Init_Struct.Duplex_Select	=	TX_RX_Mode;
	USART_Init_Struct.Char_Size	=	Char_8_Bits;
	USART_Init_Struct.Stop_Bit	=	One_Bit;
	USART_Init_Struct.Parity_Mode	=	No_Parity;
	USART_Init(USART_Init_Struct);

	/*		ADC Initialization			*/
	Struct_ADC	ADC_Init_Struct;
	ADC_Init_Struct.Vref_Ref_Sel	=	Vref_VCC_With_ext_cap;
	ADC_Init_Struct.Result_Adjust	=	Right_Adjustment;
	ADC_Init_Struct.Prescaler_Sel	=	Division_Factor_128;
	ADC_Init_Struct.Running_Mode	=	Disable;
	ADC_Init_Struct.Interrupt_Sel	=	Enable;
	ADC_Init(ADC_Init_Struct);
	
	/*		LCD Initialization			*/
	LCD_Init(&PINC, &PINC, 2,1,0,3,4,5,6);
	
	/*		IR Sensors pins Initialization		*/
	IR_Sensors_Init();
}
