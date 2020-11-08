/*
 * EXTI_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"
#include "EXTI_config.h"


static void (*EXTI_CallBack[16]) (void);

void MEXTI_voidInit(void)
{
	#if		 EXTI_LINE==EXTI_LINE0
			SET_BIT(EXTI->IMR,EXTI_LINE0);
	#elif 	EXTI_LINE==EXTI_LINE1
			SET_BIT(EXTI->IMR,EXTI_LINE1);
	#elif 	EXTI_LINE==EXTI_LINE2
			SET_BIT(EXTI->IMR,EXTI_LINE2);
	#elif 	EXTI_LINE==EXTI_LINE3
			SET_BIT(EXTI->IMR,EXTI_LINE3);
	#elif 	EXTI_LINE==EXTI_LINE4
			SET_BIT(EXTI->IMR,EXTI_LINE4);
	#elif 	EXTI_LINE==EXTI_LINE5
			SET_BIT(EXTI->IMR,EXTI_LINE5);
	#elif 	EXTI_LINE==EXTI_LINE6
			SET_BIT(EXTI->IMR,EXTI_LINE6);
	#elif 	EXTI_LINE==EXTI_LINE7
			SET_BIT(EXTI->IMR,EXTI_LINE7);
	#elif 	EXTI_LINE==EXTI_LINE8
			SET_BIT(EXTI->IMR,EXTI_LINE8);
	#elif 	EXTI_LINE==EXTI_LINE9
			SET_BIT(EXTI->IMR,EXTI_LINE9);
	#elif 	EXTI_LINE==EXTI_LINE10
			SET_BIT(EXTI->IMR,EXTI_LINE10);
	#elif 	EXTI_LINE==EXTI_LINE11
			SET_BIT(EXTI->IMR,EXTI_LINE11);
	#elif 	EXTI_LINE==EXTI_LINE12
			SET_BIT(EXTI->IMR,EXTI_LINE12);
	#elif 	EXTI_LINE==EXTI_LINE13
			SET_BIT(EXTI->IMR,EXTI_LINE13);
	#elif 	EXTI_LINE==EXTI_LINE14
			SET_BIT(EXTI->IMR,EXTI_LINE14);
	#elif 	EXTI_LINE==EXTI_LINE15
			SET_BIT(EXTI->IMR,EXTI_LINE14);
	#else
		#error ("wrong EXTI LINE !")
	#endif

	#if		 EXTI_SENSE_MODE == FALLING_EDGE
			SET_BIT(EXTI->FTSR,EXTI_LINE);
	#elif 	 EXTI_SENSE_MODE == RISING_EDGE
			SET_BIT(EXTI->RTSR,EXTI_LINE);
	#elif 	 EXTI_SENSE_MODE == ON_CHANGE
			SET_BIT(EXTI->FTSR,EXTI_LINE);
			SET_BIT(EXTI->RTSR,EXTI_LINE);
	#else
		#error ("wrong EXTI Sense Mode !")
	#endif
}
void MEXTI_voidSetSignalLatch(u8 copy_u8EXTILine , u8 copy_u8EXTISenseMode)
{
	switch(copy_u8EXTISenseMode)
	{
	case FALLING_EDGE:
		SET_BIT(EXTI->FTSR,copy_u8EXTILine);
		break;
	case RISING_EDGE:
		SET_BIT(EXTI->RTSR,copy_u8EXTILine);
		break;
	case ON_CHANGE:
		SET_BIT(EXTI->FTSR,copy_u8EXTILine);
		SET_BIT(EXTI->RTSR,copy_u8EXTILine);
		break;
	}
	SET_BIT(EXTI->IMR,copy_u8EXTILine);
}
void MEXTI_voidEnableEXTI(u8 copy_u8EXTILine)
{
	SET_BIT(EXTI->IMR,copy_u8EXTILine);
}
void MEXTI_voidDisableEXTI(u8 copy_u8EXTILine)
{
	CLR_BIT(EXTI->IMR,copy_u8EXTILine);
}
void MEXTI_voidSoftwareTrigger(u8 copy_u8EXTILine)
{
	SET_BIT(EXTI->IMR,copy_u8EXTILine);
	CLR_BIT(EXTI->PR,copy_u8EXTILine);
	SET_BIT(EXTI->SWIER,copy_u8EXTILine);
}
void MEXTI_voidSetCallBack(u8 copy_u8EXTILine,void (*ptr) (void))
{
	EXTI_CallBack[copy_u8EXTILine]=ptr;
}
void EXTI0_IRQHandler(void)
{
	EXTI_CallBack[0]();
	SET_BIT(EXTI->PR,EXTI_LINE0); //clear Pending bit
}
void EXTI1_IRQHandler(void)
{
	EXTI_CallBack[1]();
	SET_BIT(EXTI->PR,EXTI_LINE1); //clear Pending bit
}
