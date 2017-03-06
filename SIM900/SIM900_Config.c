#include "SIM900_Config.h"
#include "../Functions_Prototypes/UART_Function_Prototypes.h"

/********************************************************************************************
  Name:     SIM900_Send.
  Purpose:  Function used to send Data to the GSM network.
  Entry:    		Longitude
			Latitude
			Altitude
			Time

  Exit:		No parameters.
********************************************************************************************/
void SIM900_Send ( u8 Alarm, u8* Longitude, u8* Latitude, u8* Altitude, u8* Time){
	u8 msg0 []	= {"AT\r"};			/*	Check the connectivity of the Module		*/
	u8 msg1 []	= {"AT+CSMINS?\r"};		/*	Check if the SIM card is inserted to the module	*/
	u8 msg2 []	= {"AT+CREG?\r"};		/*	Check if the SIM is registered to the network	*/
	u8 msg3 []	= {"AT+CMGF=1\r"};		/*	Set the communication to TEXT mode		*/
	u8 msg4 []	= {"AT+CMGS="};			/*	Command used to send a MSG from the module	*/
	u8 msg5 []	= {'"', '+', '2', '0' , '1', '1',
			   '1', '1', '4', '9' , '4', '9',
			   '8', '4', '"', '\r', '\0'};
	u8 msg6		= (char)26;					/*	^z	*/
	u8 msg_Fire		[]	=	{"Fire Alarm ON"};	/*	Fire Alarm Massage	*/
	u8 msg_Accident	[]	=	{"Car Crash Happened"};		/*	Accident Massage	*/
	
	USART_Transmit_String(msg0);
	_delay_ms(100);
	USART_Transmit_String(msg1);
	_delay_ms(100);
	USART_Transmit_String(msg2);
	_delay_ms(100);
	USART_Transmit_String(msg3);
	_delay_ms(100);
	USART_Transmit_String(msg4);
	_delay_ms(100);
	USART_Transmit_String(msg5);
	_delay_ms(100);
	if (Alarm == 'F'){
		USART_Transmit_String(msg_Fire);
		USART_Transmit('\r');
		_delay_ms(100);
	}
	else if(Alarm == 'A'){
		USART_Transmit_String(msg_Accident);
		USART_Transmit('\r');
		_delay_ms(100);
	}
	USART_Transmit_String(Longitude);
	USART_Transmit('\r');
	_delay_ms(100);
	USART_Transmit_String(Latitude);
	USART_Transmit('\r');
	_delay_ms(100);
	USART_Transmit_String(Altitude);
	USART_Transmit('\r');
	_delay_ms(100);
	USART_Transmit_String(Time);
	USART_Transmit('\r');
	_delay_ms(100);
	USART_Transmit(msg6);
	_delay_ms(1000);
}
