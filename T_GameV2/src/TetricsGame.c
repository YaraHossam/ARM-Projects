/*
 * Game.c
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

#include "Game_Tetrics.h"

const u8 R = 10;
const u8 C = 8;

u8 field[10][8]={
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}};

u8 Dir=0;
u8 flag=0;
u8 lose=0;

u8 Max_Y=0;
s8 X_move =4;
s8 Y_move =10;
u8 count=0;
u8 shap_currant[4]={Shap_I,Shap_L,Shap_Z,Shap_T};
u16 color_shap_cur[4]={Color_L,Color_I,Color_T,Color_Z};

u8 figures[4][9] =
{
//  0,1,2,3,4,5,6,7,8
   {1,0,0,1,0,0,1,0,0}, // |
   {1,1,1,0,0,1,0,0,1}, // L
   {0,0,1,1,1,1,1,0,0}, // Z
   {0,1,0,0,1,0,1,1,1}// T
};

void rotat_Shap(u8 id,s8 x_center , s8 y_center , u16 Color)
{
	u8 tmp;
	tmp=figures[id][0];
	figures[id][0]=figures[id][6];
	figures[id][6]=figures[id][8];
	figures[id][8]=figures[id][2];
	figures[id][2]=tmp;
	tmp=figures[id][1];
	figures[id][1]=figures[id][3];
	figures[id][3]=figures[id][7];
	figures[id][7]=figures[id][5];
	figures[id][5]=tmp;

	ClearShap_ro( x_center , y_center);
	DrawShap(id , x_center , y_center-1, Color);
}

void Input(void)
{
	if(MGPIO_u8GetPinValue(UP)==0)
	{
		Dir=Dir_up;
		flag=1;
	}
//	else if(MGPIO_u8GetPinValue(DOWN)==0)
//	{
//		Dir=Dir_down;
//		flag=1;
//	}
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

void Background(void)
{
	u16 color ;
	u8 x=0;
	for(u8 row= 0 ; row < 10 ; row ++)
	{
		for(u8 col =0 ; col < 8 ; col++)
		{
			if(x==0)
			{
				color=0x0019;
				x=1;
			}
			else
			{
				color=0x0006;
				x=0;
			}

			HTFT_voidDrawRect(col*16,(col*16)+16 , row*16,(row*16)+16 , color);
		}
		TOG_BIT(x,0);
	}
	//HTFT_voidDrawRect()
}

void DrawSqr(u8 x , u8 y , u16 Color)
{

	HTFT_voidDrawRect((x*16)+2,(x*16)+16-2 , (y*16)+2,(y*16)+16-2 , Color);
}

void DrawShap(u8 id , s8 x_center , s8 y_center , u16 Color)
{
	s8 X_Point =-1 , Y_Point=-1;
	u8 i =0;
	for(u8 r = 0 ; r<3 ; r++)
	{
		//Y_Point+=y_center;
		X_Point =-1;
		for(u8 c = 0 ; c<3 ; c++)
		{
			//X_Point+=x_center;
			if(figures[id][i]==1)
			{
				DrawSqr(x_center+X_Point,y_center+Y_Point,Color);
			}
			i++;
			X_Point++;
		}
		Y_Point++;
	}
}

void ClearShap( u8 id, s8 x_center , s8 y_center)
{
	s8 X_Point =-1 , Y_Point=-1;
	u8 i =0;
		for(u8 r = 0 ; r<3 ; r++)
		{
			//Y_Point+=y_center;
			X_Point =-1;
			for(u8 c = 0 ; c<3 ; c++)
			{
				//X_Point+=x_center;
				if(figures[id][i]==1)
							{
					if(((y_center+Y_Point)%2==0 && (x_center+X_Point)%2==0)||((y_center+Y_Point)%2!=0 && (x_center+X_Point)%2!=0))
					{
						DrawSqr(x_center+X_Point,y_center+Y_Point,0x0019);
					}
					else
					{
						DrawSqr(x_center+X_Point,y_center+Y_Point,0x0006);
					}
							}
				i++;
				X_Point++;
			}
			Y_Point++;
		}
}
void ClearShap_ro(s8 x_center , s8 y_center)
{
	s8 X_Point =-1 , Y_Point=-1;

			for(u8 r = 0 ; r<3 ; r++)
			{
				//Y_Point+=y_center;
				X_Point =-1;
				for(u8 c = 0 ; c<3 ; c++)
				{
					//X_Point+=x_center;

						if(((y_center+Y_Point)%2==0 && (x_center+X_Point)%2==0)||((y_center+Y_Point)%2!=0 && (x_center+X_Point)%2!=0))
						{
							DrawSqr(x_center+X_Point,y_center+Y_Point,0x0019);
						}
						else
						{
							DrawSqr(x_center+X_Point,y_center+Y_Point,0x0006);
						}


					X_Point++;
				}
				Y_Point++;
			}
}
void Shift_Right(u8 id , s8 x_center , s8 y_center , u16 Color)
{
	ClearShap( id ,x_center , y_center);
	DrawShap(id , x_center-1 , y_center, Color);
}
void Shift_Left(u8 id , s8 x_center , s8 y_center , u16 Color)
{
	ClearShap(id , x_center , y_center);
	DrawShap(id , x_center+1 , y_center, Color);
}
void Shift_Down(u8 id , s8 x_center , s8 y_center , u16 Color)
{
	ClearShap(id ,  x_center , y_center);
	DrawShap(id , x_center , y_center-1, Color);
}

void check_Lines(u8 id , s8 x_center , s8 y_center)
{
	s8 X_Point =-1 , Y_Point=-1;
		u8 i =0;
		for(u8 r = 0 ; r<3 ; r++)
		{
			//Y_Point+=y_center;
			X_Point =-1;
			for(u8 c = 0 ; c<3 ; c++)
			{
				//X_Point+=x_center;
				if(figures[id][i]==1)
				{
					field[y_center+Y_Point][x_center+X_Point]=1;
				}
				else
				{
					field[y_center+Y_Point][x_center+X_Point]=0;
				}
				i++;
				X_Point++;
			}
			Y_Point++;
		}
}
u8 Last_line(u8 *arr , u8 from , u8 to)
{
	u8 res=0;
	for(u8 k =from ; k < to ; k++)
	{
		res=(res<<1)|arr[k];
	}
	return res;
}

u8 check(void)
{
	s8 X_Point =-1 , Y_Point=-1;
		u8 i =0;
		for(u8 r = 0 ; r<3 ; r++)
		{
			//Y_Point+=y_center;
			X_Point =-1;
			for(u8 c = 0 ; c<3 ; c++)
			{
				//X_Point+=x_center;
				if(figures[shap_currant[count]][i]==1 && field[Y_move-1+Y_Point][X_move+X_Point]==1)
				{
					return 0;
					//DrawSqr(x_center+X_Point,y_center+Y_Point,Color);
				}
				i++;
				X_Point++;
			}
			Y_Point++;
		}
		return 1;
}

void Move(void)
{


	switch(Dir)
	{
	case Dir_up:
		//rotate
		rotat_Shap(shap_currant[count],X_move , Y_move,color_shap_cur[count]);
		Dir=0;
		break;
	case Dir_left:
		//shift Left
		Shift_Left(shap_currant[count],X_move , Y_move,color_shap_cur[count]);
		Dir=0;
		X_move++;
		break;
	case Dir_right:
		//shift right
		Shift_Right(shap_currant[count],X_move , Y_move,color_shap_cur[count]);
		Dir=0;
		X_move--;
		break;
	default:break;
	}

	//u8 r =Last_line(figures[shap_currant[count]] , 0 , 3) & (Last_line(field[Y_move],X_move-1,X_move+1));
	//check();
	if((Y_move-1)<= 0||check()==0 )
	{
		check_Lines(shap_currant[count],X_move , Y_move);
		if(count<3)
		{
			count++;
		}
		else
		{
			count=0;
		}

		X_move =4;
		Y_move =10;
		Max_Y++;
	}
	else{
	Shift_Down(shap_currant[count], X_move,Y_move--, color_shap_cur[count]);
	}
	if((Max_Y)>= 10)
	{
		lose=1;
	}

}

void gameover(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawString("GAME OVER",100,80,0xF800);
}

void TetricsGame(void)
{

	Background();
	while(!lose)
	{
		while(!flag)
		{
			Input();
			Dir=0;
		}
		Input();
		Move();
		MSTK_voidSetBusyWait(200000);

	}
	gameover();

}

