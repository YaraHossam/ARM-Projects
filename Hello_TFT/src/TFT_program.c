/*
 * TFT_program.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "SPI_interface.h"
#include "STK_interface.h"



#include "TFT_interface.h"
#include "TFT_config.h"
#include "TFT_private.h"


const u16 Alph[26][15]={
 	{0, 514, 514, 514, 514, 514, 1022, 1022, 514, 514, 774, 260, 396, 248, 0},
   {0, 1020, 518, 514, 514, 514, 518, 1020, 518, 514, 514, 514, 518, 1020, 0},
   {0, 252, 390, 770, 512, 512, 512, 512, 512, 512, 512, 770, 390, 252, 0},
   {0, 1008, 536, 524, 518, 514, 514, 514, 514, 514, 518, 524, 536, 1008, 0},
   {0, 1022, 512, 512, 512, 512, 512, 1022, 512, 512, 512, 512, 512, 1022, 0},
	{0, 512, 512, 512, 512, 512, 512, 1022, 512, 512, 512, 512, 512, 1022, 0},
	{0, 252, 390, 770, 514, 514, 638, 638, 512, 512, 512, 770, 390, 252, 0},
	{0, 514, 514, 514, 514, 514, 514, 1022, 1022, 514, 514, 514, 514, 514, 0},
	{0, 1022, 1022, 32, 32, 32, 32, 32, 32, 32, 32, 32, 1022, 1022, 0},
	{0, 504, 780, 516, 516, 4, 4, 4, 4, 4, 4, 4, 1022, 1022, 0},
	{0, 514, 514, 514, 518, 524, 568, 992, 560, 536, 524, 518, 514, 514, 0},
	{0, 1022, 1022, 768, 768, 768, 768, 768, 768, 768, 768, 768, 768, 768, 0},
	{0, 514, 514, 514, 514, 514, 546, 626, 594, 594, 594, 594, 594, 396, 0},
	{0, 526, 522, 522, 538, 562, 546, 546, 610, 578, 706, 642, 642, 898, 0},
	{0, 112, 136, 260, 514, 514, 514, 514, 514, 514, 514, 260, 136, 112, 0},
	{0, 512, 512, 512, 512, 512, 512, 1020, 518, 514, 514, 514, 518, 1020, 0},
	{1, 114, 140, 268, 530, 546, 514, 514, 514, 514, 514, 260, 136, 112, 0},
	{0, 514, 516, 520, 528, 544, 960, 1020, 518, 514, 514, 514, 518, 1020, 0},
	{0, 120, 132, 258, 2, 4, 4, 248, 384, 256, 256, 258, 132, 120, 0},
	{0, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 1022, 1022, 0},
	{0, 508, 262, 770, 514, 514, 514, 514, 514, 514, 514, 514, 514, 514, 0},
	{0, 32, 216, 396, 260, 774, 514, 514, 514, 514, 514, 514, 514, 514, 0},
	{0, 396, 594, 594, 594, 594, 594, 546, 514, 514, 514, 514, 514, 514, 0},
	{0, 514, 260, 260, 136, 136, 80, 32, 32, 80, 136, 136, 260, 514, 0},
	{0, 32, 32, 32, 32, 32, 32, 32, 112, 216, 136, 396, 774, 514, 0},
	{0, 1022, 512, 256, 128, 64, 64, 32, 32, 16, 8, 4, 2, 1022, 0}

};

const u16 Numbers[10][15]={
		{0, 112, 136, 260, 260, 260, 260, 260, 260, 260, 260, 260, 136, 112, 0},//0
		{0, 248, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 160, 96, 0},//1
		{0, 252, 128, 128, 128, 64, 32, 16, 8, 4, 4, 260, 136, 112, 0},//2
		{0, 112, 136, 260, 4, 4, 8, 240, 8, 4, 4, 260, 136, 112, 0},//3
		{0, 4, 4, 4, 4, 4, 510, 260, 132, 68, 36, 20, 12, 4, 0},//4
		{0, 112, 136, 260, 4, 4, 4, 8, 496, 256, 256, 256, 256, 508, 0},//5
		{0, 112, 136, 260, 260, 260, 392, 368, 256, 256, 256, 260, 136, 112, 0},//6
		{0, 256, 128, 128, 64, 64, 32, 32, 16, 16, 8, 8, 4, 508, 0},//7
		{0, 112, 136, 260, 260, 260, 136, 112, 136, 260, 260, 260, 136, 112, 0},//8
		{0, 112, 136, 260, 4, 4, 4, 116, 140, 260, 260, 260, 136, 112, 0}//9
};

void HTFT_voidInit(void)
{
	//Reset ---> H100us , L1us , H100us , L100us , H120ms
	MGPIO_voidSetPinValue(TFT_RST_PIN , GPIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN , GPIO_LOW);
	MSTK_voidSetBusyWait(1);
	MGPIO_voidSetPinValue(TFT_RST_PIN , GPIO_HIGH);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN , GPIO_LOW);
	MSTK_voidSetBusyWait(100);
	MGPIO_voidSetPinValue(TFT_RST_PIN , GPIO_HIGH);
	MSTK_voidSetBusyWait(120000);
	//sleep out 0x11
	voidWriteCommand(0x11);
	//wait 150ms
	MSTK_voidSetBusyWait(150000);
	//color mode 0x3A + RGB565 0x05
	voidWriteCommand(0x3A);
	voidWriteData(0x05);
	//Display on 0x29
	voidWriteCommand(0x29);
}
void HTFT_voidDisplayImage(const u16* copy_image)
{
	u16 count;
	u8 Data;
	//set x address 0x2A  ---> start 0   end 127
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);
	//set y address 0x2B  ---> start 0   end 159
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);
	//RAM Write
	voidWriteCommand(0x2C);
	for (count = 0 ; count <20480 ; count++)
	{
		Data=copy_image[count]>>8;
		voidWriteData(Data); //high byte
		Data=copy_image[count] & 0x00ff;
		voidWriteData(Data); //low byte
	}
}
void HTFT_voidFillColor(u16 copy_u16Color)
{
	u16 count;
	u8 Data;
	//set x address 0x2A  ---> start 0   end 127
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(127);
	//set y address 0x2B  ---> start 0   end 159
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(0);
	voidWriteData(159);
	//RAM Write
	voidWriteCommand(0x2C);
	for (count = 0 ; count <20480 ; count++)
	{
		Data=copy_u16Color>>8;
		voidWriteData(Data); //high byte
		Data=copy_u16Color & 0x00ff;
		voidWriteData(Data); //low byte
	}
}
void HTFT_voidDrawRect(u8 x1, u8 x2 , u8 y1 , u8 y2 ,u16 copy_u16Color)
{
	u16 count;
	u8 Data;
	u16 size = (x2-x1+1)*(y2-y1+1);
	//set x address 0x2A  ---> start 0   end 127
	voidWriteCommand(0x2A);
	voidWriteData(0);
	voidWriteData(x1);
	voidWriteData(0);
	voidWriteData(x2);
	//set y address 0x2B  ---> start 0   end 159
	voidWriteCommand(0x2B);
	voidWriteData(0);
	voidWriteData(y1);
	voidWriteData(0);
	voidWriteData(y2);
	//RAM Write
	voidWriteCommand(0x2C);
	for (count = 0 ; count <size ; count++)
	{
		Data=copy_u16Color>>8;
		voidWriteData(Data); //high byte
		Data=copy_u16Color & 0x00ff;
		voidWriteData(Data); //low byte
	}
}
void HTFT_voidDrawPixal(u8 x , u8 y ,u16 copy_u16Color )
{
	HTFT_voidDrawRect(x,x+1,y,y+1,copy_u16Color);
}

void HTFT_voidDrawChar(u8 c , u8 x , u8 y , u16 copy_u16Color )
{
	u16 *letter=Alph[c-'A'];
	for(u8 row=0 ; row<15 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(letter[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,copy_u16Color);
			}
		}
	}
}
void HTFT_voidDrawNumChar(u8 c , u8 x , u8 y , u16 copy_u16Color )
{
	u16 *letter=Numbers[c-'0'];
	for(u8 row=0 ; row<15 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(letter[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,copy_u16Color);
			}
		}
	}
}
void HTFT_voidDrawNum(u8 n , u8 x , u8 y , u16 copy_u16Color )
{
	u16 *letter=Numbers[n];
	for(u8 row=0 ; row<15 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(letter[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,copy_u16Color);
			}
		}
	}
}
void HTFT_voidDraw2Dig(u8 num ,u8 x , u8 y , u16 copy_u16Color)
{
	u8 n1 , n2;
	n2=num/10;
	n1=num%10;
	HTFT_voidDrawNum(n2 , x , y , copy_u16Color);
	HTFT_voidDrawNum(n1 , x-11 , y , copy_u16Color);
}
void HTFT_voidClearDig(u8 x , u8 y , u16 copy_u16Color)
{
	HTFT_voidDrawRect(x,x+10,y,y+15,copy_u16Color);
}
void HTFT_voidClear2Dig(u8 x , u8 y , u16 copy_u16Color)
{
	HTFT_voidDrawRect(x,x+10,y,y+15,copy_u16Color);
	HTFT_voidDrawRect(x-11,x-11+10,y,y+15,copy_u16Color);
}

void HTFT_voidDrawString (u8 *st , u8 x ,u8 y ,u16 copy_u16Color )
{
	u8 i =0;
	while(st[i]!='\0')
	{
		if (st[i]==' ')
		{

		}
		else if(st[i]==':')
		{
			u8 letter[]={0, 0, 48, 48, 0, 0, 0, 0, 0, 0, 0, 48, 48, 0, 0};
			for(u8 row=0 ; row<15 ; row++)
				{
					for(u8 col=0 ; col<10 ; col++)
					{
						if (GET_BIT(letter[row],col))
						{
							HTFT_voidDrawPixal(x+col,y+row,copy_u16Color);
						}
					}
				}

		}
		else if (st[i]>='0' &&  st[i]<='9')
		{
			HTFT_voidDrawNumChar(st[i],x,y,copy_u16Color);
		}
		else
		{
			HTFT_voidDrawChar(st[i],x,y,copy_u16Color);

		}
		x=x-11;
		i++;
	}
}

static void voidWriteCommand(u8 copy_u8Command)
{
	u8 Local_u8Temp;
	MGPIO_voidSetPinValue(TFT_A0_PIN,GPIO_LOW);
	MSPI1_voidSendReceiveSynch(copy_u8Command, &Local_u8Temp);
}
static void voidWriteData(u8 copy_u8Data)
{
	u8 Local_u8Temp;
	MGPIO_voidSetPinValue(TFT_A0_PIN,GPIO_HIGH);
	MSPI1_voidSendReceiveSynch(copy_u8Data ,&Local_u8Temp);
}

void DrawPixel(u8 x, u8 y, u8 color)
{
  // set window
	//set x address 0x2A  ---> start 0   end 127
		voidWriteCommand(0x2A);
		voidWriteData(0);
		voidWriteData(x);
		voidWriteData(0);
		voidWriteData(x);
		//set y address 0x2B  ---> start 0   end 159
		voidWriteCommand(0x2B);
		voidWriteData(0);
		voidWriteData(y);
		voidWriteData(0);
		voidWriteData(y);

  // draw pixel by 565 mode
		// access to RAM
		voidWriteCommand(0x2C);
		  // counter

		    voidWriteData(color>>8); //high byte
		    voidWriteData(color & 0x00ff); //low byte

}


void DrawChar(char character, u16 color, ESizes size)
{
  // variables
  u8 letter, idxCol, idxRow;
  // check if character is out of range
  if ((character < 0x20) &&
      (character > 0x7f)) {
    // out of range

  }
  // last column of character array - 5 columns
  idxCol = CHARS_COLS_LEN;
  // last row of character array - 8 rows / bits
  idxRow = CHARS_ROWS_LEN;

  // --------------------------------------
  // SIZE X1 - normal font 1x high, 1x wide
  // --------------------------------------
  if (size == 0x11) {
    // loop through 5 bits
    while (idxCol--) {
      // read from ROM memory
      letter = character;
      // loop through 8 bits
      while (idxRow--) {
        // check if bit set
        if (letter & (1 << idxRow)) {
          // draw pixel
          DrawPixel( idxCol,  idxRow, color);
        }
      }
      // fill index row again
      idxRow = CHARS_ROWS_LEN;
    }

  // --------------------------------------
  // SIZE X2 - font 2x higher, normal wide
  // --------------------------------------
  } else if (size == 0x21) {
    // loop through 5 bytes
    while (idxCol--) {
      // read from ROM memory
      //letter = pgm_read_byte(&CHARACTERS[character - 32][idxCol]);
      // loop through 8 bits
      while (idxRow--) {
        // check if bit set
        if (letter & (1 << idxRow)) {
          // draw first left up pixel;
          // (idxRow << 1) - 2x multiplied
          DrawPixel( idxCol,  (idxRow << 1), color);
          // draw second left down pixel
          DrawPixel( idxCol,  (idxRow << 1) + 1, color);
        }
      }
      // fill index row again
      idxRow = CHARS_ROWS_LEN;
    }
  // --------------------------------------
  // SIZE X3 - font 2x higher, 2x wider
  // --------------------------------------
  } else if (size == 0x22) {
    // loop through 5 bytes
    while (idxCol--) {
      // read from ROM memory
      //letter = pgm_read_byte(&CHARACTERS[character - 32][idxCol]);
      // loop through 8 bits
      while (idxRow--) {
        // check if bit set
        if (letter & (1 << idxRow)) {
          // draw first left up pixel;
          // (idxRow << 1) - 2x multiplied
          DrawPixel( (idxCol << 1), (idxRow << 1), color);
          // draw second left down pixel
          DrawPixel( (idxCol << 1), (idxRow << 1) + 1, color);
          // draw third right up pixel
          DrawPixel( (idxCol << 1) + 1, (idxRow << 1), color);
          // draw fourth right down pixel
          DrawPixel((idxCol << 1) + 1,  (idxRow << 1) + 1, color);
        }
      }
      // fill index row again
      idxRow = CHARS_ROWS_LEN;
    }
  }


}
