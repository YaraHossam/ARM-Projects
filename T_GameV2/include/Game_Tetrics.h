#ifndef GAME_TERTICS_H
#define GAME_TERTICS_H

#define UP			GPIOA,8
#define DOWN		GPIOA,10
#define LEFT		GPIOA,11
#define RIGHT		GPIOA,9

#define Dir_up  10
#define Dir_down  20
#define Dir_left  30
#define Dir_right  40

#define Shap_I		0
#define Shap_L		1
#define Shap_Z		2
#define Shap_T		3

#define Color_I		0xF800 //red
#define Color_L		0x07E0 //Green
#define Color_Z		0xFFE0 //yello
#define Color_T		0xFFFF //white

void TetricsGame(void);

#endif
