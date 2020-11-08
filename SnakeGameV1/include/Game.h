#ifndef GAME_H
#define GAME_H

#define UP			GPIOA,8
#define DOWN		GPIOA,10
#define LEFT		GPIOA,11
#define RIGHT		GPIOA,9

#define Dir_up  10
#define Dir_down  20
#define Dir_left  30
#define Dir_right  40


typedef struct
{
	u8 width ;
	u8 hight ;
	u8 fruitX ;
	u8 fruitY ;
}Map;

typedef struct
{
	u8 headX ;
	u8 headY ;
	u8 Tail_L ;
	u8 TailX[10];
	u8 TailY[10];
}Snake;

typedef struct
{
	u8 scour ;
	u8 lose;
}Player;

void Snake_Game(void);

#endif
