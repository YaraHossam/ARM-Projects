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
#include "SPI2_interface.h"
#include "STK_interface.h"

void main(void)
{
		RCC_voidInitSysClock();
		RCC_voidEnableClock(RCC_APB2 , 3); //GPIOB
		RCC_voidEnableClock(RCC_APB1 , 14 ); //SPI2


		//MGPIO_voidSetPinDirection(GPIOA ,1, 0b0010 ); //A0
		MGPIO_voidSetPinDirection(GPIOB ,14, INPUT_PUP_PDOWN); //MISO
		MGPIO_voidSetPinDirection(GPIOB ,13, OUTPUT_10MHZ_AFPP); //CLK
		MGPIO_voidSetPinDirection(GPIOB ,15, OUTPUT_10MHZ_AFPP); //MOSI
		MGPIO_voidSetPinDirection(GPIOB ,12, OUTPUT_10MHZ_AFPP);
		//init STK
		MSTK_voidInit();
		MSPI2_voidInit();

		u8 Local_u8Temp=0;
		//MSPI2_voidSendReceiveSynch(0x2A, &Local_u8Temp);
		while(1)
		{
			MSPI2_voidSendReceiveSynch(Local_u8Temp, &Local_u8Temp);
			MSTK_voidSetBusyWait(1000000);
			if(Local_u8Temp!=0)
			{
				asm("NOP");
			}

		}
}
