#include "toStr_Config.h"

void toStr( u32 num, u8* str, u8 displaySize){
	u8 i = 0;
	for(i = 0 ; i < displaySize ; i++)
	str[i]=((num/(long)pow(10,(displaySize -i -1)))-(num/(long)pow(10,(displaySize -i)))*10)+'0';
}
