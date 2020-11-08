#ifndef		EXTI_INTERFACE_H
#define 	EXTI_INTERFACE_H

void MEXTI_voidInit(void);
void MEXTI_voidSetSignalLatch(u8 copy_u8EXTILine , u8 copy_u8EXTISenseMode);
void MEXTI_voidEnableEXTI(u8 copy_u8EXTILine);
void MEXTI_voidDisableEXTI(u8 copy_u8EXTILine);
void MEXTI_voidSoftwareTrigger(u8 copy_u8EXTILine);
void MEXTI_voidSetCallBack(u8 copy_u8EXTILine,void (*ptr) (void));

#endif
