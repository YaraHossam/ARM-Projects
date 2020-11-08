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

void main (void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);

	MGPIO_voidSetPinDirection(GPIOA , PIN0 , OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN1 , OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA , PIN2 , OUTPUT_2MHZ_PP);

	//Initialize NVIC
	MNVIC_voidInit();

	MNVIC_voidSetPriority(6 , 0b01000000);  //EXTI0 Group1 sub0
	MNVIC_voidSetPriority(7 , 0b00110000); //EXTI1 Group0 sub3

	//enable Exti0 interrupt
	MNVIC_voidEnableInterrupt(6); //enable Exti0 interrupt
	MNVIC_voidEnableInterrupt(7); //enable Exti1 interrupt

	MNVIC_voidSetPendingFlag(6);

	while(1)
	{

	}
}

void EXTI0_IRQHandler(void)
{
	MGPIO_voidSetPinValue(GPIOA, PIN0 , GPIO_HIGH);
	MNVIC_voidSetPendingFlag(7);
	MGPIO_voidSetPinValue(GPIOA, PIN1 , GPIO_HIGH);
}
void EXTI1_IRQHandler(void)
{
	MGPIO_voidSetPinValue(GPIOA, PIN2 , GPIO_HIGH);
}
