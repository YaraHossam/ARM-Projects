/*
 * ArkanoidGame.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"

#include "TFT_interface.h"

#include "ArkanoidGame.h"


s8 Arkanoid_right=1,Arkanoid_up=1;
u8 Ark_points =0;
s8 x_ball=3 , y_ball=2  , x_paddle=3 , y_paddle=0;

u8 Ark_field[18][8]={
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}};

void Ark_Background(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawRect(0,127,143,159,0xFFFF);
	HTFT_voidDrawString("POINT",110,143,0x0000);
	HTFT_voidDraw2Dig(Ark_points,50,143,0xF800);
}

void blockDraw(u8 x, u8  y , u16 Color)
{
	HTFT_voidDrawRect((x*16)+2,((x+1)*16)+16-2 , (y*8)+2,(y*8)+8-2 , Color);
}
void blockArk_Background(u8 x, u8  y , u16 Color)
{
	HTFT_voidDrawRect((x*16),(x*16)+16 , (y*8),(y*8)+8 , Color);
}

void DrawBlocks(void)
{
	u8 row=0;
	for(s8 r=17 ; r>=0 ; r--)
	{
		for(u8 c=0 ; c<8 ; c+=2)
		{
			if(Ark_field[r][c]==1)
			{
				blockDraw(c,row,0x07E0);
			}
		}
		row++;
	}
}

void paddleDraw(u8 x, u8  y )
{
	u16 Color=0x001F;
	HTFT_voidDrawRect((x*16),(x*16)+16 , (y*8),(y*8)+8 , Color);
	HTFT_voidDrawRect((x*16),(x*16)+16 , ((y+1)*8),((y+1)*8)+8 , Color);
	HTFT_voidDrawRect(((x+1)*16),((x+1)*16)+16 , (y*8),(y*8)+8 , Color);
	HTFT_voidDrawRect(((x+1)*16),((x+1)*16)+16 , ((y+1)*8),((y+1)*8)+8 , Color);
}

void BallDraw(u8 x , u8 y )
{
	u16 ball[8]={384, 960, 2016, 4080, 4080, 2016, 960, 384};
	for(u8 row=0 ; row<8 ; row++)
		{
			for(u8 col=0 ; col<16 ; col++)
			{
				if (GET_BIT(ball[row],col))
				{
					HTFT_voidDrawPixal((x*16)+col,(y*8)+row,0xF800);
				}
			}
		}
}

void changBallArkanoid_right(void)
{
	if(Arkanoid_right==1)
	{
		Arkanoid_right=0;
	}
	else
	{
		Arkanoid_right=1;
	}
}
void changBallArkanoid_up(void)
{
	if(Arkanoid_up==1)
	{
		Arkanoid_up=0;
	}
	else
	{
		Arkanoid_up=1;
	}
}

void changeBallXY(void)
{
	if(Arkanoid_right==1 && x_ball>0)
			{
					x_ball--;
			}
			else if(Arkanoid_right==0 && x_ball<7)
			{

					x_ball++;

			}
			/////////////////////////////////////
			if(Arkanoid_up==1 && y_ball<17)
			{
				y_ball++;
			}
			else if(Arkanoid_up==0 && y_ball>2)
			{
				y_ball--;
			}
			/////////////////////////////////////
			if(x_ball==0 || x_ball==7 )
			{
				changBallArkanoid_right();
			}
			//////////////////////////////////////
			if(y_ball==2 || y_ball==17 )
			{
				changBallArkanoid_up();
			}
			/////////////////////////////////////
}

void clearSqr(u8 x ,u8 y )
{
	if(x%2==0)
	{
		HTFT_voidDrawRect((x*16),((x+1)*16)+16 , (y*8),(y*8)+8 , 0x0000);
		Ark_field[17-y][7-x]=0;
		Ark_field[17-y][7-(x+1)]=0;
	}
	else
	{
		HTFT_voidDrawRect(((x-1)*16),(x*16)+16 , (y*8),(y*8)+8 , 0x0000);
		Ark_field[17-y][7-x]=0;
		Ark_field[17-y][(7-(x-1))]=0;
	}
}

void clearPaddle(u8 x ,u8 y )
{
	u16 Color=0x0000;
		HTFT_voidDrawRect((x*16),(x*16)+16 , (y*8),(y*8)+8 , Color);
		HTFT_voidDrawRect((x*16),(x*16)+16 , ((y+1)*8),((y+1)*8)+8 , Color);
		HTFT_voidDrawRect(((x+1)*16),((x+1)*16)+16 , (y*8),(y*8)+8 , Color);
		HTFT_voidDrawRect(((x+1)*16),((x+1)*16)+16 , ((y+1)*8),((y+1)*8)+8 , Color);
}

void Input(void)
{
	if(MGPIO_u8GetPinValue(UP)==0)
	{

	}
	else if(MGPIO_u8GetPinValue(DOWN)==0)
	{

	}
	else if(MGPIO_u8GetPinValue(LEFT)==0)
	{
		clearPaddle(x_paddle,y_paddle);
		paddleDraw(++x_paddle,y_paddle);

	}
	else if(MGPIO_u8GetPinValue(RIGHT)==0)
	{
		clearPaddle(x_paddle,y_paddle);
		paddleDraw(--x_paddle,y_paddle);
	}
}

void gameover(void)
{
	clearSqr(x_ball,y_ball);
	BallDraw(x_ball,y_ball-2);
	MSTK_voidSetBusyWait(200000);
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawString("GAME OVER",100,80,0xF800);
}
void Arkanoid_Game(void)
{
	Ark_Background();
	DrawBlocks();
	paddleDraw(x_paddle,y_paddle);
	BallDraw(x_ball,y_ball);


	while(!(y_ball==2 && (x_paddle!=x_ball && x_ball!=x_paddle+1)))
	{
		clearSqr(x_ball,y_ball);
		changeBallXY();
		BallDraw(x_ball,y_ball);
		Input();
		//check -->panddle,block,
		if(Ark_field[17-y_ball][7-x_ball]==1)
		{
			HTFT_voidClear2Dig(50,143,0xFFFF);
			HTFT_voidDraw2Dig(++Ark_points,50,143,0xF800);
			changBallArkanoid_right();
			changBallArkanoid_up();
		}
		MSTK_voidSetBusyWait(100000);
	}

	gameover();
}







