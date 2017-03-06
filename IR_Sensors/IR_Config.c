#include "IR_Config.h"

void IR_Sensors_Init( void ){
	IRSensor1_DDR &=~(1 << IRSensor1_Bit);
	IRSensor2_DDR &=~(1 << IRSensor2_Bit);
	IRSensor3_DDR &=~(1 << IRSensor3_Bit);
	IRSensor4_DDR &=~(1 << IRSensor4_Bit);
	
	IRSensor1_PullDown &=~(1 << IRSensor1_Bit);
	IRSensor2_PullDown &=~(1 << IRSensor2_Bit);
	IRSensor3_PullDown &=~(1 << IRSensor3_Bit);
	IRSensor4_PullDown &=~(1 << IRSensor4_Bit);
}

u8 Accident_Check ( void ){
	if(!((IRSensor1_PIN & (1U << IRSensor1_Bit)) && (IRSensor2_PIN & (1U << IRSensor2_Bit))
	 && (IRSensor3_PIN & (1U << IRSensor3_Bit)) && (IRSensor4_PIN & (1U << IRSensor4_Bit))))
		return No_Accident;
	else
		return Accident;
}