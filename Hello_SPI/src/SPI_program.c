/*
 * SPI_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"

#include "SPI_interface.h"
#include "SPI_config.h"
#include "SPI_private.h"



void MSPI_voidSendReceiveSynch(u8 copy_u8DataToTransmit , u8 *copy_DataToReceive)
{
	MGPIO_voidSetPinValue(MSPI1_SALAVE_PIN,GPIO_LOW);

	//send data
	MSPI1 -> DR =  copy_u8DataToTransmit;

	//wait
	while(GET_BIT(MSPI1 -> SR,7)==1);

	//return to the received data
	*copy_DataToReceive=MSPI1 -> DR;

	MGPIO_voidSetPinValue(MSPI1_SALAVE_PIN,GPIO_HIGH);
}
