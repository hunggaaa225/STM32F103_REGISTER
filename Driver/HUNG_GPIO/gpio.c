#include "gpio.h"

void HUNG_GPIO_conf(GPIO_TypeDef *port, uint16_t pin, GPIO_MODE_t mode, uint32_t cnf, GPIO_PULL_t pull)
{
	volatile uint32_t *cr; // khoi tao con tro tro toi CRH or CRL
	uint8_t shift; // vi tri bit cua chan GPIo trong thanh ghi
	uint32_t value; // gia tri can ghi vao thanh ghi de cau hinh che do mode GPIO
		// CRL - quan li chan 0-7
		// CRH - quan li chan 8-5
	if(pin < 8){
		cr = &port->CRL; // con tro cr tro toi thanh ghi CRl
		shift = pin*4; // vi tri bit cua chan dc khai bao, xem manual se hieu 
	}else{
		cr = &port->CRH; // con tro cr tro toi thanh ghi CRH
		shift = (pin - 8) * 4; // vi tri bit cua chan GPIO
	}
	value = (cnf << 2) | mode; // gop 2 thanh phan Mode va CNF thanh 1 gia tri de thuc hien ghi vao thanh ghi de cau hinh chan GPIO
	
	//xoa bit tai vi tri khai bao trc
	*cr &= ~(0xF << shift);
	// dich 4 bit 1111 den vij tri bit truy cap, sau do thuc hien dao bit roi gan AND, luc nay 4 bit o vi tri shift se bang 0
	
	// ghi gia tri value vao vi tri bit de thuc hien set up
	*cr |=(value << shift);
	
	// cau hinh che do pull up, pull down trong input
	if(mode == 0 && cnf == 2)
	{
		port->ODR |= (1 << pin);
	}else 
	{
		port->ODR &= ~(1 << pin);
	}
}

void HUNG_GPIO_Toogle(GPIO_TypeDef *port, uint16_t pin)
{
	port->ODR ^= (1 << pin);
}

void HUNG_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin, uint8_t value)
{
	if(value)
	{
		//port->ODR |= (1 << pin);
		port->BSSR = (1 << pin);
	}	
	else
	{
		//port->ODR &= ~(1 << pin);
		port->BRR = (1 << pin);
	}
	
}

uint16_t HUNG_GPIO_ReadPin(GPIO_TypeDef *port, uint16_t pin)
{
	return ((port->IDR >> pin) & 1); // dich phia pin bit de bit do ve vtri 0 rooi and voi 1
}

