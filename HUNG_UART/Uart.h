#ifndef __UART_H
#define __UART_H
#include "stdint.h"
// define struct USART register
typedef struct
{
	volatile uint32_t USART_SR, USART_DR, USART_BRR, USART_CR1, USART_CR2, USART_CR3, USART_GTPR;
}USART_TypeDef;

#define USART1 ((USART_TypeDef *) 0x40013800UL)
#define USART2 ((USART_TypeDef *) 0x40004400UL)
#define USART3 ((USART_TypeDef *) 0x40004800UL)

// define bit
#define USART_CR1_UE	(1U << 13) // enable uart
#define USART_CR1_TE 	(1U << 3)
#define USART_CR1_RE	(1U << 2)


// cac bit trang thai truyen, nhan

#define USART_SR_TXE	(1U << 7)
#define USART_SR_RXNE	(1U << 5)
#define USART_SR_TC		(1U << 6)

void HUNG_USART_Init(void);
void HUNG_USART_Trans(char c);

#endif 