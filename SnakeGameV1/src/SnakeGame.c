/*
 * Game.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Yara
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GPIO_interface.h"
#include "STK_interface.h"
#include "SPI_interface.h"

#include "TFT_interface.h"


#include "Game.h"

volatile Map Map1;
volatile Snake Snake1;
volatile Player Player1;
volatile u8 Dir=0;
volatile u32 r;
u8 pos_F_X[11]={44,64,84,14,34,104,74,24,94,54,44};
u8 pos_F_Y[11]={26,106,86,36,66,116,46,76,16,56,96};
u8 p=0;

//void fun(void)
//{
//	asm("NOP");
//}
//
//
//u8 random(void)
//{
//	return (MSTK_u32GetElapsedTime());
//}
void shift_right( u8 arr[] , s8 size)
{
	for(s8 s=size-1 ; s>=0 ; s--)
	{
		arr[s+1]=arr[s];
	}
}
//void initTail(void)
//{
//	shift_right(Snake1.TailX,10);
//		shift_right(Snake1.TailY,10);
//		Snake1.TailX[0]=Snake1.headX;
//		Snake1.TailY[0]=Snake1.headY;
//}
u8 flag=0;
void Generate_fruit(void)
{
	Map1.fruitX=pos_F_X[p];
	Map1.fruitY=pos_F_Y[p];
		p++;
	if(p>11)
	{p=0;}
//	Map1.fruitX=(random()*4)%124+4;
//	Map1.fruitY=(random()*6)%136+6;
}
void Setup(void)
{
	//to initial random function ----> srand
	//MSTK_voidIntervalPeriodic(100000,fun);

	Map1.width=124;
	Map1.hight=136;
	Generate_fruit();
	//-----------------
	Snake1.headX=Snake1.TailX[0]=4;
	Snake1.headY=Snake1.TailY[0]=16;
	Snake1.Tail_L=1;
	Snake1.TailX[1]=4;
	Snake1.TailY[1]=6;

	//----------------
	Player1.scour=0;
	Player1.lose=0;
}
void DrawHead_up(u8 x , u8 y)

{
	u16 head_up[10]={1023, 1023, 1023, 819, 819, 1023, 510, 252, 120, 48};
	u16 eye_up[10]={0, 0, 0, 132, 132, 0, 0, 0, 0, 0};
	for(u8 row=0 ; row<10 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(head_up[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,0x001F);
			}
		}
	}
	for(u8 row2=0 ; row2<10 ; row2++)
		{
			for(u8 col2=0 ; col2<10 ; col2++)
			{
				if (GET_BIT(eye_up[row2],col2))
				{
					HTFT_voidDrawPixal(x+col2,y+row2,0xFFFF);
				}
			}
		}

	//HTFT_voidDrawRect(x,x+7,y,y+7,0x001F);
}
void DrawHead_down(u8 x , u8 y)

{
	u16 head_down[10]={48, 120, 252, 510, 1023, 819, 819, 1023, 1023, 1023};
	 u16 eye_down[10]={0, 0, 0, 0, 0, 132, 132, 0, 0, 0};
	for(u8 row=0 ; row<10 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(head_down[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,0x001F);
			}
		}
	}
	for(u8 row2=0 ; row2<10 ; row2++)
		{
			for(u8 col2=0 ; col2<10 ; col2++)
			{
				if (GET_BIT(eye_down[row2],col2))
				{
					HTFT_voidDrawPixal(x+col2,y+row2,0xFFFF);
				}
			}
		}

	//HTFT_voidDrawRect(x,x+7,y,y+7,0x001F);
}
void DrawHead_left(u8 x , u8 y)

{
	u16 head_left[10]={63, 127, 231, 487, 1023, 1023, 487, 231, 127, 63};
	u16 eye_left[10]={0, 0, 24, 0, 0, 0, 0, 24, 0, 0};
	for(u8 row=0 ; row<10 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(head_left[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,0x001F);
			}
		}
	}
	for(u8 row2=0 ; row2<10 ; row2++)
		{
			for(u8 col2=0 ; col2<10 ; col2++)
			{
				if (GET_BIT(eye_left[row2],col2))
				{
					HTFT_voidDrawPixal(x+col2,y+row2,0xFFFF);
				}
			}
		}

	//HTFT_voidDrawRect(x,x+7,y,y+7,0x001F);
}
void DrawHead_right(u8 x , u8 y)

{
	u16 head_right[10]={1008, 1016, 924, 926, 1023, 1023, 926, 924, 1016, 1008};
	u16 eye_right[10]={0, 0, 96, 0, 0, 0, 0, 96, 0, 0};

	for(u8 row=0 ; row<10 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(head_right[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,0x001F);
			}
		}
	}
	for(u8 row2=0 ; row2<10 ; row2++)
		{
			for(u8 col2=0 ; col2<10 ; col2++)
			{
				if (GET_BIT(eye_right[row2],col2))
				{
					HTFT_voidDrawPixal(x+col2,y+row2,0xFFFF);
				}
			}
		}

	//HTFT_voidDrawRect(x,x+7,y,y+7,0x001F);
}
void DrawHead(u8 x , u8 y , u8 postion)
{
	switch(postion)
		{
		case Dir_up:
			DrawHead_up(x,y);
			break;
		case Dir_down:
			DrawHead_down(x,y);
			break;
		case Dir_left:
			DrawHead_left(x,y);
			break;
		case Dir_right:
			DrawHead_right(x,y);
			break;
		default:break;
		}
}
void clear_10_10(u8 x , u8 y)
{
	for(u8 row=0 ; row<10 ; row++)
		{
			for(u8 col=0 ; col<10 ; col++)
			{

					HTFT_voidDrawPixal(x+col,y+row,0b0000011111100000);
			}
		}
}
void DrawTail(u8 x , u8 y )
{
	HTFT_voidDrawRect(x,x+10,y,y+10,0x001F);
}
void DrawFruit(u8 x , u8 y )
{
	u16 letter[10]={252, 510, 1023, 1023, 1023, 1023, 510, 120, 48, 16};
	for(u8 row=0 ; row<10 ; row++)
	{
		for(u8 col=0 ; col<10 ; col++)
		{
			if (GET_BIT(letter[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,0xF800);
			}
		}
	}
}
void Draw(u8 level)
{
	HTFT_voidFillColor(0b0000011111100000);
	HTFT_voidDrawRect(0,127,136,159,0x00E0);
	HTFT_voidDrawRect(0,3,0,159,0x00E0);
	HTFT_voidDrawRect(124,127,0,159,0x00E0);
	HTFT_voidDrawRect(0,127,0,5,0x00E0);
	HTFT_voidDrawCup(110,142,0xFFE0);
	HTFT_voidDraw2Dig(Player1.scour,90,142,0xFFFF);
	HTFT_voidDrawString("LEVEL",58,142,0x0000);
	HTFT_voidDrawNum(level,5,142,0xF800);

	DrawHead(Snake1.headX,Snake1.headY,Dir_up);
	DrawTail(Snake1.TailX[1],Snake1.TailY[1]);
	DrawFruit(Map1.fruitX,Map1.fruitY);
}
void Input(void)
{
	if(MGPIO_u8GetPinValue(UP)==0)
	{
		Dir=Dir_up;
		flag=1;
	}
	else if(MGPIO_u8GetPinValue(DOWN)==0)
	{
		Dir=Dir_down;
		flag=1;
	}
	else if(MGPIO_u8GetPinValue(LEFT)==0)
	{
			Dir=Dir_left;
			flag=1;
	}
	else if(MGPIO_u8GetPinValue(RIGHT)==0)
	{
			Dir=Dir_right;
			flag=1;
	}
}
void Move(void)
{

	switch(Dir)
	{
	case Dir_up:
		clear_10_10(Snake1.TailX[Snake1.Tail_L],Snake1.TailY[Snake1.Tail_L]);
		DrawTail(Snake1.TailX[0],Snake1.TailY[0]);
		Snake1.headY+=10;
	//	DrawHead(Snake1.headX,Snake1.headY,Dir);

//		Snake1.TailX[Snake1.Tail_L]=Snake1.TailX[Snake1.Tail_L-1];
//		Snake1.TailY[Snake1.Tail_L]=Snake1.TailY[Snake1.Tail_L-1];
		break;
	case Dir_down:
		clear_10_10(Snake1.TailX[Snake1.Tail_L],Snake1.TailY[Snake1.Tail_L]);
		DrawTail(Snake1.TailX[0],Snake1.TailY[0]);
		Snake1.headY-=10;
	//	DrawHead(Snake1.headX,Snake1.headY,Dir);
//		Snake1.TailX[Snake1.Tail_L]=Snake1.TailX[Snake1.Tail_L-1];
//		Snake1.TailY[Snake1.Tail_L]=Snake1.TailY[Snake1.Tail_L-1];
//		Snake1.TailX[0]=Snake1.headX;
//		Snake1.TailY[0]=Snake1.headY;
		break;
	case Dir_left:
		clear_10_10(Snake1.TailX[Snake1.Tail_L],Snake1.TailY[Snake1.Tail_L]);
		DrawTail(Snake1.TailX[0],Snake1.TailY[0]);
		Snake1.headX+=10;
	//	DrawHead(Snake1.headX,Snake1.headY,Dir);
//		Snake1.TailX[Snake1.Tail_L]=Snake1.TailX[Snake1.Tail_L-1];
//		Snake1.TailY[Snake1.Tail_L]=Snake1.TailY[Snake1.Tail_L-1];
//		Snake1.TailX[0]=Snake1.headX;
//		Snake1.TailY[0]=Snake1.headY;
		break;
	case Dir_right:
		clear_10_10(Snake1.TailX[Snake1.Tail_L],Snake1.TailY[Snake1.Tail_L]);
		DrawTail(Snake1.TailX[0],Snake1.TailY[0]);
		Snake1.headX-=10;
	//	DrawHead(Snake1.headX,Snake1.headY,Dir);
//		Snake1.TailX[Snake1.Tail_L]=Snake1.TailX[Snake1.Tail_L-1];
//		Snake1.TailY[Snake1.Tail_L]=Snake1.TailY[Snake1.Tail_L-1];
//		Snake1.TailX[0]=Snake1.headX;
//		Snake1.TailY[0]=Snake1.headY;
		break;
	default:break;
	}
	if(Snake1.headY>=(Map1.hight-8) || Snake1.headY<=5 || Snake1.headX>=Map1.width||Snake1.headX<=3)
	{
		Player1.lose=1;
	}
	else
	{

//		Snake1.TailY=Snake1.TailX_New;
//		Snake1.TailX=Snake1.TailY_New;
		//DrawTail
		//Dir=0;
	}
	if(Snake1.headX == Map1.fruitX && Snake1.headY == Map1.fruitY)
	{
		clear_10_10(Map1.fruitX,Map1.fruitY);
		DrawHead(Snake1.headX,Snake1.headY,Dir);
		Generate_fruit();
		DrawFruit(Map1.fruitX,Map1.fruitY);
		HTFT_voidClear2Dig(80,142,0x00E0);
		Player1.scour++;
		HTFT_voidDraw2Dig(Player1.scour,80,142,0xFFFF);

		/////////////////////////////////////////////////
		DrawTail(Snake1.TailX[Snake1.Tail_L],Snake1.TailY[Snake1.Tail_L]);
		Snake1.Tail_L++;
		shift_right(Snake1.TailX,Snake1.Tail_L);
		shift_right(Snake1.TailY,Snake1.Tail_L);
		Snake1.TailX[0]=Snake1.headX;
		Snake1.TailY[0]=Snake1.headY;
//		DrawTail(Snake1.TailX[0],Snake1.TailY[0]);
//		Snake1.TailX[0]=Snake1.headX;
//		Snake1.TailY[0]=Snake1.headY;
		if(Player1.scour>5)
		{
			HTFT_voidFillColor(0xFFE0);
			HTFT_voidDrawString("UP TO LEVEL" , 110 , 100 , 0x0000);
			HTFT_voidDrawNum(2,64,80,0xF800);
			MSTK_voidSetBusyWait(1000000);
			//Setup();
			//Draw(2);
			game_2();
		}
	}
	else
	{
		DrawHead(Snake1.headX,Snake1.headY,Dir);
		shift_right(Snake1.TailX,Snake1.Tail_L);
		shift_right(Snake1.TailY,Snake1.Tail_L);
		Snake1.TailX[0]=Snake1.headX;
		Snake1.TailY[0]=Snake1.headY;
	}

}
void gameover(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawString("GAME OVER",100,80,0xF800);
}
void game_1(void)
{
	Setup();
	Draw(1);
	while(Player1.lose==0)
	{
		while(!flag)
		{
		Input();
		}
		Input();
		Move();
		MSTK_voidSetBusyWait(200000);
	}
	gameover();
}
void game_2(void)
{
	Setup();
	Draw(2);
	while(Player1.lose==0)
	{
		while(!flag)
		{
		Input();
		}
		Input();
		Move();
		MSTK_voidSetBusyWait(100000);
	}
	gameover();
}
void game_3(void)
{
	Setup();
	Draw(3);
	while(Player1.lose==0)
	{
		while(!flag)
		{
		Input();
		}
		Input();
		Move();
		MSTK_voidSetBusyWait(50000);
	}
	gameover();
}
void Snake_Game(void)
{

	if(Player1.scour>10)
	{
		game_3();
	}
	else if(Player1.scour>5)
	{
		game_2();
	}
	else
	{
		game_1();
	}

}


