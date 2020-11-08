/*
 * MazeGame.c
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

#include "AllGames.h"

u8 maze_win=0;
u8 maze_Dir=0, maze_flag=0;
u8 Xcir=0 , Ycir=0;

u8 MazeField[10][8]={
		{0,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0},
		{1,1,1,1,1,0,1,1},
		{0,0,0,0,0,0,0,0},
		{0,1,1,1,1,1,0,0},
		{0,0,0,0,1,1,1,0},
		{1,1,1,0,0,0,0,0},
		{1,0,0,0,1,1,1,1},
		{1,0,1,1,1,0,0,0},
		{1,0,0,0,0,0,1,0}
};

void maze_DrawSqr(u8 x , u8 y , u16 Color)
{

	HTFT_voidDrawRect((x*16),(x*16)+16 , (y*16),(y*16)+16 , Color);
}

void CirDraw(u8 x , u8 y )
{
	u16 egg[16]={0, 0, 384, 960, 4080, 4080, 8184, 16380, 16380, 8184, 4080, 4080, 960, 384, 0, 0};
					for(u8 row=0 ; row<16 ; row++)
					{
						if(egg[row]!=0)
							for(u8 col=0 ; col<16 ; col++)
								if (GET_BIT(egg[row],col))
									HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0xF800);
					}
}

void EndDraw(u8 x , u8 y )
{
	u16 ero[16]={0, 0, 128, 128, 128, 128, 128, 128, 8188, 4088, 2032, 992, 448, 128, 0, 0};
					for(u8 row=0 ; row<16 ; row++)
					{
						if(ero[row]!=0)
							for(u8 col=0 ; col<16 ; col++)
								if (GET_BIT(ero[row],col))
									HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x0000);
					}
}

void maze_Input(void)
{
	if(MGPIO_u8GetPinValue(UP)==0)
	{
		maze_Dir=Dir_up;
		maze_flag=1;
	}
	else if(MGPIO_u8GetPinValue(DOWN)==0)
	{
		maze_Dir=Dir_down;
		maze_flag=1;
	}
	else if(MGPIO_u8GetPinValue(LEFT)==0)
	{
			maze_Dir=Dir_left;
			maze_flag=1;
	}
	else if(MGPIO_u8GetPinValue(RIGHT)==0)
	{
			maze_Dir=Dir_right;
			maze_flag=1;
	}
}

void MazeDraw(void)
{
	for(u8 r =0 ; r<10 ; r++)
	{
		for(u8 c =0 ; c<8 ; c++)
		{
			if(MazeField[9-r][7-c]==1)
			{
				maze_DrawSqr(c,r,0x0000);
			}
		}
	}
}

void maze_Background(void)
{

	HTFT_voidFillColor(0xFF60);

}

void maze_checkwin(void)
{
	if(Xcir==7 && Ycir==9)
	{
		maze_win=1;
	}
}

void Maze_Game(void)
{
	maze_Background();
	MazeDraw();
	EndDraw(7,9);
	CirDraw(0,0);

	while(!maze_win)
	{
		while(!maze_flag)
		{
			maze_Input();
			MSTK_voidSetBusyWait(200000);
		}
		switch(maze_Dir)
		{
		case Dir_up:
			if(MazeField[9-(Ycir+1)][7-Xcir]!=1 && Ycir<9)
			{
				maze_DrawSqr(Xcir,Ycir,0xFF60);
				CirDraw(Xcir,++Ycir);
			}
			maze_checkwin();
			maze_Dir=0;
			break;
		case Dir_down:
			if(MazeField[9-(Ycir-1)][7-Xcir]!=1 && Ycir>0)
			{
				maze_DrawSqr(Xcir,Ycir,0xFF60);
				CirDraw(Xcir,--Ycir);
			}
			maze_checkwin();
			maze_Dir=0;
			break;
		case Dir_left:
			if(MazeField[9-(Ycir)][7-(Xcir+1)]!=1 && Xcir<7)
			{
				maze_DrawSqr(Xcir,Ycir,0xFF60);
				CirDraw(++Xcir,Ycir);
			}
			maze_checkwin();
			maze_Dir=0;
			break;
		case Dir_right:
			if(MazeField[9-(Ycir)][7-(Xcir-1)]!=1 && Xcir>0)
			{
				maze_DrawSqr(Xcir,Ycir,0xFF60);
				CirDraw(--Xcir,Ycir);
			}
			maze_checkwin();
			maze_Dir=0;
			break;
		default:break;
		}
		maze_flag=0;
	}
	HTFT_voidDrawRect(0,127,50+20,70+30,0xFFFF);
		HTFT_voidDrawString("YOU DO IT",100,80,0xFFE0);
}
