#ifndef MEMORY_GAME_H
#define MEMORY_GAME_H

#define UP			GPIOA,8
#define DOWN		GPIOA,10
#define LEFT		GPIOA,11
#define RIGHT		GPIOA,9
#define CHOOSE		GPIOA,12
//#define SAVE_SQR	GPIOA,15

#define Dir_up		10
#define Dir_down	20
#define Dir_left	30
#define Dir_right	40
#define Dir_choose	50
//#define Dir_save	60

#define DRAW	1
#define CLEAR 	2

#define Shape_Icecream	1
#define Shape_FlagSh	2
#define Shape_treeleave	3
#define Shape_Crown		4

#define on	10
#define off	20

void Memory_Game(void);


#endif
