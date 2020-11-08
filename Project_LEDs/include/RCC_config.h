/********************************/
/* Author  : Yara Hossam        */
/* Date    : 8 AUG 2020         */
/* Version : V01                */
/********************************/
#ifndef RCC_CONFIG_H
#define RCC_CONFIG_H

/* options: RCC_HSE_CRYSTAL
			RCC_HSE_RC
			RCC_HSI
			RCC_PLL              */
#define RCC_CLOCK_TYPES  RCC_HSE_CRYSTAL


/* options: RCC_PLL_IN_HSI_DIV_2
			RCC_PLL_IN_HSE_DIV_2
			RCC_PLL_IN_HSE        */
/* Note: Select value only if you have PLL as input clock source */
#if RCC_CLOCK_TYPES == RCC_PLL
#define RCC_PLL_INPUT   RCC_PLL_IN_HSE_DIV_2
#endif

/* options 2 to 16 */
/* Note: Select value only if you have PLL as input clock source */
#if RCC_CLOCK_TYPES == RCC_PLL
#define RCC_PLL_MUL_VAL    4
#endif

#endif