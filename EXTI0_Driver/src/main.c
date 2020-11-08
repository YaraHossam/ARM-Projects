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
#include "STK_interface.h"

#include "EXTI_interface.h"

void fun(void)
{
	//pin A2 High
	MGPIO_voidSetPinValue(GPIOA,PIN2,GPIO_HIGH);
	//delay
	MSTK_voidSetBusyWait(1000000);
	//pin A2 Low
	MGPIO_voidSetPinValue(GPIOA,PIN2,GPIO_LOW);
	//delay
	MSTK_voidSetBusyWait(1000000);
}

void main(void)
{
	//RCC
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2 , 2);//GPIOA
	RCC_voidEnableClock(RCC_APB2 , 0);


	MEXTI_voidSetCallBack(0,fun);

	MNVIC_voidInit();
	MNVIC_voidEnableInterrupt(6);//EXTI0

}
