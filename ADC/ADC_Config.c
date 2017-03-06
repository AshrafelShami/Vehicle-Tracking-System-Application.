#include "ADC_Config.h"

/********************************************************************************************
  Name:     ADC_Init.
  Purpose:  Initialize, all possible ADC registers for ATmega32 and Enables it.
  Entry:    (Struct_ADC) a STRUCT that setup the following.
							1) Voltage reference.
							2) Result Adjustment in ADCL and ADCH registers.
							3) Prescaler, The ADC operates at freq from 50kHz ~ 250kHz.
							4) Trigger settings if it is needed.
							5) Adjustment of the trigger source.
							6) Interrupt, if needed. 
  Exit:     no parameters
********************************************************************************************/
void ADC_Init ( Struct_ADC ADC_Config){

	ADCSRA |= (1 << ADEN);					/*	Enable the ADC	*/

	switch(ADC_Config.Vref_Ref_Sel){
		case Vref_Internal_Vref_OFF : ADMUX &=~(1 << REFS1); ADMUX &=~(1 << REFS0); break;
		case Vref_VCC_With_ext_cap  : ADMUX &=~(1 << REFS1); ADMUX |= (1 << REFS0); break;
		case Vref_2_56_Volt			: ADMUX |= (1 << REFS1); ADMUX |= (1 << REFS0); break;
		default						: ADMUX &=~(1 << REFS1); ADMUX &=~(1 << REFS0); break;
	}
	
	switch(ADC_Config.Result_Adjust){
		case Left_Adjustment  : ADMUX |= (1 << ADLAR); break;
		case Right_Adjustment : ADMUX &=~(1 << ADLAR); break;
		default				  : ADMUX &=~(1 << ADLAR); break;
	}
	
	switch(ADC_Config.Prescaler_Sel){
		case Division_Factor_2   : ADCSRA &=~ (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		case Division_Factor_4   : ADCSRA &=~ (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
		case Division_Factor_8   : ADCSRA &=~ (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		case Division_Factor_16  : ADCSRA |=  (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
		case Division_Factor_32  : ADCSRA |=  (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		case Division_Factor_64  : ADCSRA |=  (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
		case Division_Factor_128 : ADCSRA |=  (1 << ADPS2); ADCSRA |=  (1 << ADPS1); ADCSRA |=  (1 << ADPS0); break;
		default					 : ADCSRA &=~ (1 << ADPS2); ADCSRA &=~ (1 << ADPS1); ADCSRA &=~ (1 << ADPS0); break;
	}
	
	switch(ADC_Config.Running_Mode){
		case Enable  : ADCSRA |= (1 << ADFR); break;
		case Disable : ADCSRA &=~(1 << ADFR); break;
		default		 : ADCSRA &=~(1 << ADFR); break;
	}
	
	switch(ADC_Config.Interrupt_Sel){
		case Interrupt_Disable	: ADCSRA &=~(1 << ADIE); break;
		case Interrupt_Enable	: ADCSRA |= (1 << ADIE); break;
		default					: ADCSRA &=~(1 << ADIE); break;
	}
}

/********************************************************************************************
  Name:     ADC_Scan.
  Purpose:  Setup the ADC channel and starts the conversion.
  Entry:    (Channel_Select) The Channel number that you are gonna work with (0 ~ 7).
  Exit:     (u68 ADC) Returns the value of the ADC conversion of the two registers.
********************************************************************************************/
u16 ADC_Scan ( u8 Channel_Select ){
	Channel_Select &= 0x07;
	ADMUX |= Channel_Select;				/*	Select ADC Channel					*/
	
	ADCSRA |= (1 << ADSC);					/*	Start the Convention				*/
	
	while (ADCSRA & (1 << ADSC));			/*	Wait for the conversion to complete
												And ADSC bit will be LOW		    */
	return ADC;
}
