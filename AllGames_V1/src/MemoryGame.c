/*
 * MemoryGame.c
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

u8 Mem_flag=0 , Mem_Dir=0;
s8 Mem_x_sqr=0 , Mem_y_sqr=0;
u8 choose=0; ;
u8 Xopen,Yopen , REMAIND=4;

u8 fieldMemory[3][3]={
		{Shape_Icecream,Shape_FlagSh,Shape_Crown},
		{Shape_treeleave,Shape_Crown,Shape_Icecream},
		{0,Shape_FlagSh,Shape_treeleave}
};

u8 fieldMemory_onoff[3][3]={
		{off,off,off},
		{off,off,off},
		{off,off,off}
};

void rotat_Shap(void)
{
	u8 tmp;
	tmp=fieldMemory[0][0];
	fieldMemory[0][0]=fieldMemory[0][2];
	fieldMemory[0][2]=fieldMemory[2][2];
	fieldMemory[2][2]=fieldMemory[2][0];
	fieldMemory[2][0]=fieldMemory[1][1];
	fieldMemory[1][1]=tmp;

	tmp=fieldMemory[0][1];
	fieldMemory[0][1]=fieldMemory[1][2];
	fieldMemory[1][2]=fieldMemory[2][1];
	fieldMemory[2][1]=fieldMemory[1][0];
	fieldMemory[1][0]=tmp;

}

void Mem_Background(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawRect(45,50,30,130,0xFFFF);
	HTFT_voidDrawRect(77,82,30,130,0xFFFF);//gg
	HTFT_voidDrawRect(14,113,60,65,0xFFFF);//gg
	HTFT_voidDrawRect(14,113,93,98,0xFFFF);//g
}

void Mem_DrawSqr(u8 x , u8 y ,u16 Color)
{
	changeXY(&x,&y);
	HTFT_voidDrawRect( x,x+27,y,y+28, Color);
}

void changeXY(u8* x ,u8* y )
{
	switch(*x)
		{
		case 0:
			*x=18;
			break;
		case 1:
			*x=50;
			break;
		case 2:
			*x=82;
			break;
		default:break;
		}
		switch(*y)
		{
		case 0:
			*y=32;
			break;
		case 1:
			*y=65;
			break;
		case 2:
			*y=98;
			break;
		default:break;
		}
}

void EmtySqr(u8 x , u8 y , u8 caseof)
{
	switch(caseof)
			{
			case DRAW:
				Mem_DrawSqr(x,y,0x0841);
				break;
			case CLEAR:
				Mem_DrawSqr(x,y,0x0000);
				break;
			default:break;
			}
}

void Qustion(u8 x , u8 y , u8 caseof)
{
	changeXY(&x,&y);
	u32 Qus[27]={0, 0, 12288, 12288, 0, 0, 0, 12288, 12288, 12288, 12288, 14336, 7168, 3584, 1792, 384, 384, 384, 384, 384, 393600, 393600, 197376, 130560, 64512, 0, 0};
	EmtySqr(x,y,caseof);
	for(u8 row=0 ; row<27 ; row++)
		{
		if(Qus[row]!=0)
			for(u8 col=0 ; col<27 ; col++)
			{
				if (GET_BIT(Qus[row],col))
				{
					HTFT_voidDrawPixal(x+col,y+row,0xF000);
				}
			}
		}

}

void Icecream(u8 x , u8 y , u8 caseof)
{
	changeXY(&x,&y);
	u32 quno[27]={0, 0, 16384, 57344, 126976, 260096, 260096, 523264, 523264, 1048064, 1048064, 1048064, 1048064, 2096896, 2096896, 2096896, 2096896, 2096896, 2096896, 0, 0, 0, 0, 0, 0, 0, 0};
	u32 pink[27]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14336, 31744, 65024, 65024, 31744, 14336, 0, 0};
	u32 white[27]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 917504, 2031616, 4161536, 4161536, 2031616, 917504, 0, 0};
	u32 brown[27]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 57344, 126976, 260096, 260096, 126976, 57344, 0};
	EmtySqr(x,y,caseof);
		//quno
		for(u8 row=0 ; row<27 ; row++)
			{
			if(quno[row]!=0)
				for(u8 col=0 ; col<27 ; col++)
				{
					if (GET_BIT(quno[row],col))
					{
						HTFT_voidDrawPixal(x+col,y+row,0xE5C2);
					}
				}
			}
		//brown
		for(u8 row=0 ; row<27 ; row++)
		{
			if(brown[row]!=0)
				for(u8 col=0 ; col<27 ; col++)
					if (GET_BIT(brown[row],col))
						HTFT_voidDrawPixal(x+col,y+row,0xA50D);

		}
		//white
		for(u8 row=0 ; row<27 ; row++)
		{
			if(white[row]!=0)
				for(u8 col=0 ; col<27 ; col++)
					if (GET_BIT(white[row],col))
						HTFT_voidDrawPixal(x+col,y+row,0xFFFF);

		}
		//pink
		for(u8 row=0 ; row<27 ; row++)
		{
			if(pink[row]!=0)
				for(u8 col=0 ; col<27 ; col++)
					if (GET_BIT(pink[row],col))
						HTFT_voidDrawPixal(x+col,y+row,0xF82E);

		}

}

void FlagSh(u8 x , u8 y , u8 caseof)
{
	changeXY(&x,&y);
	u32 Leg[27]={0, 0, 1008, 480, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 192, 448, 0, 0};
	u32 flagarray[27]={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 768, 3840, 16128, 65280, 261888, 1048320, 4194048, 2096896, 1048320, 261888, 65280, 16128, 3840, 512, 0, 0};

	EmtySqr(x,y,caseof);
		//leg
		for(u8 row=0 ; row<27 ; row++)
			{
			if(Leg[row]!=0)
				for(u8 col=0 ; col<27 ; col++)
					if (GET_BIT(Leg[row],col))
						HTFT_voidDrawPixal(x+col,y+row,0xFFFF);
			}
		//flag
		for(u8 row=0 ; row<27 ; row++)
		{
			if(flagarray[row]!=0)
				for(u8 col=0 ; col<27 ; col++)
					if (GET_BIT(flagarray[row],col))
						HTFT_voidDrawPixal(x+col,y+row,0xF000);
		}
}

void treeleave(u8 x , u8 y , u8 caseof)
{
	changeXY(&x,&y);
	u32 tree[27]={0, 0, 0, 0, 0, 16252928, 25952256, 50724864, 33815552, 261632, 524032, 483200, 505792, 482272, 519648, 489200, 506864, 515568, 257776, 128880, 65456, 16368, 4080, 0, 0, 0, 0};
	EmtySqr(x,y,caseof);
			//tree leave
			for(u8 row=0 ; row<27 ; row++)
				{
				if(tree[row]!=0)
					for(u8 col=0 ; col<27 ; col++)
						if (GET_BIT(tree[row],col))
							HTFT_voidDrawPixal(x+col,y+row,0x07E0);
				}
}

void Crown(u8 x , u8 y , u8 caseof)
{
	changeXY(&x,&y);
	u32 crown[27]={0, 0, 4194272, 4194272, 4194272, 4194272, 4194272, 4194272, 4186080, 4194272, 4194272, 4194272, 4127712, 4194272, 4194272, 4194272, 4194272, 4062688, 3733728, 3174496, 2105376, 2105376, 7368816, 5263440, 7368816, 2105376, 0};

	EmtySqr(x,y,caseof);
				//tree leave
				for(u8 row=0 ; row<27 ; row++)
					{
					if(crown[row]!=0)
						for(u8 col=0 ; col<27 ; col++)
							if (GET_BIT(crown[row],col))
								HTFT_voidDrawPixal(x+col,y+row,0xEFC0);
					}
}

void DrawINsqr(u8 x , u8 y ,u8 caseof )
{
	if(fieldMemory_onoff[2-y][2-x]==on)
	{
	switch(fieldMemory[2-y][2-x])
	{
	case 0:
		EmtySqr(x,y,caseof);
		break;
	case Shape_Icecream:
		Icecream(x,y,caseof);
		break;
	case Shape_FlagSh:
		FlagSh(x,y,caseof);
		break;
	case Shape_treeleave:
		treeleave(x,y,caseof);
		break;
	case Shape_Crown:
		Crown(x,y,caseof);
		break;
	default:break;
	}
	}
	else
	{
		Qustion(x,y,caseof);
	}
}

void DrawMemoryMap(void)
{
	for(u8 r=0 ; r<3 ; r++)
	{
		for(u8 c=0 ; c<3 ; c++)
		{
			DrawINsqr(c,r,CLEAR);
		}
	}
}

void AllMapIs(u8 status)
{
	switch(status)
	{
	case on:
		for(u8 r=0 ; r<3 ; r++)
			for(u8 c=0 ; c<3 ; c++)
				fieldMemory_onoff[r][c]=on;
		break;
	case off:
		for(u8 r=0 ; r<3 ; r++)
			for(u8 c=0 ; c<3 ; c++)
				fieldMemory_onoff[r][c]=off;
		break;
	default:break;
	}
}

void Mem_Input(void)
{
    	if(MGPIO_u8GetPinValue(UP)==0 && Mem_y_sqr<2)
		{
			Mem_Dir=Dir_up;
			Mem_flag=1;
		}
		else if(MGPIO_u8GetPinValue(DOWN)==0 && Mem_y_sqr>0)
		{
			Mem_Dir=Dir_down;
			Mem_flag=1;
		}
		else if(MGPIO_u8GetPinValue(LEFT)==0 && Mem_x_sqr<2)
		{
			Mem_Dir=Dir_left;
			Mem_flag=1;
		}
		else if(MGPIO_u8GetPinValue(RIGHT)==0 && Mem_x_sqr>0)
		{
			Mem_Dir=Dir_right;
			Mem_flag=1;
		}
		else if(MGPIO_u8GetPinValue(CHOOSE)==0 && fieldMemory_onoff[2-Mem_y_sqr][2-Mem_x_sqr]==off)
		{
			Mem_Dir=Dir_choose;
			Mem_flag=1;
		}
}

void ChooseProcess(void)
{
	 fieldMemory_onoff[2-Mem_y_sqr][2-Mem_x_sqr]=on;
	 DrawINsqr(Mem_x_sqr,Mem_y_sqr,DRAW);

	if(choose == 0)
	{
		Xopen=Mem_x_sqr;
		Yopen=Mem_y_sqr;
		choose = 1;
	}
	else
	{
		if(fieldMemory[2-Yopen][2-Xopen]!=fieldMemory[2-Mem_y_sqr][2-Mem_x_sqr])
		{
			MSTK_voidSetBusyWait(1000000);//wait
			fieldMemory_onoff[2-Mem_y_sqr][2-Mem_x_sqr]=off;
			DrawINsqr(Mem_x_sqr,Mem_y_sqr,DRAW);
		}
		else
		{
			REMAIND--;
			HTFT_voidClearDig(30,140,0x0000);
			HTFT_voidDrawNum(REMAIND,30,140,0xF800);
			choose = 0;
		}
	}
}

void Memory_Game(void)
{
	Mem_Background();
	HTFT_voidDrawString("REMAIND",100,140,0xFFFF);
	HTFT_voidDrawNum(REMAIND,30,140,0xF800);
	AllMapIs(on);//all Map is on
	DrawMemoryMap();
	MSTK_voidSetBusyWait(2000000);//wait
	AllMapIs(off);//all Map is off
	DrawMemoryMap();
	DrawINsqr(Mem_x_sqr,Mem_y_sqr,DRAW);
	while(REMAIND!=0)
		{
			while(!Mem_flag)
			{
				Mem_Input();
				MSTK_voidSetBusyWait(200000);
			}
			switch(Mem_Dir)
			{
				case Dir_up:
					DrawINsqr(Mem_x_sqr,Mem_y_sqr,CLEAR);
					DrawINsqr(Mem_x_sqr,++Mem_y_sqr,DRAW);
					Mem_Dir=0;
					break;
				case Dir_down:
					DrawINsqr(Mem_x_sqr,Mem_y_sqr,CLEAR);
					DrawINsqr(Mem_x_sqr,--Mem_y_sqr,DRAW);
					Mem_Dir=0;
					break;
				case Dir_left:
					DrawINsqr(Mem_x_sqr,Mem_y_sqr,CLEAR);
					DrawINsqr(++Mem_x_sqr,Mem_y_sqr,DRAW);
					Mem_Dir=0;
					break;
				case Dir_right:
					DrawINsqr(Mem_x_sqr,Mem_y_sqr,CLEAR);
					DrawINsqr(--Mem_x_sqr,Mem_y_sqr,DRAW);
					Mem_Dir=0;
					break;
				case Dir_choose:
					ChooseProcess();
					Mem_Dir=0;
					break;
				default:break;
			}
			Mem_flag=0;
		}
	HTFT_voidDrawRect(0,127,50+20,70+30,0xFFFF);
	HTFT_voidDrawString("YOU DO IT",100,80,0xFFE0);
}
