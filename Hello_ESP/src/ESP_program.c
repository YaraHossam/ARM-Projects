/*
 * ESP_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "UART_interface.h"

#include "ESP_interface.h"
#include "ESP_private.h"
#include "ESP_config.h"

void HESP_voidInit(void)
{
	u8 Local_u8Res=0;
	//stop ECHO
	while(Local_u8Res==0)
	{
		MUSART_voidTransmit("ATE0\r\n");
		Local_u8Res=ESPValidateCmd();
	}

	Local_u8Res=0;

	//set station mode
	while(Local_u8Res==0)
	{
		MUSART_voidTransmit("AT+CWMODE=1\r\n");
		Local_u8Res=ESPValidateCmd();
	}
	Local_u8Res=0;

}

u8 ESPValidateCmd(void)
{
	u8 Local_u8Response[100]={0};
	u8 i=0;
	u8 result=0;

	while(i<= 100)
	{
		Local_u8Response[i]=MUSART_u8Receive();
		i++;
	}
	//check if ok
	for(u8 i = 0 ; i<99 ; i++)
	{
		if(Local_u8Response[i]=='O' && Local_u8Response[i+1]=='K')
		{
			result=1;
			break;
		}
	}
	return result;

}
u8 ESPValidateCmdRes(void)
{
	u8 Local_u8Response[100]={0};
	u8 i=0;
	u8 RES=0;

	while(Local_u8Response[i]!=255)
	{
		Local_u8Response[i]=MUSART_u8Receive();
		i++;
	}
	//check if ok
	for(u8 i = 0 ; i<99 ; i++)
	{
		if(Local_u8Response[i]==':')
		{
			RES=Local_u8Response[i+1];
			break;
		}
	}
	return RES;

}

void HESP_voidConnectWiFi(u8* copy_wifiname , u8* copy_pass)
{
	u8 Local_u8Res=0;
	while(Local_u8Res==0)
	{
		MUSART_voidTransmit("AT+CWJAP_CUR=\"body\",\"yara01116203170\"\r\n");
//		MUSART_voidTransmit("AT+CWJAP_CUR=\"");
//		MUSART_voidTransmit(copy_wifiname);
//		MUSART_voidTransmit("\",\"");
//		MUSART_voidTransmit(copy_pass);
//		MUSART_voidTransmit("\"\r\n");

		Local_u8Res=ESPValidateCmd();
	}
}

void HESP_voidConnectServer(u8* copy_IP , u8* copy_Port)
{
	u8 Local_u8Res=0;
	while(Local_u8Res==0)
	{
		MUSART_voidTransmit("AT+CIPSTART=\"TCP\",\"162.253.155.226\",80\r\n");
//		MUSART_voidTransmit("AT+CIPSTART=\"TCP\",\"");
//		MUSART_voidTransmit(copy_IP);
//		MUSART_voidTransmit("\",");
//		MUSART_voidTransmit(copy_Port);
//		MUSART_voidTransmit("\r\n");


		Local_u8Res=ESPValidateCmd();
	}
}

u8 HESP_u8SendReceiveData(void)
{
	u8 Local_u8Res=0;
	u8 Receive;
	while(Local_u8Res==0)
	{
		MUSART_voidTransmit("AT+CIPSEND=46\r\n");

		Local_u8Res=ESPValidateCmd();
	}
	Local_u8Res=0;

	MUSART_voidTransmit("GET http://imtarmyara.freevar.com/status.txt\r\n");

	Receive=ESPValidateCmdRes();

	return Receive;
}
