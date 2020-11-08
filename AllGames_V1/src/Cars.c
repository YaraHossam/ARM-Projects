/*
 * Cars.c
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

u8 Car_Dir=0, Car_flag=0;
u8 X_car=5 ,Y_car=0;
u8 Car_lose=0;
u8 road[10][4]={
		{1,1,1,0},
		{0,0,0,0},
		{0,1,1,1},
		{0,0,0,1},
		{1,1,0,1},
		{0,1,0,0},
		{0,0,1,0},
		{1,1,0,0},
		{0,0,0,1},
		{0,1,1,1}
};

void Car_Background(void)
{
	HTFT_voidFillColor(0x07E0);
	HTFT_voidDrawRect(31,95,0,159,0x3186);
	HTFT_voidDrawRect(29,31,0,159,0xFFFF);
	HTFT_voidDrawRect(95,97,0,159,0xFFFF);
}

void car_Input(void)
{
	if(MGPIO_u8GetPinValue(UP)==0)
	{
		Car_Dir=Dir_up;
		Car_flag=1;
	}
//	else if(MGPIO_u8GetPinValue(DOWN)==0)
//	{
//		Car_Dir=Dir_down;
//		Car_flag=1;
//	}
	else if(MGPIO_u8GetPinValue(LEFT)==0 && X_car<5)
	{
			Car_Dir=Dir_left;
			Car_flag=1;
	}
	else if(MGPIO_u8GetPinValue(RIGHT)==0&& X_car>2)
	{
			Car_Dir=Dir_right;
			Car_flag=1;
	}
}

void CarDraw(u8 x ,u8 y ,u16 color)
{
	u16 carbody[16]={0, 0, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 2016, 0, 0, 0};
	u16 wheels[16]={0, 0, 0, 2064, 2064, 2064, 0, 0, 2064, 2064, 2064, 0, 0, 0, 0, 0};
				for(u8 row=0 ; row<16 ; row++)
				{
						for(u8 col=0 ; col<16 ; col++)
						{
							if (GET_BIT(carbody[row],col))
								HTFT_voidDrawPixal((x*16)+col,(y*16)+row,color);
//							else if(GET_BIT(wheels[row],col))
//								HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x0000);
						}
				}
				for(u8 row=0 ; row<16 ; row++)
								{
										for(u8 col=0 ; col<16 ; col++)
										{
											if (GET_BIT(wheels[row],col))
												HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x0000);
				//							else if(GET_BIT(wheels[row],col))
				//								HTFT_voidDrawPixal((x*16)+col,(y*16)+row,0x0000);
										}
								}
}

void ClearCar(u8 x , u8 y)
{
	HTFT_voidDrawRect((x*16),(x*16)+16 , (y*16),(y*16)+16 , 0x3186);
}

void roadDraw(void)
{
	for(u8 r=0 ; r<10 ; r++)
	{
		for(u8 c=0 ; c<4 ; c++)
		{
			if(road[9-r][3-c]==1)
			{
				CarDraw(c+2,r,0x019F);
			}
		}
	}
}

void car_checklose(void)
{
	if(road[9-Y_car][3-(X_car-2)]==1)
	{
		Car_lose=1;
	}
	else if(X_car==2 && Y_car==9)
	{
		Car_lose=100;
	}
}

void Cars_Game(void)
{
	Car_Background();
	roadDraw();
	CarDraw(X_car,Y_car,0xF800);
	while(!Car_lose)
	{
			while(!Car_flag)
			{
				car_Input();
				MSTK_voidSetBusyWait(200000);

			}
			switch(Car_Dir)
			{
			case Dir_up:
				ClearCar(X_car,Y_car);
				CarDraw(X_car,++Y_car,0xF800);
				car_checklose();
				Car_Dir=0;
				break;
			case Dir_left:
				ClearCar(X_car,Y_car);
				CarDraw(++X_car,Y_car,0xF800);
				car_checklose();
				Car_Dir=0;
				break;
			case Dir_right:
				ClearCar(X_car,Y_car);
				CarDraw(--X_car,Y_car,0xF800);
				car_checklose();
				Car_Dir=0;
				break;
			default:break;
			}
			Car_flag=0;
	}

		if(Car_lose==100)
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
