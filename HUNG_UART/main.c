#include "gpio.h"
#include "RCC_conf.h"
#include "stdint.h"
#include "Uart.h"

void delay_ms(unsigned int count){
	while(count--){
		for(volatile unsigned int i=0; i < 6000; i++);
	}
}

int main(void)
{
    HUNG_USART_Init();
//		HUNG_RCC_En(HUNG_RCC_GPIOA);
//		
//		HUNG_GPIO_conf(GPIOA, 9, GPIO_MODE_OUTPUT_10, GPIO_CNF_OUT_PP, GPIO_NOPULL);
    
    while (1)
    {
    HUNG_USART_Trans('A');
		delay_ms(500);
       
    }
}