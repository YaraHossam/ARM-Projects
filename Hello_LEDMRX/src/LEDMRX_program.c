/*
 * LEDMRX_program.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "STK_interface.h"

#include "LEDMRX_interface.h"
#include "LEDMRX_private.h"
#include "LEDMRX_config.h"


void HLEDMRX_voidInit(void)
{
	MGPIO_voidSetPinDirection(LEDMRX_R0_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_R1_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_R2_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_R3_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_R4_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_R5_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_R6_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_R7_PIN,OUTPUT_2MHZ_PP);

	MGPIO_voidSetPinDirection(LEDMRX_C0_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_C1_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_C2_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_C3_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_C4_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_C5_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_C6_PIN,OUTPUT_2MHZ_PP);
	MGPIO_voidSetPinDirection(LEDMRX_C7_PIN,OUTPUT_2MHZ_PP);


}

void HLEDMRX_voidDisplay(u8 *copy_u8Data)
{

	//disable all columns
	DisableAllCols();
	//enable bits on row
	SetRowValues(copy_u8Data[0]);
	//enable column 0
	MGPIO_voidSetPinValue(LEDMRX_C0_PIN,GPIO_LOW);
	//delay
	MSTK_voidSetBusyWait(2500);

	DisableAllCols();
	SetRowValues(copy_u8Data[1]);
	MGPIO_voidSetPinValue(LEDMRX_C1_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2500);

	DisableAllCols();
	SetRowValues(copy_u8Data[2]);
	MGPIO_voidSetPinValue(LEDMRX_C2_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2500);

	DisableAllCols();
	SetRowValues(copy_u8Data[3]);
	MGPIO_voidSetPinValue(LEDMRX_C3_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2500);

	DisableAllCols();
	SetRowValues(copy_u8Data[4]);
	MGPIO_voidSetPinValue(LEDMRX_C4_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2500);

	DisableAllCols();
	SetRowValues(copy_u8Data[5]);
	MGPIO_voidSetPinValue(LEDMRX_C5_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2500);

	DisableAllCols();
	SetRowValues(copy_u8Data[6]);
	MGPIO_voidSetPinValue(LEDMRX_C6_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2500);

	DisableAllCols();
	SetRowValues(copy_u8Data[7]);
	MGPIO_voidSetPinValue(LEDMRX_C7_PIN,GPIO_LOW);
	MSTK_voidSetBusyWait(2500);

}

static void DisableAllCols(void)
{
	MGPIO_voidSetPinValue(LEDMRX_C0_PIN,GPIO_HIGH);
	MGPIO_voidSetPinValue(LEDMRX_C1_PIN,GPIO_HIGH);
	MGPIO_voidSetPinValue(LEDMRX_C2_PIN,GPIO_HIGH);
	MGPIO_voidSetPinValue(LEDMRX_C3_PIN,GPIO_HIGH);
	MGPIO_voidSetPinValue(LEDMRX_C4_PIN,GPIO_HIGH);
	MGPIO_voidSetPinValue(LEDMRX_C5_PIN,GPIO_HIGH);
	MGPIO_voidSetPinValue(LEDMRX_C6_PIN,GPIO_HIGH);
	MGPIO_voidSetPinValue(LEDMRX_C7_PIN,GPIO_HIGH);
}

static void SetRowValues(u8 copy_u8Value)
{
	u8 local_bit;
		local_bit=GET_BIT(copy_u8Value,0);
		MGPIO_voidSetPinValue(LEDMRX_R0_PIN,local_bit);

		local_bit=GET_BIT(copy_u8Value,1);
		MGPIO_voidSetPinValue(LEDMRX_R1_PIN,local_bit);

		local_bit=GET_BIT(copy_u8Value,2);
		MGPIO_voidSetPinValue(LEDMRX_R2_PIN,local_bit);

		local_bit=GET_BIT(copy_u8Value,3);
		MGPIO_voidSetPinValue(LEDMRX_R3_PIN,local_bit);

		local_bit=GET_BIT(copy_u8Value,4);
		MGPIO_voidSetPinValue(LEDMRX_R4_PIN,local_bit);

		local_bit=GET_BIT(copy_u8Value,5);
		MGPIO_voidSetPinValue(LEDMRX_R5_PIN,local_bit);

		local_bit=GET_BIT(copy_u8Value,6);
		MGPIO_voidSetPinValue(LEDMRX_R6_PIN,local_bit);

		local_bit=GET_BIT(copy_u8Value,7);
		MGPIO_voidSetPinValue(LEDMRX_R7_PIN,local_bit);
}
void DisplayOneTime(u8 *copy_u8Data)
{
	//disable all columns
		DisableAllCols();
		//enable bits on row
		SetRowValues(copy_u8Data[0]);
		//enable column 0
		MGPIO_voidSetPinValue(LEDMRX_C0_PIN,GPIO_LOW);
		//delay
		MSTK_voidSetBusyWait(2500);

		DisableAllCols();
		SetRowValues(copy_u8Data[1]);
		MGPIO_voidSetPinValue(LEDMRX_C1_PIN,GPIO_LOW);
		MSTK_voidSetBusyWait(2500);

		DisableAllCols();
		SetRowValues(copy_u8Data[2]);
		MGPIO_voidSetPinValue(LEDMRX_C2_PIN,GPIO_LOW);
		MSTK_voidSetBusyWait(2500);

		DisableAllCols();
		SetRowValues(copy_u8Data[3]);
		MGPIO_voidSetPinValue(LEDMRX_C3_PIN,GPIO_LOW);
		MSTK_voidSetBusyWait(2500);

		DisableAllCols();
		SetRowValues(copy_u8Data[4]);
		MGPIO_voidSetPinValue(LEDMRX_C4_PIN,GPIO_LOW);
		MSTK_voidSetBusyWait(2500);

		DisableAllCols();
		SetRowValues(copy_u8Data[5]);
		MGPIO_voidSetPinValue(LEDMRX_C5_PIN,GPIO_LOW);
		MSTK_voidSetBusyWait(2500);

		DisableAllCols();
		SetRowValues(copy_u8Data[6]);
		MGPIO_voidSetPinValue(LEDMRX_C6_PIN,GPIO_LOW);
		MSTK_voidSetBusyWait(2500);

		DisableAllCols();
		SetRowValues(copy_u8Data[7]);
		MGPIO_voidSetPinValue(LEDMRX_C7_PIN,GPIO_LOW);
		MSTK_voidSetBusyWait(2500);
}
void HLEDMRX_voidDisplayFrame(u8 *copy_u8Data)
{
	u8 * localdata;
	while(1)
	{
	for(int i = 0 ; i<30 ; i++)
	{
		localdata=copy_u8Data+i;
		DisplayOneTime(localdata);
	}
	}
}














