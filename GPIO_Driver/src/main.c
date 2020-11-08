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

void main(void)
{
	/* Init clock system*/
	RCC_voidInitSysClock();

	//Enable GPIO A, B, C
	/* enable peripheral 2 on APB2 bus (GPIOA)*/
	RCC_voidEnableClock(RCC_APB2 , 2);
	/* enable peripheral 3 on APB2 bus (GPIOB)*/
	//RCC_voidEnableClock(RCC_APB2 , 3);
	/* enable peripheral 4 on APB2 bus (GPIOC)*/
	//RCC_voidEnableClock(RCC_APB2 , 4);

	/* PINA0 output push pull 10MHZ */
	MGPIO_voidSetPinDirection(GPIOA , PIN0 , OUTPUT_10MHZ_PP );
	MGPIO_voidSetPinDirection(GPIOA , PIN1 , OUTPUT_10MHZ_PP );
	MGPIO_voidSetPinDirection(GPIOA , PIN2 , OUTPUT_10MHZ_PP );
	MGPIO_voidSetPinDirection(GPIOA , PIN3 , OUTPUT_10MHZ_PP );
	MGPIO_voidSetPinDirection(GPIOA , PIN4 , OUTPUT_10MHZ_PP );
	MGPIO_voidSetPinDirection(GPIOA , PIN5 , OUTPUT_10MHZ_PP );
	MGPIO_voidSetPinDirection(GPIOA , PIN6 , OUTPUT_10MHZ_PP );



	while(1)
	{
//		MGPIO_voidSetPinValue(GPIOA, PIN0, GPIO_HIGH);
//		MGPIO_voidSetPinValue(GPIOA, PIN1, GPIO_HIGH);
//		MGPIO_voidSetPinValue(GPIOA, PIN2, GPIO_HIGH);
//		MGPIO_voidSetPinValue(GPIOA, PIN3, GPIO_HIGH);
//		MGPIO_voidSetPinValue(GPIOA, PIN4, GPIO_HIGH);
		MGPIO_voidSetPinValue(GPIOA, PIN5, GPIO_HIGH);
//		MGPIO_voidSetPinValue(GPIOA, PIN6, GPIO_HIGH);
//

	}
}
