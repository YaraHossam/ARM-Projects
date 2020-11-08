/********************************/
/* Author  : Yara Hossam        */
/* Date    : 1  Sep 2020        */
/* Version : V01                */
/********************************/

#ifndef		STK_INTERFACE_H
#define 	STK_INTERFACE_H

void MSTK_voidInit(void);
void MSTK_voidSetBusyWait( u32 copy_u32Ticks);
void MSTK_voidIntervalSingle(u32 copy_u32Ticks , void (*copy_ptr) (void));
void MSTK_voidIntervalPeriodic(u32 copy_u32Ticks , void (*copy_ptr) (void));
void MSTK_voidStopTimer(void);
u32 MSTK_u32GetElapsedTime(void); // load-value
u32 MSTK_u32GetRemaining(void);   //value



#endif
