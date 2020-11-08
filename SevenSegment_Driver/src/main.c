/*
 * main.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "SevenSegment_interface.h"
#include "SevenSegment_config.h"
#include "SevenSegment_private.h"

void delay(void)
{
	for(int i=0 ; i<500 ; i++ )
			{
				for(int k=0 ; k<500 ; k++ )
				{
					asm("NOP");
				}
			}
}

void main(void)
{
	/* Init clock system*/
		RCC_voidInitSysClock();
		//Enable GPIO A, B, C
	/* enable peripheral 2 on APB2 bus (GPIOA)*/
		RCC_voidEnableClock(RCC_APB2 , 2);

		//intial SevenSgment
		SevenSegment_voidIntial();

		while(1)
		{
			for(int n=0 ; n<10 ; n++)
			{
				SevenSegment_voidDisplay(SS_COMMEN_CATHODE , n);
				delay();
				delay();
				delay();
				delay();
			}
		}
}
