#include "UART_Config.h"

/********************************************************************************************
  Name:     USART_Init.
  Purpose:  Initialize USART registers for ATmega32.
  Entry:    ( Struct_USART USART_Config ) a STRUCT that setup the following.
							1) Baud Rate.
							2) Operation Mode(Normal and Double speed).
							3) Duplex selection.
							4) Character size.
							5) Stop bit set.
							6) Parity Mode.
							7) Interrupts Selection if required.
							8) Clock Polarity.
  Exit:     no parameters
********************************************************************************************/
void USART_Init(Struct_USART USART_Config){
	u16 UBRR;
	u8 Mode;
	if (USART_Config.Operation_Mode == Asynchronous_Double_Speed){Mode = 8UL;}
	else {Mode = 16UL;}
	UBRR  = (F_CPU/Mode/USART_Config.BuadRate) -1;
	UBRR0L = (u8)UBRR;
	UBRR0H = (u8)(UBRR >> 8);
	UCSR0C &=~(1 << UMSEL0);

	switch(USART_Config.Operation_Mode){
		case Synchronous				: UCSR0C |= (1U << UMSEL0); break;
		case Asynchronous_Normal_Speed	: UCSR0C &=~(1U << UMSEL0); UCSR0A &=~(1U << U2X0); break;
		case Asynchronous_Double_Speed	: UCSR0C &=~(1U << UMSEL0); UCSR0A |= (1U << U2X0); break;
		default							: UCSR0C &=~(1U << UMSEL0); UCSR0A &=~(1U << U2X0); break;
	}
	
	switch(USART_Config.Duplex_Select){
		case TX_Mode	: UCSR0B |= (1U << TXEN0); break;
		case RX_Mode	: UCSR0B |= (1U << RXEN0); break;
		case TX_RX_Mode : UCSR0B |= (1U << TXEN0)|(1U << RXEN0); break;
		default			: UCSR0B |= (1U << TXEN0); break; 
	}
	
	switch(USART_Config.Char_Size){
		case Char_5_Bits : UCSR0B &=~(1U << UCSZ02); UCSR0C &=~(1U << UCSZ01); UCSR0C &=~(1U << UCSZ00); break;
		case Char_6_Bits : UCSR0B &=~(1U << UCSZ02); UCSR0C &=~(1U << UCSZ01); UCSR0C |= (1U << UCSZ00); break;
		case Char_7_Bits : UCSR0B &=~(1U << UCSZ02); UCSR0C |= (1U << UCSZ01); UCSR0C &=~(1U << UCSZ00); break;
		case Char_8_Bits : UCSR0B &=~(1U << UCSZ02); UCSR0C |= (1U << UCSZ01); UCSR0C |= (1U << UCSZ00); break;
		case Char_9_Bits : UCSR0B |= (1U << UCSZ02); UCSR0C |= (1U << UCSZ01); UCSR0C |= (1U << UCSZ00); break;
		default			 : UCSR0B &=~(1U << UCSZ02); UCSR0C |= (1U << UCSZ01); UCSR0C |= (1U << UCSZ00); break;
	}
	
	switch(USART_Config.Parity_Mode){
		case No_Parity	: UCSR0C &=~(1U << UPM01); UCSR0C &=~(1U << UPM00); break;
		case Even_Parity: UCSR0C |= (1U << UPM01); UCSR0C &=~(1U << UPM00); break;
		case Odd_Parity	: UCSR0C |= (1U << UPM01); UCSR0C |= (1U << UPM00); break;
		default			: UCSR0C &=~(1U << UPM01); UCSR0C &=~(1U << UPM00); break;
	}
	
	switch(USART_Config.Stop_Bit){
		case One_Bit	: UCSR0C &=~(1U << USBS0); break;
		case Two_Bits	: UCSR0C |= (1U << USBS0); break;
		default			: UCSR0C &=~(1U << USBS0); break;
	}

	switch(USART_Config.Clock_Polirity){
		case TX_Falling_Edge	: UCSR0C |= (1U << UCPOL0); break;
		case TX_Rising_Edge		: UCSR0C &=~(1U << UCPOL0); break;
		default					: UCSR0C &=~(1U << UCPOL0); break;
	}
	
	switch(USART_Config.interrupt_Sel){
		case RX_Complete_Int_Enable		: UCSR0B |= (1U << RXCIE0); break;
		case TX_Complete_Int_Enable		: UCSR0B |= (1U << TXCIE0); break;
		case Data_Reg_Empty_Int_Enable	: UCSR0B |= (1U << UDRIE0); break;
		default							: UCSR0B &=~((1U << RXCIE0)|(1U << TXCIE0)|(1U << UDRIE0)); break;
	}
}

/********************************************************************************************
  Name:     USART_Rx_Error_Detection.
  Purpose:  Function receive the data of the USART and check if there is possible errors or not..
  Entry:    no parameters
  Exit:     ( Struct_Status Data_Status ) a STRUCT to check the following errors and returns the received Data.
						  1) Frame Error.
						  2) Data OverFlow Error.
						  3) Polarity Error.
********************************************************************************************/
Struct_Status USART_Rx_Error_Detection( void ){
	Struct_Status Data_Error;
	while (!(UCSR0A & (1U << RXC0)));		/*	Wait for the data to be received	*/	
	
	if(((UCSR0A & (1U << FE0)) == 0) && ((UCSR0A & (1U << DOR0)) == 0) && ((UCSR0A & (1U << PE0)) == 0))
		Data_Error.Detection = Correct;

	else if ((UCSR0A & (1U << FE0)) != 0)
		Data_Error.Detection = Frame_Error;

	else if ((UCSR0A & (1U << DOR0)) != 0)
		Data_Error.Detection = Data_OverFlow;

	else if ((UCSR0A & (1U << PE0)) != 0)
		Data_Error.Detection = Parity_Error;
	Data_Error.Data = UDR0;
	return Data_Error;
}

/********************************************************************************************
  Name:     USART_Receive.
  Purpose:  Function receive the data of the UDR0 register.
  Entry:    no parameters
  Exit:     ( return UDR0 ) Return Data in unsigned char.
********************************************************************************************/
u8 USART_Receive( void ){
	while (!(UCSR0A & (1U << RXC0)));	/*	Wait for the data to be received			*/
	return UDR0;						/*	Return the received data in the UDR0		*/
}

u8 USART_Receive_NoBlock( void ){
	if (UCSR0A & (1U << RXC0))			/*	Check for the data to be received without polling	*/
		return UDR0;					/*	Return the received data in the UDR0				*/
	else
		return 0;
}

/********************************************************************************************
  Name:     USART_Receive_9bit.
  Purpose:  Function receive the data of the UDR0 register if the frame structure is 9-bit.
  Entry:    no parameters
  Exit:     ( return Data_9bit; ) Return Data in u16.
********************************************************************************************/
u16 USART_Receive_9bit( void ){
	u16 Data_9bit = 0;
	while (!(UCSR0A & (1U << RXB80)));
	Data_9bit |= ((UCSR0B & (1U << RXB80)) << 8);
	Data_9bit |= UDR0;
	return Data_9bit;
}

/********************************************************************************************
  Name:     USART_Transmit.
  Purpose:  Function Transmit the data to the UDR0 register.
  Entry:    ( u8 Data ) The required data to be sent.
  Exit:     no parameters
********************************************************************************************/
void USART_Transmit( u8 Data ){
	while (!(UCSR0A & (1U << UDRE0)));	/*	Wait for the Buffer register to be Free.(1)	*/	
	UDR0 = Data;						/*	Send the Data to the Data register.			*/
}

/********************************************************************************************
  Name:     USART_Transmit_9Bit.
  Purpose:  Function Transmit the data to the UDR0 register if the frame structure is 9-bit.
  Entry:    ( u16 Data_9bit ) The required data to be sent.
  Exit:     no parameters
********************************************************************************************/
void USART_Transmit_9Bit( u16 Data_9bit ){
	while(!(UCSR0A & (1U << UDRE0)));
	UCSR0B |= ((Data_9bit & (1U << 8)) << TXB80);
	UDR0 = Data_9bit;
}

/********************************************************************************************
  Name:     USART_Transmit_String.
  Purpose:  Function Transmit the data in the form of array of char to the UDR0 register.
  Entry:    ( char* String ) The required data to be sent.
  Exit:     no parameters
********************************************************************************************/
void USART_Transmit_String( u8* String ){
	u8 Index = 0;
	while (String[Index] != '\0')
		USART_Transmit(String[Index++]);
}

/********************************************************************************************
  Name:     USART_Disable.
  Purpose:  Function used to disable the USART and override the USART pins to the default state.
  Entry:    no parameters
  Exit:     no parameters
********************************************************************************************/
void USART_Disable( void ){
	UCSR0B &=~((1 << TXEN0)|(1 << RXEN0));	/*	Disable Transmitter and Receiver.			*/
}