/*
 * Minesweeper.c
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

#include "Minesweeper.h"


u8 Mines=10;

u8 lose=0, win=0;

// field1[8][8]={
//		{1,1,1,1,1,0,0,0},
//		{9,1,2,9,2,0,0,0},
//		{2,3,3,9,2,0,0,0},
//		{9,2,9,3,3,1,1,0},
//		{2,3,2,9,3,9,2,0},
//		{9,2,1,1,3,9,2,0},
//		{9,2,0,0,1,1,1,0},
//		{1,1,0,0,0,0,0,0}};

// field1[8][8]={
//		{0,1,2,3,2,1,0,0},
//		{0,1,9,9,9,1,1,1},
//		{1,2,3,3,2,1,1,9},
//		{2,9,1,0,0,0,2,2},
//		{9,2,1,0,0,0,1,9},
//		{2,3,1,1,0,0,1,1},
//		{9,2,9,2,1,1,0,0},
//		{1,2,1,2,9,1,0,0}};

u8 field1[8][8]={
		{1,2,9,2,9,1,0,0},
		{9,3,1,2,1,1,0,0},
		{9,2,0,1,1,1,0,0},
		{2,2,0,1,9,2,1,0},
		{9,3,2,2,2,9,1,0},
		{2,9,9,1,1,1,1,0},
		{2,3,3,1,0,0,0,0},
		{1,9,1,0,0,0,0,0}};

//u8 field1_open[8][8]={
//		{0,0,0,0,1,1,1,1},
//		{0,0,0,0,1,1,1,1},
//		{0,0,0,0,1,1,1,1},
//		{0,0,0,0,0,1,1,1},
//		{0,0,0,0,0,0,1,1},
//		{0,1,1,1,1,0,1,1},
//		{0,1,1,1,1,1,1,1},
//		{0,1,1,1,1,1,1,1}};

//u8 field1_open[8][8]={
//		{1,1,0,0,0,4,4,4},
//		{1,1,0,0,0,4,4,4},
//		{1,1,2,2,2,2,0,0},
//		{0,0,2,2,2,2,0,0},
//		{0,0,2,2,2,2,0,0},
//		{0,0,2,2,2,2,3,3},
//		{0,0,2,0,0,3,3,3},
//		{0,0,0,0,0,3,3,3}};

u8 field1_open[8][8]={
		{0,0,0,0,0,1,1,1},
		{0,2,2,2,0,1,1,1},
		{0,2,2,2,0,1,1,1},
		{0,2,2,2,0,0,1,1},
		{0,2,2,2,0,0,1,1},
		{0,0,0,1,1,1,1,1},
		{0,0,0,1,1,1,1,1},
		{0,0,1,1,1,1,1,1}};

u8 status_field1[8][8]={
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE},
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE},
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE},
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE},
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE},
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE},
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE},
		{CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE,CLOSE}};


s8 x_sqr=0 , y_sqr=0;
u8 flag=0 , Dir=0;

void Background(void)
{
		HTFT_voidFillColor(0x0000);
		HTFT_voidDrawString("MINES:",110,140,0xFFFF);
		HTFT_voidDraw2Dig(Mines,40,140,0xF800);
		for(u8 row= 0 ; row < 8 ; row ++)
		{
			for(u8 col =0 ; col < 8 ; col++)
			{

				HTFT_voidDrawRect((col*16)+1,((col*16)+16)-1 , (row*16)+1,((row*16)+16)-1 , 0x632C);
			}
		}
}

void NumDraw(u8 num ,u8 x , u8 y ,u16 Color)
{
	HTFT_voidDrawNum(num, (x*16) , (y*16), Color);
}

void MineDraw(u8 x , u8 y)
{
	u16 Mine[16]={0, 0, 12684, 14748, 8184, 4080, 4080, 16380, 16380, 4080, 4080, 8184, 14748, 12684, 0, 0};
		for(u8 row=0 ; row<16 ; row++)
		{
			for(u8 col=0 ; col<16 ; col++)
			{
				if (GET_BIT(Mine[row],col))
				{
					HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x0000);
				}
			}
		}
}

void FlagDraw(u8 x , u8 y)
{
	u16 LegFlag[16]={0, 8128, 3968, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 512, 0};
	u16 redFlag[16]={0, 0, 0, 0, 0, 0, 0, 448, 496, 504, 496, 480, 448, 384, 256, 0};
			for(u8 row=0 ; row<16 ; row++)
			{
				for(u8 col=0 ; col<16 ; col++)
				{
					if (GET_BIT(LegFlag[row],col))
					{
						HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x0000);
					}
				}
			}
			/////////////
			for(u8 row=0 ; row<16 ; row++)
						{
							for(u8 col=0 ; col<16 ; col++)
							{
								if (GET_BIT(redFlag[row],col))
								{
									HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0xF800);
								}
							}
						}
}

void DrawMap(void)
{
	for(s8 r=7 ; r>=0 ; r--)
	{
		for(s8 c=7 ; c>=0 ; c--)
		{
			if(field1[r][c]==0)
			{

			}
			else if(field1[r][c]==1)
			{
				NumDraw(1,7-c,7-r,0x001F);
			}
			else if(field1[r][c]==2)
			{
				NumDraw(2,7-c,7-r,0x0320);
			}
			else if(field1[r][c]==3)
			{
				NumDraw(3,7-c,7-r,0x9000);
			}
			else if(field1[r][c]==4)
			{
				NumDraw(4,7-c,7-r,0x000C);
			}
			else if(field1[r][c]==9)
			{
				MineDraw(7-c,7-r);
			}
		}

	}
}

void DrawSqr(u8 x , u8 y)
{
	u16 Color= 0x0841;
	HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1 ,((y*16)+16)-1 , Color);
}

void Input(void)
{
    	if(MGPIO_u8GetPinValue(UP)==0 && y_sqr<7)
		{
			Dir=Dir_up;
			flag=1;
		}
		else if(MGPIO_u8GetPinValue(DOWN)==0 && y_sqr>0)
		{
			Dir=Dir_down;
			flag=1;
		}
		else if(MGPIO_u8GetPinValue(LEFT)==0 && x_sqr<7)
		{
			Dir=Dir_left;
			flag=1;
		}
		else if(MGPIO_u8GetPinValue(RIGHT)==0 && x_sqr>0)
		{
			Dir=Dir_right;
			flag=1;
		}
		else if(MGPIO_u8GetPinValue(OPEN_SQR)==0)
		{
			Dir=Dir_open;
			flag=1;
		}
		else if(MGPIO_u8GetPinValue(SAVE_SQR)==0)
		{
			Dir=Dir_save;
			flag=1;
		}
}

void DrawCloseCase(u8 x , u8 y)
{
	HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x632C);
}

void openall(u8 x , u8 y)
{
	u8 value=field1_open[7-y][7-x];
	for(u8 r=0 ; r<8 ; r++)
	{
		for(u8 c=0 ; c<8 ; c++)
		{
			if (field1_open[r][c]==value && field1[r][c]==0)
			{
				status_field1[r][c]=OPEN;
				HTFT_voidDrawRect(((7-c)*16)+1,(((7-c)*16)+16)-1 , ((7-r)*16)+1,(((7-r)*16)+16)-1 , 0x10A2);
			}
			else if(field1_open[r][c]==value)
			{
				status_field1[r][c]=OPEN;
				Status((7-c),(7-r));
			}
		}
	}
}

void DrawOpenCase(u8 x , u8 y)
{
	u8 r=7-y;
	u8 c=7-x;
	HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x632C);
				if(field1[r][c]==0)
				{
					//open all
					openall(x,y);
					HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x10A2);
				}
				else if(field1[r][c]==1)
				{
					HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x10A2);
					NumDraw(1,x,y,0x001F);
				}
				else if(field1[r][c]==2)
				{
					HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x10A2);
					NumDraw(2,x,y,0x0320);
				}
				else if(field1[r][c]==3)
				{
					HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x10A2);
					NumDraw(3,x,y,0x9000);
				}
				else if(field1[r][c]==4)
				{
					HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x10A2);
					NumDraw(4,x,y,0x000C);
				}
				else if(field1[r][c]==9)
				{
					HTFT_voidDrawRect((x*16)+1,((x*16)+16)-1 , (y*16)+1,((y*16)+16)-1 , 0x10A2);
					MineDraw(x,y);
				}
}

void Status(u8 x , u8 y)
{
	if (status_field1[7-y][7-x]==CLOSE)
	{
		DrawCloseCase(x,y);
	}
	else if (status_field1[7-y][7-x]==OPEN)
	{
		DrawOpenCase(x,y);
	}
	else if (status_field1[7-y][7-x]==SAVE)
	{
		FlagDraw(x,y);
	}
}

u8 CheckIfMine(u8 x , u8 y)
{
	if(field1[7-y][7-x]==9)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

u8 checkWin(void)
{
	for(u8 r=0 ; r<8 ; r++)
	{
		for(u8 c=0 ; c<8 ; c++)
		{
			if(field1[r][c]==9 && status_field1[r][c]==SAVE)
			{

			}
			else if ((field1[r][c]==9 && status_field1[r][c]!=SAVE)||(field1[r][c]!=9 && status_field1[r][c]==SAVE))
			{
				return 0;
			}
		}
	}
	return 1;
}

void gameover(void)
{
	HTFT_voidDrawRect(0,127,50+20,70+30,0x0000);
	HTFT_voidDrawString("GAME OVER",100,80,0xF800);
}

void Minesweeper_Game(void)
{
	Background();
	//DrawMap();
	DrawSqr(x_sqr,y_sqr);
	//FlagDraw(7,0);
	while(!lose)
	{
		while(!flag)
		{
			Input();
			MSTK_voidSetBusyWait(200000);
		}
		switch(Dir)
			{
			case Dir_up:
				Status(x_sqr,y_sqr);
				DrawSqr(x_sqr,++y_sqr);
				Dir=0;
				break;
			case Dir_down:
				Status(x_sqr,y_sqr);
				DrawSqr(x_sqr,--y_sqr);
				Dir=0;
				break;
			case Dir_left:
				Status(x_sqr,y_sqr);
				DrawSqr(++x_sqr,y_sqr);
				Dir=0;
				break;
			case Dir_right:
				Status(x_sqr,y_sqr);
				DrawSqr(--x_sqr,y_sqr);
				Dir=0;
				break;
			case Dir_open:
				if(status_field1[7-y_sqr][7-x_sqr]==CLOSE || status_field1[7-y_sqr][7-x_sqr]==SAVE)
				{
					if(status_field1[7-y_sqr][7-x_sqr]==SAVE)
					{
						if(Mines<10)
						 {Mines++;}
						HTFT_voidClear2Dig(40,140,0x0000);
						HTFT_voidDraw2Dig(Mines,40,140,0xF800);
					}
					status_field1[7-y_sqr][7-x_sqr]=OPEN;
					Status(x_sqr,y_sqr);
					//check if Mine
					lose=CheckIfMine(x_sqr,y_sqr);
				}
				Dir=0;
				break;
			case Dir_save:
				if(Mines>0 && status_field1[7-y_sqr][7-x_sqr]==CLOSE)
				{
					status_field1[7-y_sqr][7-x_sqr]=SAVE;
					Status(x_sqr,y_sqr);
					//Min --
					Mines--;
					HTFT_voidClear2Dig(40,140,0x0000);
					HTFT_voidDraw2Dig(Mines,40,140,0xF800);

				}
				Dir=0;
				break;
			default:break;
			}
		flag=0;
		if(Mines==0)
		{
			//check if win
			if(checkWin())
			{
				win=1;
				break;
			}
		}

	}
	if(win==1)
	{
		HTFT_voidDrawRect(0,127,50+20,70+30,0x0000);
		HTFT_voidDrawString("YOU DO IT",100,80,0xFFE0);
	}
	else
	{
		//gameover
			MSTK_voidSetBusyWait(1000000);
			gameover();
	}

}
