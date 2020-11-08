#ifndef XO_GAME_H
#define XO_GAME_H

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

#define is_X		10
#define is_O		20

void XO_Game(void);

#endif
