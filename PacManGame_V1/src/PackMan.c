/*
 * PackMan.c
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

#include "PacMan.h"

u8 Dir=0, flag=0;
u8 Xpac =1 , Ypac=1;
u8 scour=0;
u8 Xarrimp[3] ={1,14,1},Yarrimp[3]={14,14,16} , flagsimp[3]={0};

u8 PacmanField[20][16]={
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//
		{1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1},//
		{1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},//
		{1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1},//
		{1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},//
		{1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1},//
		{1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
		{1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1},
		{1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1},//
		{1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},//
		{1,0,1,1,1,1,1,0,0,1,1,1,1,1,0,1},//
		{1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},//
		{1,1,1,0,1,0,1,1,1,1,0,1,0,1,1,1},//
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},//
		{1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1},
		{1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

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

void DrawSqr(u8 x , u8 y , u16 Color)
{

	HTFT_voidDrawRect((x*8),(x*8)+8 , (y*8),(y*8)+8 , Color);
}

void food(u8 x , u8 y)
{
	u8 Food[8]={0, 0, 0, 8, 0, 0, 0, 0};
	for(u8 row=0 ; row<8 ; row++)
	{
		if(Food[row]!=0)
			for(u8 col=0 ; col<8 ; col++)
				if (GET_BIT(Food[row],col))
					HTFT_voidDrawPixal((x*8)+col,(y*8)+row,0xF800);
	}

}

void Pacman(u8 x , u8 y)
{
	u8 Pac[8]={0, 24, 60, 126, 126, 60, 24, 0};
		for(u8 row=0 ; row<8 ; row++)
		{
			if(Pac[row]!=0)
				for(u8 col=0 ; col<8 ; col++)
					if (GET_BIT(Pac[row],col))
						HTFT_voidDrawPixal((x*8)+col,(y*8)+row,0xEFE0);
		}
}

void Imp(u8 x , u8 y ,u16 color)
{
	u8 imp[8]={0, 73, 73, 73, 127, 62, 62, 0};
			for(u8 row=0 ; row<8 ; row++)
			{
					for(u8 col=0 ; col<8 ; col++)
						if (GET_BIT(imp[row],col))
							HTFT_voidDrawPixal((x*8)+col,(y*8)+row,color);
			}
}

void FieldDraw(void)
{
	for(u8 r =0 ; r<20 ; r++)
	{
		for(u8 c =0 ; c<16 ; c++)
		{
			if(PacmanField[19-r][15-c]==1)
			{
				DrawSqr(c,r,0x001F);
			}
			else
			{
				food(c,r);
			}
		}
	}
}

void ForI(u8 x , u8 y)
{
	if(PacmanField[19-y][15-x]==0)
	{
		DrawSqr(x,y,0x0000);
		food(x,y);
	}
	else
	{
		DrawSqr(x,y,0x0000);
	}
}

void MoveImp(void)
{
	if(Yarrimp[0]>5 && flagsimp[0]==0)
	{

		ForI(Xarrimp[0],Yarrimp[0]);
		Imp(Xarrimp[0],--Yarrimp[0], 0xF81C);
		ForI(Xarrimp[1],Yarrimp[1]);
		Imp(Xarrimp[1],--Yarrimp[1], 0x07FF);
	}
	else if(Yarrimp[0]==5 ||Yarrimp[0]==14)
	{
		TOG_BIT(flagsimp[0],0);
	}
	if(Yarrimp[0]<14 && flagsimp[0]==1)
	{
		ForI(Xarrimp[0],Yarrimp[0]);
		Imp(Xarrimp[0],++Yarrimp[0], 0xF81C);
		ForI(Xarrimp[1],Yarrimp[1]);
		Imp(Xarrimp[1],++Yarrimp[1], 0x07FF);
	}
////////////////////////////////////////////////////////
	//Imp(Xarrimp[2],Yarrimp[2], 0x37E0);
	if(Xarrimp[2]>1 && flagsimp[2]==0)
		{
			ForI(Xarrimp[2],Yarrimp[2]);
			Imp(--Xarrimp[2],Yarrimp[2], 0x37E0);
		}
		else if(Xarrimp[2]==1 ||Xarrimp[2]==14)
		{
			TOG_BIT(flagsimp[2],0);
		}
		if(Xarrimp[2]<14 && flagsimp[2]==1)
		{
			ForI(Xarrimp[2],Yarrimp[2]);
			Imp(++Xarrimp[2],Yarrimp[2], 0x37E0);
		}
}

void checklose(void)
{
	if((Xpac==Xarrimp[0] && Ypac==Yarrimp[0])||(Xpac==Xarrimp[1] && Ypac==Yarrimp[1])||(Xpac==Xarrimp[2] && Ypac==Yarrimp[2]))
	{
		scour=200;
	}
}

void PacMan_Game(void)
{
	HTFT_voidFillColor(0x0000);
	FieldDraw();
	Pacman(Xpac,Ypac);
	while(scour<158)
	{

			Input();
			MSTK_voidSetBusyWait(200000);

		switch(Dir)
		{
		case Dir_up:
			if(PacmanField[19-(Ypac+1)][15-Xpac]!=1 && Ypac<19)
			{
				DrawSqr(Xpac,Ypac,0x0000);
				Pacman(Xpac,++Ypac);
				if(PacmanField[19-Ypac][15-Xpac]==0)
				{
					PacmanField[19-Ypac][15-Xpac]=5;
					scour++;
				}

			}
			checklose();
			//Dir=0;
			break;
		case Dir_down:
			if(PacmanField[19-(Ypac-1)][15-Xpac]!=1 && Ypac>0)
			{
				DrawSqr(Xpac,Ypac,0x0000);
				Pacman(Xpac,--Ypac);
				if(PacmanField[19-Ypac][15-Xpac]==0)
				{
					PacmanField[19-Ypac][15-Xpac]=5;
					scour++;
				}

			}
			checklose();
			//Dir=0;
			break;
		case Dir_left:
			if(PacmanField[19-(Ypac)][15-(Xpac+1)]!=1 && Xpac<15)
			{
				DrawSqr(Xpac,Ypac,0x0000);
				Pacman(++Xpac,Ypac);
				if(PacmanField[19-Ypac][15-Xpac]==0)
				{
					PacmanField[19-Ypac][15-Xpac]=5;
					scour++;
				}

			}
			checklose();
			//Dir=0;
			break;
		case Dir_right:
			if(PacmanField[19-(Ypac)][15-(Xpac-1)]!=1 && Xpac>0)
			{
				DrawSqr(Xpac,Ypac,0x0000);
				Pacman(--Xpac,Ypac);
				if(PacmanField[19-Ypac][15-Xpac]==0)
				{
					PacmanField[19-Ypac][15-Xpac]=5;
					scour++;
				}

			}
			checklose();
			//Dir=0;
			break;
		default:break;
		}
		MoveImp();
	}
	if(scour==158)
	{
		HTFT_voidDrawRect(0,127,50+20,70+30,0xFFFF);
		HTFT_voidDrawString("YOU DO IT",100,80,0xFFE0);
	}
	else
	{
		//gameover
		HTFT_voidDrawRect(0,127,50+20,70+30,0x0000);
		HTFT_voidDrawString("GAME OVER",100,80,0xF800);
	}
}
