#ifndef UART_INTERFACE_H
#define UART_INTERFACE_H

void MUSART_voidInit(void);
void MUSART_voidTransmit(u8 arr[]);
u8 MUSART_u8Receive(void);

#endif
