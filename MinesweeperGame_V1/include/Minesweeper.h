#ifndef MINESWEEPER_GAME_H
#define MINESWEEPER_GAME_H

#define UP			GPIOA,8
#define DOWN		GPIOA,10
#define LEFT		GPIOA,11
#define RIGHT		GPIOA,9
#define OPEN_SQR	GPIOA,12
#define SAVE_SQR	GPIOA,15

#define Dir_up		10
#define Dir_down	20
#define Dir_left	30
#define Dir_right	40
#define Dir_open	50
#define Dir_save	60

#define CLOSE	10
#define OPEN	20
#define SAVE	30

void Minesweeper_Game(void);

#endif
