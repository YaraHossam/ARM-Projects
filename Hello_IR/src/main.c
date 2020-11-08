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
#include "EXTI_interface.h"
#include "NVIC_interface.h"
#include "STK_interface.h"

volatile u8 u8startFlag=0;
volatile u32 u32FrameData[50] = {0};
volatile u8 u8EdgeCount =0;
volatile u8 u8Data=0;

void voidplay(void)
{
	/*if (u8Data == 1)
	{
		MGPIO_voidSetPinValue(GPIOA,1,GPIO_HIGH);
	}
	else if (u8Data == 2)
	{
		MGPIO_voidSetPinValue(GPIOA,2,GPIO_HIGH);
	}
	else if (u8Data == 3)
	{
		MGPIO_voidSetPinValue(GPIOA,3,GPIO_HIGH);
	}
	else if (u8Data == 4)
	{
		MGPIO_voidSetPinValue(GPIOA,1,GPIO_LOW);
	}
	else if (u8Data == 5)
	{
		MGPIO_voidSetPinValue(GPIOA,2,GPIO_LOW);
	}
	else if (u8Data == 6)
	{
		MGPIO_voidSetPinValue(GPIOA,3,GPIO_LOW);
	}
	else if(u8Data == 69)
	{
		MGPIO_voidSetPinValue(GPIOA,PIN8,GPIO_HIGH);
	}
	else if(u8Data == 0)
	{
		MGPIO_voidSetPinValue(GPIOA,PIN8,GPIO_LOW);
	}
	else
	{
		MGPIO_voidSetPinValue(GPIOA,PIN8,GPIO_HIGH);
	}*/
	asm("NOP");
}

void voidTakeAction(void)
{
	//asm("NOP");
	u8Data=0;
	if(u32FrameData[0]>=10000 && u32FrameData[0]<=14000)
	{
	for(u8 i=0 ; i<8 ; i++)
	{
		if (u32FrameData[17+i]>=2000 && u32FrameData[17+i]<=2300)
		{
			SET_BIT(u8Data,i);
		}
		else
		{
			CLR_BIT(u8Data,i);
		}
	}
	}
	else
	{
		//Invalid Frame
	}
	voidplay();
	u8startFlag=0;
	u32FrameData[0]=0;
	u8EdgeCount =0;

}

void voidGetframe(void)
{
	//asm("NOP");
	if(u8startFlag==0)
	{
		//start timer
		MSTK_voidIntervalSingle(500000,voidTakeAction);
		u8startFlag=1;
	}
	else
	{
		u32FrameData[u8EdgeCount]=MSTK_u32GetElapsedTime();//first time 13500
		MSTK_voidIntervalSingle(500000,voidTakeAction);
		u8EdgeCount++;
	}

}

void main(void)
{
	//initialize
	RCC_voidInitSysClock();
	RCC_voidEnableClock(RCC_APB2,2);

	MGPIO_voidSetPinDirection(GPIOA,PIN0,INPUT_FLOATING);//out Rec
	MGPIO_voidSetPinDirection(GPIOA,PIN1,OUTPUT_2MHZ_PP);//Red
	MGPIO_voidSetPinDirection(GPIOA,PIN2,OUTPUT_2MHZ_PP);//Green
	MGPIO_voidSetPinDirection(GPIOA,PIN3,OUTPUT_2MHZ_PP);//Blue
	MGPIO_voidSetPinDirection(GPIOA,PIN8,OUTPUT_2MHZ_PP);

	//EXTI Init
	MEXTI_voidSetCallBack(0,voidGetframe);
	MEXTI_voidInit();

	//NVIC init
	MNVIC_voidInit();
	MNVIC_voidEnableInterrupt(6);

	//STK init
	MSTK_voidInit();//enable systick on AHB/8

	while(1)
	{

	}


}
