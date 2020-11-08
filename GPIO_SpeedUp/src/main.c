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

	/* enable peripheral 2 on APB2 bus (GPIOA)*/
	RCC_voidEnableClock(RCC_APB2 , 2);
	/* enable peripheral 3 on APB2 bus (GPIOB)*/
	RCC_voidEnableClock(RCC_APB2 , 3);
	/* enable peripheral 4 on APB2 bus (GPIOC)*/
	RCC_voidEnableClock(RCC_APB2 , 4);

	//direction
	MGPIO_voidSetPinDirection(GPIOA , PIN0 , OUTPUT_10MHZ_PP );
	MGPIO_voidSetPinDirection(GPIOB , PIN0 , OUTPUT_10MHZ_PP );

	MGPIO_SpeedUp_voidSetPinValue(GPIOA, PIN0 , GPIO_HIGH);
	MGPIO_SpeedUp_voidSetPinValue(GPIOB, PIN0 , GPIO_HIGH);
	while(1)
	{

	}


}
