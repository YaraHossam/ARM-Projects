#ifndef	ALL_GAMES_H
#define	ALL_GAMES_H

#define UP			GPIOA,8
#define DOWN		GPIOA,10
#define LEFT		GPIOA,11
#define RIGHT		GPIOA,9
#define CHOOSE		GPIOA,12
#define SAVE_SQR	GPIOA,15
#define OPEN_SQR	GPIOA,12


#define Dir_up		10
#define Dir_down	20
#define Dir_left	30
#define Dir_right	40
#define Dir_choose	50
#define Dir_save	60
#define Dir_open	50

#define CLOSE	10
#define OPEN	20
#define SAVE	30

#define DRAW	1
#define CLEAR 	2

#define Shape_Icecream	1
#define Shape_FlagSh	2
#define Shape_treeleave	3
#define Shape_Crown		4

#define on	10
#define off	20

#define SNAKE 		1
#define TETRIS		2
#define ARKANOID 	3
#define CARS		4
#define TICTACTOE	5
#define MEMORY		6
#define CHICHEN 	7
#define PACMAN		8
#define MAZE  		9
#define MINSWEEPER	10

#define Shap_I		0
#define Shap_L		1
#define Shap_Z		2
#define Shap_T		3

#define Color_I		0xF800 //red
#define Color_L		0x07E0 //Green
#define Color_Z		0xFFE0 //yello
#define Color_T		0xFFFF //white

#define is_X		10
#define is_O		20

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

void ALL_Games(void);

void Arkanoid_Game(void);
void Cars_Game(void);
void Chichen_Game(void);
void Maze_Game(void);
void Memory_Game(void);

void Minesweeper_Game(void);
void PacMan_Game(void);
void Snake_Game(void);
void TetricsGame(void);
void XO_Game(void);

#endif
