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
#include "UART_interface.h"


void main(void)
{

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);
	RCC_voidEnableClock(RCC_APB2,14);//Enable UART

	MGPIO_voidSetPinDirection(GPIOA, 9 ,OUTPUT_50MHZ_PP );//TX OUT
	MGPIO_voidSetPinDirection(GPIOA, 10 ,INPUT_FLOATING );//RX IN

	MGPIO_voidSetPinDirection(GPIOA, 0 ,OUTPUT_2MHZ_PP );

	MUSART_voidInit();
	u8 x;
	while(1)
	{
		MUSART_voidTransmit("97");
		x=MUSART_u8Receive();
		if(x=='5')
		{
			MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_HIGH);
		}
		else
		{
			MGPIO_voidSetPinValue(GPIOA, 0 , GPIO_LOW);
		}
	}

}

