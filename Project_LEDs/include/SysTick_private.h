/********************************/
/* Author  : Yara Hossam        */
/* Date    : 24 AUG 2020        */
/* Version : V01                */
/********************************/
#ifndef SYSTICK_PRIVATE_H
#define SYSTICK_PRIVATE_H

#define SysTick_BASE_ADDRESS		0xE000E010

#define STK_CTRL		*((u32*)(SysTick_BASE_ADDRESS))
#define STK_LOAD		*((u32*)(SysTick_BASE_ADDRESS+0x04))
#define STK_VAL			*((u32*)(SysTick_BASE_ADDRESS+0x08))
#define STK_CALIB		*((u32*)(SysTick_BASE_ADDRESS+0x0C))

#endif
