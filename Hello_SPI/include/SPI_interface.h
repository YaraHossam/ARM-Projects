#ifndef SPI_INTERFACE_H
#define SPI_INTERFACE_H

void MSPI_voidInit(void);
void MSPI_voidSendReceiveSynch(u8 copy_u8DataToTransmit , u8 copy_DataToReceive);
void MSPI_voidSendReceiveASynch(u8 copy_u8DataToTransmit , void (*callback)(u8));

#endif
