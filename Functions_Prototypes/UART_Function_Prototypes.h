
#include "../DataTypes/DataTypes.h"

u8	USART_Receive			( void );
u8 USART_Receive_NoBlock	( void );
u16 USART_Receive_9bit		( void );

void USART_Transmit			( u8 Send_Data );
void USART_Transmit_String	( u8* Array_String );
void USART_Transmit_9Bit	( u16 Data_9bit );

void USART_Disable			( void );
