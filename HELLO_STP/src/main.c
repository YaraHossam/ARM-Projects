/*
 * maine.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"

#include "STP_interface.h"


void main(void)
{
	//RCC
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);

	MGPIO_voidSetPinDirection(GPIOA,0,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA,1,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(GPIOA,2,OUTPUT_2MHZ_PP);

	MSTK_voidInit();


	u8 i = 0;
	HSTP_voidSendSynchronus(0xAA);

	while(1)
	{
//		for (i=0 ; i<8 ; i++)
//		{
//			HSTP_voidSendSynchronus(1<<i);
//			MSTK_voidSetBusyWait(300000);
//		}
	}


}
