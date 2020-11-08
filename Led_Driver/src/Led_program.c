/********************************/
/* Author  : Yara Hossam        */
/* Date    : 17 AUG 2020        */
/* Version : V01                */
/********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "Led_interface"

void LedON (u8 copy_u8PORT , u8 copy_u8PIN)
{
	MGPIO_SpeedUp_voidSetPinValue(copy_u8PORT, copy_u8PIN , GPIO_HIGH);
}

void LedOFF (u8 copy_u8PORT , u8 copy_u8PIN)
{
	MGPIO_SpeedUp_voidSetPinValue(copy_u8PORT, copy_u8PIN , GPIO_LOW);
}


