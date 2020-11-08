/********************************/
/* Author  : Yara Hossam        */
/* Date    : 16 AUG 2020        */
/* Version : V01                */
/********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "SevenSegment_interface.h"
#include "SevenSegment_config.h"
#include "SevenSegment_private.h"

void SevenSegment_voidIntial(void)
{
	MGPIO_voidSetPinDirection(SEVEN_SEGMENT_PORT , SS_A , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(SEVEN_SEGMENT_PORT , SS_B , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(SEVEN_SEGMENT_PORT , SS_C , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(SEVEN_SEGMENT_PORT , SS_D , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(SEVEN_SEGMENT_PORT , SS_E , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(SEVEN_SEGMENT_PORT , SS_F , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(SEVEN_SEGMENT_PORT , SS_G , OUTPUT_10MHZ_PP);
	
}

void SevenSegment_voidDisplay(u8 Copy_u8TypeOfSS , u8 Copy_u8Number)
{
	switch(Copy_u8TypeOfSS)
	{
		case SS_COMMEN_ANODE:
							SS_voidAnodeDisplay(Copy_u8Number);
							break;
		case SS_COMMEN_CATHODE:
							SS_voidCathodeDisplay(Copy_u8Number);
							break;
	}
}

void SS_voidCathodeDisplay(u8 Copy_u8Number)
{
	switch(Copy_u8Number)
	{
		case 0:
			//on ABCDEF  off G
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 1:
			//on BC  off ADEFG
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 2:
			//on ABGED  off CF
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 3:
			//on ABCDG  off FE
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 4:
			//on BCFG  off ADE
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 5:
			//on AFGCD  off BE
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 6:
			//on AFGEDC  off B
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 7:
			//on ABC  off FGED
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 8:
			//on ABCDEFG  off 
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 9:
			//on ABCDFG  off E
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
	}
	
}

void SS_voidAnodeDisplay(u8 Copy_u8Number)
{
	switch(Copy_u8Number)
	{
		case 0:
			//oFF ABCDEF  oN G
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 1:
			//oFF BC  oN ADEFG
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 2:
			//oFF ABGED  oN CF
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 3:
			//oFF ABCDG  oN FE
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 4:
			//oFF BCFG  oN ADE
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 5:
			//oFF AFGCD  oN BE
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 6:
			//oFF AFGEDC  oN B
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 7:
			//oFF ABC  oN FGED
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_HIGH);
			break;
		case 8:
			//oFF ABCDEFG  oN 
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
		case 9:
			//oFF ABCDFG  oN E
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_A , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_B , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_C , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_D , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_E , GPIO_HIGH);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_F , GPIO_LOW);
			MGPIO_voidSetPinValue(SEVEN_SEGMENT_PORT , SS_G , GPIO_LOW);
			break;
	}
	
}






