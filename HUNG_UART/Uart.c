#include "Uart.h"
#include "gpio.h"
#include "RCC_conf.h"

// ham innit cau hinh chan gpio, clock
void HUNG_USART_Init(void)
{
	
// Default config for usart1
	// En clock
	HUNG_RCC_En(HUNG_RCC_GPIOA);
	HUNG_RCC_En(HUNG_RCC_USART1);
	// GPIO conf
	HUNG_GPIO_conf(GPIOA, 9, GPIO_MODE_OUTPUT_50, GPIO_CNF_OUT_AF_PP, GPIO_NOPULL); // TX = PA9
	HUNG_GPIO_conf(GPIOA, 10, GPIO_MODE_INPUT, GPIO_CNF_IN_FLOAT,  GPIO_NOPULL); // RX= PA10
	// BAUD RATE conf
	//USARTDIV = PCLK / (16 × baud)
	// BRR = (mantissa << 4) | fraction
	// chon baud rate = 9600 -> USARTDIV= 8 000 000 / (16 * 9600) = 52.0833
	// -> mantissa  = 52 = 0x34 ; fration = 0.0883 = 1.33
	//-> BRR = 0x341
	USART1->USART_BRR = 0x341;
	
	// bat usart
	USART1->USART_CR1 |= USART_CR1_UE;
	USART1->USART_CR1 |= USART_CR1_TE;
	USART1->USART_CR1 |= USART_CR1_RE;
} 

void HUNG_USART_Trans(char c)
{
	while(!(USART1->USART_SR & USART_SR_TXE)); // cho den khi TXE=1
	USART1->USART_DR = (uint8_t)c;
}