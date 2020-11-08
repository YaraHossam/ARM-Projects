/********************************/
/* Author  : Yara Hossam        */
/* Date    : 12 AUG 2020        */
/* Version : V01                */
/********************************/
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "GPIO_config.h"
#include "GPIO_private.h"

void MGPIO_voidSetPinDirection(u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Mode)
{
	switch(copy_u8PORT)
	{
		case GPIOA :
					if(copy_u8PIN <= 7)
					{
						GPIOA_CRL &= ~((0b1111) << (copy_u8PIN*4));
						GPIOA_CRL |= ((copy_u8Mode) << (copy_u8PIN*4));
					}
					else if(copy_u8PIN <= 15)
					{
						GPIOA_CRH &= ~((0b1111) << ((copy_u8PIN-8)*4));
						GPIOA_CRH |= ((copy_u8Mode) << ((copy_u8PIN-8)*4));
					}
					break;
		case GPIOB :
					if(copy_u8PIN <= 7)
					{
						GPIOB_CRL &= ~((0b1111) << (copy_u8PIN*4));
						GPIOB_CRL |= ((copy_u8Mode) << (copy_u8PIN*4));
					}
					else if(copy_u8PIN <= 15)
					{
						GPIOB_CRH &= ~((0b1111) << ((copy_u8PIN-8)*4));
						GPIOB_CRH |= ((copy_u8Mode) << ((copy_u8PIN-8)*4));
					}
					break;
		case GPIOC :
					if(copy_u8PIN <= 7)
					{
						GPIOC_CRL &= ~((0b1111) << (copy_u8PIN*4));
						GPIOC_CRL |= ((copy_u8Mode) << (copy_u8PIN*4));
					}
					else if(copy_u8PIN <= 15)
					{
						GPIOC_CRH &= ~((0b1111) << ((copy_u8PIN-8)*4));
						GPIOC_CRH |= ((copy_u8Mode) << ((copy_u8PIN-8)*4));
					}
					break;
		default : break;
	}
}

void MGPIO_SpeedUp_voidSetPinValue(u8 copy_u8PORT , u8 copy_u8PIN , u8 copy_u8Value)
{
	switch(copy_u8PORT)
	{
		case GPIOA :
					if(copy_u8Value == GPIO_HIGH)
					{
						GPIOA_BSR=(1<<copy_u8PIN);
					}
					else if(copy_u8Value == GPIO_LOW)
					{
						GPIOA_BRR=(1<<copy_u8PIN);
					}
					break;
		case GPIOB :
					if(copy_u8Value == GPIO_HIGH)
					{
						GPIOB_BSR=(1<<copy_u8PIN);
					}
					else if(copy_u8Value == GPIO_LOW)
					{
						GPIOB_BRR=(1<<copy_u8PIN);
					}
					break;
		case GPIOC :
					if(copy_u8Value == GPIO_HIGH)
					{
						GPIOC_BSR=(1<<copy_u8PIN);
					}
					else if(copy_u8Value == GPIO_LOW)
					{
						GPIOC_BRR=(1<<copy_u8PIN);
					}
					break;
		default : break;
	}
}

void MGPIO_voidSetPortValue(u8 copy_u8PORT , u16 copy_u16Value)
{
	switch(copy_u8PORT)
		{
			case GPIOA :
						GPIOA_ODR = copy_u16Value;
						break;
			case GPIOB :
						GPIOB_ODR = copy_u16Value;
						break;
			case GPIOC :
						GPIOC_ODR = copy_u16Value;
						break;
			default : break;
		}
}

u8 MGPIO_u8GetPinValue(u8 copy_u8PORT , u8 copy_u8PIN )
{
	u8 LOC_u8Res =0;
	switch(copy_u8PORT)
	{
		case GPIOA :
					LOC_u8Res=GET_BIT(GPIOA_IDR,copy_u8PIN);
					break;
		case GPIOB :
					LOC_u8Res=GET_BIT(GPIOB_IDR,copy_u8PIN);
					break;
		case GPIOC :
					LOC_u8Res=GET_BIT(GPIOC_IDR,copy_u8PIN);
					break;
		default : break;
	}
	return LOC_u8Res;
}
