/*
 * STK_program.c
 *
 *  Created on: ??�/??�/????
 *      Author: Yara
 */

/********************************/
/* Author  : Yara Hossam        */
/* Date    : 1  Sep 2020        */
/* Version : V01                */
/********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "STK_interface.h"
#include "STK_private.h"
#include "STK_config.h"

void (*callBack) (void);

/* Define Variable for interval mode */
static u8 MSTK_u8ModeOfInterval;

//chosses clock
void MSTK_voidInit(void)
{
	#if STK_CLKSOURCE==AHB_8
		STK_CTRL=0x00000000;
	#elif STK_CLKSOURCE==AHB
		STK_CTRL=0x00000004;
	#endif
}

void MSTK_voidSetBusyWait( u32 copy_u32Ticks)
{
	STK_LOAD=copy_u32Ticks;
	SET_BIT(STK_CTRL,0); //Enable SysTick
	while(GET_BIT(STK_CTRL,16)==0);
	//stop timer
		CLR_BIT(STK_CTRL,0); //Disable SysTick
		CLR_BIT(STK_CTRL,1); //Disable Interrupt
		STK_LOAD=0;
		STK_VAL=0;
}

void MSTK_voidIntervalSingle(u32 copy_u32Ticks , void (*copy_ptr) (void))
{	CLR_BIT(STK_CTRL,0);
	STK_VAL=0;

	/* Load ticks to load register */
		STK_LOAD = copy_u32Ticks;

		/* Start Timer */
		SET_BIT(STK_CTRL, 0);

		/* Save CallBack */
		callBack = copy_ptr;

		/* Set Mode to Single */
		MSTK_u8ModeOfInterval = MSTK_SINGLE_INTERVAL;

		/* Enable STK Interrupt */
		SET_BIT(STK_CTRL, 1);
}
void MSTK_voidIntervalPeriodic(u32 copy_u32Ticks , void (*copy_ptr) (void))
{
	STK_LOAD=copy_u32Ticks;
	callBack=copy_ptr;
	SET_BIT(STK_CTRL,0); //Enable SysTick
	SET_BIT(STK_CTRL,1); //Enable Interrupt

}
void MSTK_voidStopTimer(void)
{
	CLR_BIT(STK_CTRL,0); //Disable SysTick
	CLR_BIT(STK_CTRL,1); //Disable Interrupt
	STK_LOAD=0;
	STK_VAL=0;
}
// load-value
u32 MSTK_u32GetElapsedTime(void)
{
	return STK_LOAD-STK_VAL;
}
//value
u32 MSTK_u32GetRemaining(void)
{
	return STK_VAL;
}
void SysTick_Handler(void)
{
	u8 Local_u8Temporary;

		if (MSTK_u8ModeOfInterval == MSTK_SINGLE_INTERVAL)
		{
			/* Disable STK Interrupt */
			CLR_BIT(STK_CTRL, 1);

			/* Stop Timer */
			SET_BIT(STK_CTRL, 0);
			STK_LOAD = 0;
			STK_VAL  = 0;
		}

		/* Callback notification */
		callBack();

		/* Clear interrupt flag */
		Local_u8Temporary = GET_BIT(STK_CTRL,16);
}
