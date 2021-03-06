/*
 * main.c
 *
 *  Created on: ??�/??�/????
 *      Author: Yara
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "LEDMRX_interface.h"

u8 DataArray[]={1, 2, 4, 248, 4, 2, 1, 0, 0, 252, 18, 17, 17, 18, 252, 0, 0, 255, 17, 49, 81, 159, 0, 0, 252, 18, 17, 17, 18, 252,0,0,0,0,0,0,0,0};
volatile u8 * data=DataArray;
u8 i = 1;

void change (void)
{
	if(i<29)
	{
		i++;

	}
	else
	{
		i=0;
	}
	data = DataArray + i;
}
void ledon (void)
{
	if(i==0)
	{
		MGPIO_voidSetPinValue(GPIOA,PIN8 , GPIO_LOW);
		i=1;
	}
	else
	{
		MGPIO_voidSetPinValue(GPIOA,PIN8 , GPIO_HIGH);
				i=0;
	}
}
void main(void)
{

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);
	RCC_voidEnableClock(RCC_APB2,3);

	MSTK_voidInit();
	HLEDMRX_voidInit();
	MGPIO_voidSetPinDirection(GPIOA,PIN8,OUTPUT_2MHZ_PP);

	MSTK_voidIntervalPeriodic(100000 ,ledon);

	while(1)
	{
		for (u32 k=0 ; k<20 ; k++)
		{

			HLEDMRX_voidDisplay(data);
		}
		if(i<29)
			{
				i++;

			}
			else
			{
				i=0;
			}
			data = DataArray + i;

	}


}
