#ifndef TFT_INTERFACE_H
#define TFT_INTERFACE_H

void HTFT_voidInit(void);
void HTFT_voidDisplayImage(const u16* copy_image);
void HTFT_voidFillColor(u16 copy_u16Color);
void HTFT_voidDrawRect(u8 x1, u8 x2 , u8 y1 , u8 y2 ,u16 copy_u16Color);
void HTFT_voidA(u8 x1, u8 x2 , u8 y1 , u8 y2 ,u16 copy_u16Color);
void HTFT_voidDrawPixal(u8 x , u8 y ,u16 copy_u16Color );
void HTFT_voidDrawChar(u8 c , u8 x , u8 y , u16 copy_u16Color );
void HTFT_voidDrawString (u8 *st , u8 x ,u8 y ,u16 copy_u16Color );
void HTFT_voidDrawNumChar(u8 c , u8 x , u8 y , u16 copy_u16Color );
void HTFT_voidDrawNum(u8 n , u8 x , u8 y , u16 copy_u16Color );
void HTFT_voidClearDig(u8 x , u8 y , u16 copy_u16Color);
void HTFT_voidDraw2Dig(u8 num ,u8 x , u8 y , u16 copy_u16Color);
void HTFT_voidClear2Dig(u8 x , u8 y , u16 copy_u16Color);
void HTFT_voidDrawCup( u8 x , u8 y , u16 copy_u16Color);

#endif
