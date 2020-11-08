#ifndef SPI_PRIVATE_H
#define SPI_PRIVATE_H

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR;

}SPI_REG;

#define MSPI1 ((SPI_REG*)0x40013000)

#endif
