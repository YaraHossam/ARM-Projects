/*
 * STP_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "STK_interface.h"

#include "STP_interface.h"
#include "STP_config.h"
#include "STP_private.h"

void HSTP_voidSendSynchronus(u8 copy_u8DataToSend)
{
	//send bit by bit starting from MSB
	s8 Local_s8Counter;
	u8 Local_u8Bit;
	for (Local_s8Counter = 7 ; Local_s8Counter>=0 ; Local_s8Counter--)
	{
		Local_u8Bit=GET_BIT(copy_u8DataToSend,Local_s8Counter);
		MGPIO_voidSetPinValue(HSTP_SERIAL_DATA,Local_u8Bit);

		//send pulse to shift clock
		MGPIO_voidSetPinValue(HSTP_SHIFT_CLOCK,GPIO_HIGH);
		MSTK_voidSetBusyWait(1);
		MGPIO_voidSetPinValue(HSTP_SHIFT_CLOCK,GPIO_LOW);
		MSTK_voidSetBusyWait(1);

	}
	//send pulse to store clock
	MGPIO_voidSetPinValue(HSTP_STORE_CLOCK,GPIO_HIGH);
	MSTK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(HSTP_STORE_CLOCK,GPIO_LOW);
	MSTK_voidSetBusyWait(1);
}

