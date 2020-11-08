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

#include "image.h"

void main(void)
{

	u8 hour=0;
	u8 min=0;
	u8 sec=0;

	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);
	RCC_voidEnableClock(RCC_APB2 , 12 ); //SPI

	MGPIO_voidSetPinDirection(GPIOA ,1, 0b0010 ); // A0
	MGPIO_voidSetPinDirection(GPIOA ,2, 0b0010); //RST
	MGPIO_voidSetPinDirection(GPIOA ,5, 0b1001); //CLK
	MGPIO_voidSetPinDirection(GPIOA ,7, 0b1001); //MOSI

	//init STK
	MSTK_voidInit();
	MSPI1_voidInit();
	HTFT_voidInit();

	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawString("DIGITAL",110,140,0b1111100000011111);
	HTFT_voidDrawString("CLOCK",64,120,0b1111100000011111);

	HTFT_voidDrawString("26 SEP 2020",113,50,0b1111111111100000);

	HTFT_voidDrawString("SATURDAY",95,20,0b0000000000011111);
	//HTFT_voidDraw2Dig(5,64,60,0x0000);

	HTFT_voidDraw2Dig(hour,100,80,0b0000011111100000);
	HTFT_voidDrawString(":",75 ,80 ,0b0000011111100000);
	HTFT_voidDraw2Dig(min,60,80,0b0000011111100000);
	HTFT_voidDrawString(":",35 ,80 ,0b0000011111100000);
	HTFT_voidDraw2Dig(sec,20,80,0b0000011111100000);



	while(1)
	{
		for (sec = 0 ; sec<60 ; sec++)
		{
			HTFT_voidClear2Dig(20,80,0x0000);
			HTFT_voidDraw2Dig(sec,20,80,0b0000011111100000);
			MSTK_voidSetBusyWait(1000000);
		}
		if(min<59)
		{
		min++;
		HTFT_voidClear2Dig(60,80,0x0000);
		HTFT_voidDraw2Dig(min,60,80,0b0000011111100000);
		}
		else
		{
			min=0;
			hour++;
			HTFT_voidClear2Dig(60,80,0x0000);
			HTFT_voidDraw2Dig(min,60,80,0b0000011111100000);
			HTFT_voidClear2Dig(100,80,0x0000);
			HTFT_voidDraw2Dig(hour,100,80,0b0000011111100000);
		}

	}
}

