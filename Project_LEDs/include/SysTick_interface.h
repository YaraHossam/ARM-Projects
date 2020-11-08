/********************************/
/* Author  : Yara Hossam        */
/* Date    : 24 AUG 2020        */
/* Version : V01                */
/********************************/
#ifndef SYSTICK_INTERFACE_H
#define SYSTICK_INTERFACE_H

void SysTick_voidInit(void);
void SysTick_voidMS(u32 copy_u32ValueMS);
u8 SysTick_u8ReadFlag(void);

#endif
