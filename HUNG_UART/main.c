#include "gpio.h"
#include "RCC_conf.h"
#include "stdint.h"
#include "Uart.h"
#include "string.h"

void delay_ms(unsigned int count){
	while(count--){
		for(volatile unsigned int i=0; i < 6000; i++);
	}
}
//led_init
static void led_init(void)
{

	HUNG_RCC_En(HUNG_RCC_GPIOC);
	HUNG_GPIO_conf(GPIOC, 13, GPIO_MODE_OUTPUT_2, GPIO_CNF_OUT_PP, GPIO_NOPULL);
	
}
// led_blink
static void led_blink_once(void)
{

	HUNG_GPIO_Toogle(GPIOC, 13);
	delay_ms(500);
}

int main(void)
{
    HUNG_USART_Init(USART3);
    led_init();

		uint8_t rx_buff[32];  // khoibtao mang nhan du lieu
    while (1)
    {
//        /* Phát 'A' qua PA9 */
//        HUNG_USART_Trans(USART3, 'A');

//        /* Nhận từ PA10 */
//        uint8_t received = HUNG_USART_Recv(USART3);

//        /* Nếu nhận đúng 'A' → nháy LED */
//        if (received == 'A')
//        {
//            led_blink_once();
//        }
				HUNG_USART_SendBuff(USART3, "ABC", 3);
				HUNG_USART_RecvBuff(USART3, rx_buff, 3);
			
				if(memcmp(rx_buff, "ABC", 3) ==0)
				{
					led_blink_once();
				}
    }
}