
#ifndef IR_CONFIG_H_
#define IR_CONFIG_H_
#include "../Functions_Prototypes/IR_Functions_Prototypes.h"
#include <avr/io.h>

#define		Accident		1
#define		No_Accident		0

#define IRSensor1_Bit		0
#define IRSensor2_Bit		1
#define IRSensor3_Bit		2
#define IRSensor4_Bit		3

#define IRSensor1_DDR		DDRD
#define IRSensor2_DDR		DDRD
#define IRSensor3_DDR		DDRD
#define IRSensor4_DDR		DDRD

#define IRSensor1_PIN		PIND
#define IRSensor2_PIN		PIND
#define IRSensor3_PIN		PIND
#define IRSensor4_PIN		PIND

#define IRSensor1_PullDown	PORTD
#define IRSensor2_PullDown	PORTD
#define IRSensor3_PullDown	PORTD
#define IRSensor4_PullDown	PORTD


#endif /* IR_CONFIG_H_ */