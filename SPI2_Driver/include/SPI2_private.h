#ifndef SPI2_PRIVATE_H
#define SPI2_PRIVATE_H

typedef struct
{
	volatile u32 CR1    ;
	volatile u32 CR2    ;
	volatile u32 SR     ;
	volatile u32 DR     ;
	volatile u32 CRCPR  ;
	volatile u32 RXCRCR ;
	volatile u32 TXCRCR ;
	volatile u32 I2SCFGR;
	volatile u32 I2SPR  ;

}SPI2_Register;


#define MSPI2   ((SPI2_Register*)0x40003800)

#endif
