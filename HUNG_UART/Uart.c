#include "Uart.h"
#include "gpio.h"
#include "RCC_conf.h"

// ham innit cau hinh chan gpio, clock
void HUNG_USART_Init(USART_TypeDef *USARTx)
{
	if( USARTx == USART1)
		{
// Default config for usart1
	// En clock
		HUNG_RCC_En(HUNG_RCC_GPIOA);
		HUNG_RCC_En(HUNG_RCC_USART1);
		// GPIO conf
		HUNG_GPIO_conf(GPIOA, 9, GPIO_MODE_OUTPUT_50, GPIO_CNF_OUT_AF_PP, GPIO_NOPULL); // TX = PA9
		HUNG_GPIO_conf(GPIOA, 10, GPIO_MODE_INPUT, GPIO_CNF_IN_FLOAT,  GPIO_NOPULL); 		// RX= PA10
		}
		
	if( USARTx == USART2)
		{
		// En clock
			HUNG_RCC_En(HUNG_RCC_GPIOA);
			HUNG_RCC_En(HUNG_RCC_USART2);
			// GPIO conf
			HUNG_GPIO_conf(GPIOA, 2, GPIO_MODE_OUTPUT_50, GPIO_CNF_OUT_AF_PP, GPIO_NOPULL); // TX = PA2
			HUNG_GPIO_conf(GPIOA, 3, GPIO_MODE_INPUT, GPIO_CNF_IN_FLOAT,  GPIO_NOPULL); 		// RX= PA3
		}
		
		if( USARTx == USART3)
		{
		// En clock
			HUNG_RCC_En(HUNG_RCC_GPIOB);
			HUNG_RCC_En(HUNG_RCC_USART3);
			// GPIO conf
			HUNG_GPIO_conf(GPIOB, 10, GPIO_MODE_OUTPUT_50, GPIO_CNF_OUT_AF_PP, GPIO_NOPULL); 	// TX = PB10
			HUNG_GPIO_conf(GPIOB, 11, GPIO_MODE_INPUT, GPIO_CNF_IN_FLOAT,  GPIO_NOPULL); 			// RX= PB11
		}
		
	// BAUD RATE conf
	//USARTDIV = PCLK / (16 × baud)
	// BRR = (mantissa << 4) | fraction
	// chon baud rate = 9600 -> USARTDIV= 8 000 000 / (16 * 9600) = 52.0833
	// -> mantissa  = 52 = 0x34 ; fration = 0.0883 = 1.33
	//-> BRR = 0x341
	USARTx->USART_BRR = 0x341;
	
	// bat usart
	USARTx->USART_CR1 |= USART_CR1_UE;
	USARTx->USART_CR1 |= USART_CR1_TE;
	USARTx->USART_CR1 |= USART_CR1_RE;
} 

void HUNG_USART_Trans(USART_TypeDef *USARTx, char c)
{
		while(!(USARTx->USART_SR & USART_SR_TXE)); // cho den khi TXE=1
		USARTx->USART_DR = (uint8_t)c;
}

uint8_t HUNG_USART_Recv(USART_TypeDef *USARTx)
{
	while(!(USARTx->USART_SR & USART_SR_RXNE));
	return (uint8_t)USARTx->USART_DR;
}

void HUNG_USART_SendBuff(USART_TypeDef *USARTx, const void *data, uint16_t len)
{
	// dung pointer void de cho toi bat ki du lieu nao
	// khoi tao con tro p de duyet data
	const uint8_t *p = (const uint8_t *)data; 
	for(uint16_t i = 0; i < len ; i++)
	{
		HUNG_USART_Trans(USARTx, (char)p[i]); // goi ham trans de gui tung byte du lieu
	}
	while(!(USARTx->USART_SR & USART_SR_TC)); // cho den khi TC=1
}

void HUNG_USART_RecvBuff(USART_TypeDef *USARTx, const void *data, uint16_t len)
{
	uint8_t *p = (uint8_t *)data; 
	for(uint16_t i = 0 ; i < len ; i++)
	{
		p[i] = HUNG_USART_Recv(USARTx);
	}
	
}