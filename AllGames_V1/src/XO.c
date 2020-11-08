/*
 * XO.c
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

//BLUE AND RED
u8 XO_flag=0 , XO_Dir=0;
s8 XO_x_sqr=1 , XO_y_sqr=1;
u8 finishGame=0 , countGame=0;
u8 flagPlayer=1;
volatile u8 isO=1 , choss=0;
u8 player1=0 , player2=0;

u8 fieldXO[3][3]={
		{0,0,0},
		{0,0,0},
		{0,0,0}
};

void Input(void)
{
    	if(MGPIO_u8GetPinValue(UP)==0 && XO_y_sqr<2)
		{
			XO_Dir=Dir_up;
			XO_flag=1;
		}
		else if(MGPIO_u8GetPinValue(DOWN)==0 && XO_y_sqr>0)
		{
			XO_Dir=Dir_down;
			XO_flag=1;
		}
		else if(MGPIO_u8GetPinValue(LEFT)==0 && XO_x_sqr<2)
		{
			XO_Dir=Dir_left;
			XO_flag=1;
		}
		else if(MGPIO_u8GetPinValue(RIGHT)==0 && XO_x_sqr>0)
		{
			XO_Dir=Dir_right;
			XO_flag=1;
		}
		else if(MGPIO_u8GetPinValue(CHOOSE)==0)
		{
			XO_Dir=Dir_choose;
			XO_flag=1;
		}
}

void DrawSqr(u8 x , u8 y ,u16 Color)
{
	switch(x)
	{
	case 0:
		x=18;
		break;
	case 1:
		x=50;
		break;
	case 2:
		x=82;
		break;
	default:break;
	}
	switch(y)
	{
	case 0:
		y=32;
		break;
	case 1:
		y=65;
		break;
	case 2:
		y=98;
		break;
	default:break;
	}
	HTFT_voidDrawRect( x,x+27,y,y+28, Color);
}

void InitPlayer(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawString("PLAYER 1",100,80,0xFFFF);
	HTFT_voidDrawChar('X',90,50,0xF800);
	HTFT_voidDrawString("OR",70,50,0xFFFF);
	HTFT_voidDrawChar('O',40,50,0x001F);
	while(!choss)
	{
	while(!XO_flag)
			{
				Input();
				MSTK_voidSetBusyWait(200000);
			}
	switch(XO_Dir)
	{
	case Dir_left:
		HTFT_voidDrawRect(85,105,50,65,0xFFFF);
		HTFT_voidDrawChar('X',90,50,0xF800);
		HTFT_voidDrawRect(35,55,50,65,0x0000);
		HTFT_voidDrawChar('O',40,50,0x001F);
		isO=0;
		XO_Dir=0;
		break;
	case Dir_right:
		HTFT_voidDrawRect(35,55,50,65,0xFFFF);
		HTFT_voidDrawChar('O',40,50,0x001F);
		HTFT_voidDrawRect(85,105,50,65,0x0000);
		HTFT_voidDrawChar('X',90,50,0xF800);
		isO=1;
		XO_Dir=0;
		break;
	case Dir_choose:
		choss=1;
		XO_Dir=0;
		break;
	default:break;
	}
	XO_flag=0;
	}

	switch(isO)
	{
	case 0:
		HTFT_voidFillColor(0x0000);
		HTFT_voidDrawString("PLAYER1",110,80,0xFFFF);
		HTFT_voidDrawChar('X',20,80,0xF800);
		HTFT_voidDrawString("PLAYER2",110,50,0xFFFF);
		HTFT_voidDrawChar('O',20,50,0x001F);
		player1=is_X;
		player2=is_O;
		break;
	case 1:
		HTFT_voidFillColor(0x0000);
		HTFT_voidDrawString("PLAYER1",110,80,0xFFFF);
		HTFT_voidDrawChar('O',20,80,0x001F);
		HTFT_voidDrawString("PLAYER2",110,50,0xFFFF);
		HTFT_voidDrawChar('X',20,50,0xF800);
		player1=is_O;
		player2=is_X;
		break;
	default:break;
	}

}

void Background(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawRect(45,50,30,130,0xFFFF);
	HTFT_voidDrawRect(77,82,30,130,0xFFFF);//gg
	HTFT_voidDrawRect(14,113,60,65,0xFFFF);//gg
	HTFT_voidDrawRect(14,113,93,98,0xFFFF);//g
}



void Draw_XO(u8 x , u8 y , u8 xo)
{
	u32 X_[27]={0, 0, 0, 12582936, 14680120, 7340144, 3670240, 1835456, 918400, 460544, 232960, 121856, 63488, 28672, 63488, 121856, 232960, 460544, 918400, 1835456, 3670240, 7340144, 14680120, 12582936, 0, 0, 0};
	u32 O_[27]={0, 0, 0, 261632, 524032, 786816, 1573056, 3145824, 6291504, 12582936, 12582936, 12582936, 12582936, 12582936, 12582936, 12582936, 12582936, 12582936, 6291504, 3145824, 1573056, 786816, 524032, 261632, 0, 0, 0};
	u32 *XO_;
	u16 color;
	switch(x)
		{
		case 0:
			x=18;
			break;
		case 1:
			x=50;
			break;
		case 2:
			x=82;
			break;
		default:break;
		}
		switch(y)
		{
		case 0:
			y=32;
			break;
		case 1:
			y=65;
			break;
		case 2:
			y=98;
			break;
		default:break;
		}
		switch(xo)
		{
		case is_X:
			XO_=X_;
			color=0xF800;
		    break;
		case is_O:
			XO_=O_;
			color=0x001F;
			break;
		default:break;
		}

	for(u8 row=0 ; row<27 ; row++)
	{
		for(u8 col=0 ; col<27 ; col++)
		{
			if (GET_BIT(XO_[row],col))
			{
				HTFT_voidDrawPixal(x+col,y+row,color);
			}
		}
	}
}

void clearsqr(u8 x , u8 y)
{
	DrawSqr(x,y,0x0000);
	switch(fieldXO[2-y][2-x])
	{
	case 0:
		break;
	case is_X:
		Draw_XO(x,y,is_X);
		break;
	case is_O:
		Draw_XO(x,y,is_O);
		break;
	default:break;
	}
}

void DrawIN(u8 x , u8 y)
{
	DrawSqr(x,y,0x0841);
	switch(fieldXO[2-y][2-x])
		{
		case 0:
			break;
		case is_X:
			Draw_XO(x,y,is_X);
			break;
		case is_O:
			Draw_XO(x,y,is_O);
			break;
		default:break;
		}
}

u8 checkwin(void)
{
	if((fieldXO[0][0]==fieldXO[0][1]&&fieldXO[0][1]==fieldXO[0][2] &&fieldXO[0][2]!=0) || (fieldXO[1][0]==fieldXO[1][1]&&fieldXO[1][1]==fieldXO[1][2] && fieldXO[1][2]!=0) || (fieldXO[2][0]==fieldXO[2][1]&&fieldXO[2][1]==fieldXO[2][2]&&fieldXO[2][2]!=0 ) || (fieldXO[0][0]==fieldXO[1][0]&&fieldXO[1][0]==fieldXO[2][0] && fieldXO[2][0]!=0) || (fieldXO[0][1]==fieldXO[1][1]&&fieldXO[1][1]==fieldXO[2][1] && fieldXO[2][1]!=0) || (fieldXO[0][2]==fieldXO[1][2]&&fieldXO[1][2]==fieldXO[2][2] && fieldXO[2][2]!=0) || (fieldXO[0][0]==fieldXO[1][1]&&fieldXO[1][1]==fieldXO[2][2] &&fieldXO[2][2]!=0 ) || (fieldXO[0][2]==fieldXO[1][1]&&fieldXO[1][1]==fieldXO[2][0] && fieldXO[2][0]!=0))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

u8 chooseProcess(void)
{
	if(flagPlayer==1 && fieldXO[2-XO_y_sqr][2-XO_x_sqr]==0)
	{
		fieldXO[2-XO_y_sqr][2-XO_x_sqr]=player1;
		DrawIN(XO_x_sqr,XO_y_sqr);

		if(checkwin())
		{
			HTFT_voidDrawRect(0,127,50+20,70+30,0xFFFF);
			HTFT_voidDrawString("YOU DO IT",100,80,0xFFE0);
			return 1;
		}


		flagPlayer=2;
		HTFT_voidClearDig(30,140,0x0000);
		HTFT_voidDrawNum(2,30,140,0xFFFF);
	}
	else
	{
		fieldXO[2-XO_y_sqr][2-XO_x_sqr]=player2;
		DrawIN(XO_x_sqr,XO_y_sqr);
		if(checkwin())
		{
			HTFT_voidDrawRect(0,127,50+20,70+30,0xFFFF);
			HTFT_voidDrawString("YOU DO IT",100,80,0xFFE0);
			return 1;
		}
		flagPlayer=1;
		HTFT_voidClearDig(30,140,0x0000);
		HTFT_voidDrawNum(1,30,140,0xFFFF);
	}
	return 0;


}

void XO_Game(void)
{
	InitPlayer();
	MSTK_voidSetBusyWait(200000);
	Background();
	DrawSqr(XO_x_sqr,XO_y_sqr,0x0841);
	HTFT_voidDrawString("PLAYER",100,140,0xFFFF);
	HTFT_voidDrawNum(1,30,140,0xFFFF);
	//Draw_XO(1,1,is_X);
	//Draw_XO(0,0,is_O);
	while(!finishGame)
	{
		while(!XO_flag)
		{
			Input();
			MSTK_voidSetBusyWait(200000);
		}
		switch(XO_Dir)
		{
			case Dir_up:
				clearsqr(XO_x_sqr,XO_y_sqr);
				DrawIN(XO_x_sqr,++XO_y_sqr);
				XO_Dir=0;
				break;
			case Dir_down:
				clearsqr(XO_x_sqr,XO_y_sqr);
				DrawIN(XO_x_sqr,--XO_y_sqr);
				XO_Dir=0;
				break;
			case Dir_left:
				clearsqr(XO_x_sqr,XO_y_sqr);
				DrawIN(++XO_x_sqr,XO_y_sqr);
				XO_Dir=0;
				break;
			case Dir_right:
				clearsqr(XO_x_sqr,XO_y_sqr);
				DrawIN(--XO_x_sqr,XO_y_sqr);
				XO_Dir=0;
				break;
			case Dir_choose:
				countGame++;
				if(chooseProcess())
				{
					finishGame=1;
				}
				else if(countGame==9)
				{
					finishGame=1;
					HTFT_voidDrawRect(0,127,50+20,70+30,0xFFFF);
					HTFT_voidDrawString("NO WINNER",100,80,0x0000);
				}


				XO_Dir=0;
				break;
			default:break;
		}
		XO_flag=0;
	}
}
