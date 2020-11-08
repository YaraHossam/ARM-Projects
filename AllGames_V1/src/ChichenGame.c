/*
 * ChichenGame.c
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

u8 chich_flag=0 , chich_Dir=0;
u8 chich_scour=0;
u8 X_Rocket =3 , Y_Rocket=0;
u8 chich_lose=0;
u8 FieldChichen[8][8]={
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0}
};

u8 XarrShot=0;
u8 YarrShot=0;
s8 Xegg=2;
s8 Yegg=3;

void chich_Background(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawRect((0*16),(7*16)+16 , (8*16),(9*16)+16 , 0x3019);
	HTFT_voidDrawString("SCOUR", 110, 140,0x0000);
	HTFT_voidDraw2Dig(chich_scour, 40,140 , 0xFFFF);
	DrawRocket(X_Rocket,Y_Rocket);
	allChickens(OPEN);
}

void allChickens(u8 Draw)
{
	for(u8 y=4 ; y<8 ; y++)
		{
			for(u8 x=0 ; x<8 ; x++)
			{
				if(FieldChichen[7-y][7-x]==1)
				{
					switch(Draw)
					{
					case OPEN:
						DrawChichen(x,y);
						break;
					case CLOSE:
						CLearWing(x,y);
						break;
					default:break;
					}
				}


			}
		}
}

void chichen_Input(void)
{
    	if(MGPIO_u8GetPinValue(UP)==0)
		{
			chich_Dir=Dir_up;
			chich_flag=1;
		}
		else if(MGPIO_u8GetPinValue(LEFT)==0 && X_Rocket<7)
		{
			chich_Dir=Dir_left;
			chich_flag=1;
		}
		else if(MGPIO_u8GetPinValue(RIGHT)==0 && X_Rocket>0)
		{
			chich_Dir=Dir_right;
			chich_flag=1;
		}
}

void chichen_DrawSqr(u8 x , u8 y , u16 Color)
{
	HTFT_voidDrawRect((x*16),(x*16)+16 , (y*16),(y*16)+16 , Color);
}

void DrawChichen(u8 x , u8 y)
{
	u16 orang[16]={3696, 3696, 576, 0, 0, 0, 0, 0, 0, 0, 0, 384, 384, 0, 0, 0};
	u16 blue[16]={0, 0, 0, 0, 2016, 4080, 4080, 2016, 2016, 960, 0, 0, 0, 0, 0, 0};
	u16 white[16]={0, 0, 0, 960, 0, 14364, 28686, 28686, 63519, 63519, 64575, 25158, 576, 384, 384, 0};
	//orang
	for(u8 row=0 ; row<16 ; row++)
	{
		if(orang[row]!=0)
			for(u8 col=0 ; col<16 ; col++)
				if (GET_BIT(orang[row],col))
					HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0xFE40);

	}
	//blue
	for(u8 row=0 ; row<16 ; row++)
	{
		if(blue[row]!=0)
			for(u8 col=0 ; col<16 ; col++)
				if (GET_BIT(blue[row],col))
					HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x003F);

	}
	//white

		for(u8 row=0 ; row<16 ; row++)
		{
		if(white[row]!=0)
			for(u8 col=0 ; col<16 ; col++)
				if (GET_BIT(white[row],col))
					HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0xFFFF);

		}



}

void CLearWing(u8 x , u8 y)
{
	u16 white[16]={0, 0, 0, 0, 0, 0, 16386, 16386, 49155, 57351, 63519, 24582, 0, 0, 0, 0};
	for(u8 row=0 ; row<16 ; row++)
			{
			if(white[row]!=0)
				for(u8 col=0 ; col<16 ; col++)
					if (GET_BIT(white[row],col))
						HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x0000);

			}
}

void DrawRocket(u8 x , u8 y)
{
	u16 Rocket[16]={0, 0, 960, 8184, 16380, 32766, 13260, 960, 960, 960, 960, 2016, 960, 384, 384, 0};
		for(u8 row=0 ; row<16 ; row++)
		{
			if(Rocket[row]!=0)
				for(u8 col=0 ; col<16 ; col++)
					if (GET_BIT(Rocket[row],col))
						HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x632C);

		}
}

void Shot(u8 x , u8 y)
{
	u16 shot[16]={0, 128, 128, 128, 448, 448, 992, 992, 2032, 2032, 2032, 992, 448, 448, 128, 0};
			for(u8 row=0 ; row<16 ; row++)
			{
				if(shot[row]!=0)
					for(u8 col=0 ; col<16 ; col++)
						if (GET_BIT(shot[row],col))
							HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x3019);
			}
}

void chich_gameover(void)
{
	HTFT_voidFillColor(0x0000);
	HTFT_voidDrawString("GAME OVER",100,80,0xF800);
}

void Egg(u8 x , u8 y)
{
	u16 egg[16]={0, 0, 0, 0, 0, 384, 960, 2016, 2016, 960, 384, 0, 0, 0, 0, 0};
				for(u8 row=0 ; row<16 ; row++)
				{
					if(egg[row]!=0)
						for(u8 col=0 ; col<16 ; col++)
							if (GET_BIT(egg[row],col))
								HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0xDDE6);
				}

}

void Chichen_Game(void)
{
	chich_Background();
	while(chich_scour<32)
	{
		while(!chich_flag)
		{
			if(Yegg>0)
			{
				if(Yegg==4)
				{}
				else{
					chichen_DrawSqr(Xegg,Yegg , 0x0000);
				}

			Egg(Xegg,--Yegg);

			}
			else
			{
				if(Xegg==X_Rocket)
				{
					chich_scour=100;
					break;
				}
				else{
					chichen_DrawSqr(Xegg,Yegg , 0x0000);
					if(Xegg>=7)
					{
						Xegg=0;
					}

					Xegg++;
					Yegg=4;

				}
			}
			if(YarrShot!=0 && YarrShot<7 && FieldChichen[7-YarrShot][7-XarrShot]!=1)
			{
			chichen_DrawSqr(XarrShot,YarrShot , 0x0000);
			Shot(XarrShot, ++YarrShot);
			}
			else if(FieldChichen[7-YarrShot][7-XarrShot]==1)
			{
				chichen_DrawSqr(XarrShot,YarrShot , 0x0000);
				FieldChichen[7-YarrShot][7-XarrShot]=0;
				HTFT_voidClear2Dig(40,140 ,0x3019);
				HTFT_voidDraw2Dig(++chich_scour, 40,140 , 0xFFFF);
				YarrShot=0;
			}
			else if (YarrShot==7)
			{
				chichen_DrawSqr(XarrShot,YarrShot , 0x0000);
			}


			chichen_Input();
			MSTK_voidSetBusyWait(200000);
		}
		switch(chich_Dir)
		{
		case Dir_up:
				XarrShot=X_Rocket;
				YarrShot=Y_Rocket+1;
				Shot(XarrShot, YarrShot);

			chich_Dir=0;
			break;
		case Dir_left:
			chichen_DrawSqr(X_Rocket,Y_Rocket , 0x0000);
			DrawRocket(++X_Rocket,Y_Rocket);
			chich_Dir=0;
			break;
		case Dir_right:
			chichen_DrawSqr(X_Rocket,Y_Rocket , 0x0000);
			DrawRocket(--X_Rocket,Y_Rocket);
			chich_Dir=0;
			break;
		default:break;
		}
		chich_flag=0;
	}
	if(chich_scour==32)
	{
	HTFT_voidDrawRect(0,127,50+20,70+30,0xFFFF);
		HTFT_voidDrawString("YOU DO IT",100,80,0xFFE0);
	}
	else
	{
		chich_gameover();
	}

}
