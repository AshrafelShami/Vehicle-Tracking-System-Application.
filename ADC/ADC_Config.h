
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#include <avr/io.h>
#include "../DataTypes/DataTypes.h"
#include "../Functions_Prototypes/ADC_Function_Prototypes.h"

typedef enum{
	Vref_Internal_Vref_OFF,
	Vref_VCC_With_ext_cap ,
	Vref_2_56_Volt
	}Vref;
	
typedef enum{
	Right_Adjustment,
	Left_Adjustment	,
	}Adjust;
	
typedef enum{
	Division_Factor_2  ,
	Division_Factor_4  ,
	Division_Factor_8  ,
	Division_Factor_16 ,
	Division_Factor_32 ,
	Division_Factor_64 ,
	Division_Factor_128
	}Prescaler;
	
typedef enum{
	Enable,
	Disable
	}Free_Running_Mode;
	
typedef enum{
	Interrupt_Disable,
	Interrupt_Enable
	}Interrupt;

typedef struct{
		Vref			Vref_Ref_Sel	;
		Adjust			Result_Adjust	;
		Prescaler		Prescaler_Sel	;
		Free_Running_Mode	Running_Mode	;
		Interrupt		Interrupt_Sel	;
	}Struct_ADC;
	
void ADC_Init ( Struct_ADC );

#endif /* ADC_CONFIG_H_ */
