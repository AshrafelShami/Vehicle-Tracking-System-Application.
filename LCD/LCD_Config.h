#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#include "../DataTypes/DataTypes.h"
#include "../Functions_Prototypes/LCD_Function_Prototypes.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>
#include <avr/io.h>

vu8* Data;	/*	Data Port	*/
vu8* Ctrl;	/*	Ctrl Port	*/

u8 E;		/*	Enable Pin	*/
u8 RW;		/*	R/W Pin		*/
u8 RS;		/*	RS Pin		*/

u8 D1;		/*	Data_1 Pin	*/
u8 D2;		/*	Data_1 Pin	*/
u8 D3;		/*	Data_1 Pin	*/
u8 D4;		/*	Data_1 Pin	*/


#endif /* LCD_CONFIG_H_ */