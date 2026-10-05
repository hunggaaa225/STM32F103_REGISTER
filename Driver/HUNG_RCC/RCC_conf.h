#ifndef __RCC_CONF_H
#define __RCC_CONF_H

#include "stdint.h"


// struct RCC register
typedef struct
{
		volatile uint32_t CR, CFGR, CIR, APB2RSTR, APB1RSTR, AHBENR, APB2ENR, APB1ENR, BDCR, CSR, AHBSTR;
} RCC_TypeDef;

//  RCC address
#define RCC ((RCC_TypeDef *) 0x40021000UL)

// bit define
// tam thoi chi dinh nghia cho GPIO va UART
// APB2ENR
#define RCC_APB2ENR_AFIOEN 		(1U << 0)
#define RCC_APB2ENR_IOPAEN 		(1U << 2)
#define RCC_APB2ENR_IOPBEN 		(1U << 3)
#define RCC_APB2ENR_IOPCEN 		(1U << 4)
#define RCC_APB2ENR_IOPDEN 		(1U << 5)
#define RCC_APB2ENR_USART1EN 	(1U << 14) // uart1
// APB1ENR
#define RCC_APB1ENR_USART2EN (1U << 17)
#define RCC_APB1ENR_USART3EN (1U << 18)
  
typedef enum
{
	HUNG_RCC_AFIO = 0,
	HUNG_RCC_GPIOA,
	HUNG_RCC_GPIOB,
	HUNG_RCC_GPIOC,
	HUNG_RCC_GPIOD,
	HUNG_RCC_USART1,
	HUNG_RCC_USART2,
	HUNG_RCC_USART3,
} HUNG_RCC_Periph_t;

void HUNG_RCC_En(HUNG_RCC_Periph_t periph);
void HUNG_RCC_Dis(HUNG_RCC_Periph_t periph);
#endif