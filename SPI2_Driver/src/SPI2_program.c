/*
 * SPI2_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "SPI2_interface.h"
#include "SPI2_config.h"
#include "SPI2_private.h"

void (*CallBack)(u8);

void MSPI2_voidInit(void)
{
	MSPI2->CR1 = 0x0347;
}

void MSPI2_voidSendReceiveSynch(u8 Copy_u8DataToTransmit, u8 *Copy_DataToReceive)
{
	/* Clear For Slave Select Pin */
	MGPIO_voidSetPinValue(MSPI2_SLAVE_PIN,GPIO_LOW);

	/* Send Data */
	MSPI2 -> DR = Copy_u8DataToTransmit;

	/* Wait Busy Flag to finish */
	while (GET_BIT(MSPI2 -> SR, 7) == 1);

 	/* Return to the received data */
	*Copy_DataToReceive = MSPI2 -> DR;

	/* Set Salve Select Pin */
	MGPIO_voidSetPinValue(MSPI2_SLAVE_PIN,GPIO_HIGH);
}
