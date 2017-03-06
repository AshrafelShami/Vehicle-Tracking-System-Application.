
#include "../DataTypes/DataTypes.h"
	
void LCD_Init		( vu8* D_Port, vu8* C_Port, u8 E_PIN, u8 RW_PIN, u8 RS_PIN, u8 D1_PIN, u8 D2_PIN, u8 D3_PIN, u8 D4_PIN);
void LCD_Command	( u8 Command );
void LCD_Char		( u8 Charcter );
void LCD_Print		( u8 Pos_X, u8 Pos_Y, u8 * word );
void LCD_GOTO		( u8 GOTO_X, u8 GOTO_Y );
void LCD_Latch_Enable	( void );
void LCD_Sync_Data_Pins ( u8 Value );
void LCD_BasyFlag_Check	( void );
