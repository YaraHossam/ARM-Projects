/********************************/
/* Author  : Yara Hossam        */
/* Date    : 24 AUG 2020        */
/* Version : V01                */
/********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "SysTick_interface.h"
#include "SysTick_private.h"
#include "SysTick_config.h"

void SysTick_voidInit(void)
{
	STK_CTRL = 0x00000003; // Enable Counter , Enable Interrupt , Selects the clock source AHB/8
}

void SysTick_voidMS(u32 copy_u32ValueMS)
{
	STK_LOAD = copy_u32ValueMS*1000;
}

u8 SysTick_u8ReadFlag(void)
{
	return GET_BIT(STK_CTRL,16);
}
