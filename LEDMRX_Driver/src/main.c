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
#include "LEDMRX_interface.h"

u8 DataArray[8]={3, 6, 12, 248, 12, 6, 3, 0};

void main(void)
{
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);
	RCC_voidEnableClock(RCC_APB2,3);

	MSTK_voidInit();
	HLEDMRX_voidInit();

	HLEDMRX_voidDisplay(DataArray);

}

