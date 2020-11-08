/*
 * UART_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"
#include "UART_private.h"
#include "UART_config.h"

void MUSART_voidInit(void)
{
	/*9600       BRR=0x341 */
	/*115200     BRR= */
	UART1 -> BRR =0x341;

	SET_BIT(UART1 -> CR1 ,2); //Enable RX
	SET_BIT(UART1 -> CR1 ,3); //Enable TX
	SET_BIT(UART1 -> CR1 ,13); //Enable UART

	/* Clear Status Register */
	UART1 -> SR =0;
}
void MUSART_voidTransmit(u8 arr[])
{
	u8 i =0;
	while(arr[i] !='\0')
	{
		UART1 -> DR = arr[i];
		//wait till transmission is complete
		while(GET_BIT(UART1 -> SR ,6) ==0);
		i++;
	}
}
u8 MUSART_u8Receive(void)
{
	while(GET_BIT(UART1 -> SR , 5 )==0);
	return (0xFF & (UART1 -> DR));
}
