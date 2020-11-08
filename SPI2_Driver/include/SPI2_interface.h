#ifndef SPI2_INTERFACE_H
#define SPI2_INTERFACE_H

void MSPI2_voidInit(void); /* Home Work */

void MSPI2_voidSendReceiveSynch(u8 Copy_u8DataToTransmit, u8 *Copy_DataToReceive);

void MSPI2_voidSendReceiveAsynch(u8 Copy_u8DataToTransmit, void (*CallBack)(u8));

#endif
