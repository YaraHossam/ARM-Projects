/********************************/
/* Author  : Yara Hossam        */
/* Date    : 1  Sep 2020        */
/* Version : V01                */
/********************************/

#ifndef		STK_PRIVATE_H
#define 	STK_PRIVATE_H

#define AHB_8		0
#define AHB			1

#define SysTick_BASE_ADDRESS		0xE000E010

#define STK_CTRL		*((volatile u32*)(SysTick_BASE_ADDRESS))
#define STK_LOAD		*((volatile u32*)(SysTick_BASE_ADDRESS+0x04))
#define STK_VAL			*((volatile u32*)(SysTick_BASE_ADDRESS+0x08))
#define STK_CALIB		*((volatile u32*)(SysTick_BASE_ADDRESS+0x0C))



#endif
