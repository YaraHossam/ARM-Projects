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
#include "NVIC_interface.h"
#include "SysTick_interface.h"

volatile u8 count=0;
volatile u8 CPP=0;

void main (void)
{

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);

	MGPIO_voidSetPinDirection(GPIOA , PIN0 , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN1 , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN2 , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN3 , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN4 , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN5 , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN6 , OUTPUT_10MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN7 , OUTPUT_10MHZ_PP);

	SysTick_voidMS(200);
	SysTick_voidInit();

	while(1)
	{
		SysTick_voidMS(200);
		//ping pong 4 times
		for(int i =0 ; i <4 ; i++)
		{
			for(int j = 0 ; j < 8 ; j ++)
			{
				count=0;
				PingPong(j);
				//delay
				while(count == 0)
				{

				}
			}
			for(int j = 7 ; j >= 0 ; j --)
			{
				count=0;
				PingPong(j);
				//delay
				while(count == 0)
				{

				}
			}
		}

		//flower 4 times
		for(int i =0 ; i <4 ; i++)
		{
			for(int j = 0 ; j < 4 ; j ++)
			{
				count=0;
				flower(j);
				//delay
				while(count == 0)
				{

				}
			}
			for(int j = 3 ; j >= 0 ; j --)
			{
				count=0;
				flower(j);
				//delay
				while(count == 0)
				{

				}
			}
		}
		//flashing
		SysTick_voidMS(500);
		SysTick_voidInit();
		for(int i =0 ;i<8 ; i++)
		{
			//on
			count=0;
			flashing(1);
			//delay
			while(count == 0)
			{

			}
			//off
			count=0;
			flashing(0);
			//delay
			while(count == 0)
			{

			}
		}

	}
}

void PingPong(u8 copy_u8PinHigh)
{
	for(int i = 0 ; i < 8 ; i ++)
	{
		if(i == copy_u8PinHigh)
		{
			MGPIO_voidSetPinValue(GPIOA, i , GPIO_HIGH);
		}
		else
		{
			MGPIO_voidSetPinValue(GPIOA, i , GPIO_LOW);
		}
	}

}

void flower(u8 copy_u8PinHigh)
{
	switch(copy_u8PinHigh)
		{
			case 0 :
				MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 1 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 2 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 3 , GPIO_HIGH);
				MGPIO_voidSetPinValue(GPIOA, 4 , GPIO_HIGH);
				MGPIO_voidSetPinValue(GPIOA, 5 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 6 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 7 , GPIO_LOW);
						break;
			case 1 :
				MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 1 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 2 , GPIO_HIGH);
				MGPIO_voidSetPinValue(GPIOA, 3 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 4 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 5 , GPIO_HIGH);
				MGPIO_voidSetPinValue(GPIOA, 6 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 7 , GPIO_LOW);
						break;
			case 2 :
				MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 1 , GPIO_HIGH);
				MGPIO_voidSetPinValue(GPIOA, 2 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 3 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 4 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 5 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 6 , GPIO_HIGH);
				MGPIO_voidSetPinValue(GPIOA, 7 , GPIO_LOW);
						break;
			case 3 :
				MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_HIGH);
				MGPIO_voidSetPinValue(GPIOA, 1 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 2 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 3 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 4 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 5 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 6 , GPIO_LOW);
				MGPIO_voidSetPinValue(GPIOA, 7 , GPIO_HIGH);
						break;
			default : break;
		}


}

void flashing(u8 copy_onoff)
{
	switch(copy_onoff)
	{
	case 0 :
		MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_LOW);
		MGPIO_voidSetPinValue(GPIOA, 1 , GPIO_LOW);
	    MGPIO_voidSetPinValue(GPIOA, 2 , GPIO_LOW);
		MGPIO_voidSetPinValue(GPIOA, 3 , GPIO_LOW);
		MGPIO_voidSetPinValue(GPIOA, 4 , GPIO_LOW);
		MGPIO_voidSetPinValue(GPIOA, 5 , GPIO_LOW);
		MGPIO_voidSetPinValue(GPIOA, 6 , GPIO_LOW);
		MGPIO_voidSetPinValue(GPIOA, 7 , GPIO_LOW);
		break;
	case 1:
		MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIOA, 1 , GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIOA, 2 , GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIOA, 3 , GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIOA, 4 , GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIOA, 5 , GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIOA, 6 , GPIO_HIGH);
	    MGPIO_voidSetPinValue(GPIOA, 7 , GPIO_HIGH);
	    break;
	}
}


void SysTick_Handler(void)
{

	count=1;

}
