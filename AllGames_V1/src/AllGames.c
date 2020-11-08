/*
 * AllGames.c
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

static u8 All_Dir=0, All_flag=0;
static u8 Y_choose=9;

static u8 ALLGamesMap[10]=
		{SNAKE , TETRIS ,ARKANOID , CARS,TICTACTOE, MEMORY,CHICHEN , PACMAN,MINSWEEPER, MAZE};

static void Input(void)
{
	if(MGPIO_u8GetPinValue(UP)==0 && Y_choose<9)
	{
		All_Dir=Dir_up;
		All_flag=1;
	}
	else if(MGPIO_u8GetPinValue(DOWN)==0 && Y_choose>0)
	{
		All_Dir=Dir_down;
		All_flag=1;
	}
//	else if(MGPIO_u8GetPinValue(LEFT)==0 && X_choose<1)
//	{
//			Dir=Dir_left;
//			All_flag=1;
//	}
//	else if(MGPIO_u8GetPinValue(RIGHT)==0 && X_choose>0)
//	{
//			Dir=Dir_right;
//			All_flag=1;
//	}
	else if(MGPIO_u8GetPinValue(CHOOSE)==0)
	{
			All_Dir=Dir_choose;
			All_flag=1;
	}
}

static void background(void)
{
	HTFT_voidFillColor(0xFFFF);

	HTFT_voidDrawString("SNAKE",85,144,0x0000);
	HTFT_voidDrawString("TETRIS",90,128,0x0000);

	HTFT_voidDrawString("ARKANOID",100,112,0x0000);
	HTFT_voidDrawString("CARS",80,96,0x0000);

	HTFT_voidDrawString("TICTACTOE",105,80,0x0000);
	HTFT_voidDrawString("MEMORY",90,64,0x0000);

	HTFT_voidDrawString("CHICHEN",95,48,0x0000);
	HTFT_voidDrawString("PACMAN",90,32,0x0000);

	HTFT_voidDrawString("MINSWEEPER",110,16,0x0000);
	HTFT_voidDrawString("MAZE",80,0,0x0000);


}
static void Sqr( u8 y , u8 clr_draw)
{
	switch(clr_draw)
	{
	case 0:
		HTFT_voidDrawRect(0, 128 , (y*16),(y*16)+16 , 0xFFFF);
		break;
	case 1:
		HTFT_voidDrawRect(0, 128 , (y*16),(y*16)+16 , 0x059F);
		break;
	default:break;
	}

	switch(y)
	{
	case 9:
		HTFT_voidDrawString("SNAKE",85,144,0x0000);
		break;
	case 8:
		HTFT_voidDrawString("TETRIS",90,128,0x0000);
		break;
	case 7:
		HTFT_voidDrawString("ARKANOID",100,112,0x0000);
		break;
	case 6:
		HTFT_voidDrawString("CARS",80,96,0x0000);
		break;
	case 5:
		HTFT_voidDrawString("TICTACTOE",105,80,0x0000);
		break;
	case 4:
		HTFT_voidDrawString("MEMORY",90,64,0x0000);
		break;
	case 3:
		HTFT_voidDrawString("CHICHEN",95,48,0x0000);
		break;
	case 2:
		HTFT_voidDrawString("PACMAN",90,32,0x0000);
		break;
	case 1:
		HTFT_voidDrawString("MINSWEEPER",110,16,0x0000);
		break;
	case 0:
		HTFT_voidDrawString("MAZE",80,0,0x0000);
		break;
	}

}

static void PLAY(void)
{
	switch(Y_choose)
		{
		case 9:
			//HTFT_voidDrawString("SNAKE",85,144,0x0000);
			Snake_Game();
			break;
		case 8:
			//HTFT_voidDrawString("TETRIS",90,128,0x0000);
			TetricsGame();
			break;
		case 7:
			//HTFT_voidDrawString("ARKANOID",100,112,0x0000);
			Arkanoid_Game();
			break;
		case 6:
			//HTFT_voidDrawString("CARS",80,96,0x0000);
			Cars_Game();
			break;
		case 5:
			//HTFT_voidDrawString("TICTACTOE",105,80,0x0000);
			XO_Game();
			break;
		case 4:
			//HTFT_voidDrawString("MEMORY",90,64,0x0000);
			Memory_Game();
			break;
		case 3:
			//HTFT_voidDrawString("CHICHEN",95,48,0x0000);
			Chichen_Game();
			break;
		case 2:
			//HTFT_voidDrawString("PACMAN",90,32,0x0000);
			PacMan_Game();
			break;
		case 1:
			//HTFT_voidDrawString("MINSWEEPER",110,16,0x0000);
			Minesweeper_Game();
			break;
		case 0:
			//HTFT_voidDrawString("MAZE",80,0,0x0000);
			Maze_Game();
			break;
		}

}

void ALL_Games(void)
{
	u8 finsh=0;
	background();
	Sqr(Y_choose,1);
	while(!finsh)
		{
				while(!All_flag)
				{
					Input();
					MSTK_voidSetBusyWait(200000);

				}
				switch(All_Dir)
				{
				case Dir_up:
					Sqr(Y_choose,0);
					Sqr(++Y_choose,1);
					All_Dir=0;
					break;
				case Dir_down:
					Sqr(Y_choose,0);
					Sqr(--Y_choose,1);
					All_Dir=0;
					break;
				case Dir_choose:
					PLAY();
					MSTK_voidSetBusyWait(2000000);
					finsh=1;
					All_Dir=0;
					break;
				default:break;
				}
				All_flag=0;
		}
}
