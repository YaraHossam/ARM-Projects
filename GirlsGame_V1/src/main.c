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
#include "STK_interface.h"
#include "SPI_interface.h"

#include "TFT_interface.h"

#include "GirlsGame.h"

void main(void)
{
		RCC_voidInitSysClock();
		RCC_voidEnableClock(RCC_APB2 , 2); //GPIOA
		//RCC_voidEnableClock(RCC_APB2 , 3);
		RCC_voidEnableClock(RCC_APB2 , 12 ); //SPI

		MGPIO_voidSetPinDirection(UP,INPUT_PUP_PDOWN );
		MGPIO_voidSetPinValue(UP, GPIO_HIGH);
		MGPIO_voidSetPinDirection(DOWN,INPUT_PUP_PDOWN );
		MGPIO_voidSetPinValue(DOWN, GPIO_HIGH);
		MGPIO_voidSetPinDirection(LEFT,INPUT_PUP_PDOWN );
		MGPIO_voidSetPinValue(LEFT, GPIO_HIGH);
		MGPIO_voidSetPinDirection(RIGHT,INPUT_PUP_PDOWN );
		MGPIO_voidSetPinValue(RIGHT, GPIO_HIGH);
		MGPIO_voidSetPinDirection(CHOOSE,INPUT_PUP_PDOWN );
		MGPIO_voidSetPinValue(CHOOSE, GPIO_HIGH);
//		MGPIO_voidSetPinDirection(SAVE_SQR,INPUT_PUP_PDOWN );
//		MGPIO_voidSetPinValue(SAVE_SQR, GPIO_HIGH);

		MGPIO_voidSetPinDirection(GPIOA ,1, 0b0010 ); // A0
		MGPIO_voidSetPinDirection(GPIOA ,2, 0b0010); //RST
		MGPIO_voidSetPinDirection(GPIOA ,5, 0b1001); //CLK
		MGPIO_voidSetPinDirection(GPIOA ,7, 0b1001); //MOSI

		//init STK
		MSTK_voidInit();
		MSPI1_voidInit();
		HTFT_voidInit();

		Girls_Game();


		while(1)
		{

		}
}
