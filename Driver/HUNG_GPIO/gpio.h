#ifndef GPIO_DRIVER_H 
#define GPIO_DRIVER_H

#include <stdint.h>
// khai bao cau truc cua driver
// struct dinh nghia thanh ghi
typedef struct
{
	volatile uint32_t CRL, CRH, IDR, ODR, BSSR, BRR, LCKK;
}GPIO_TypeDef;

typedef struct
{
	
}GPIO_Init;

#define GPIOA ((GPIO_TypeDef*)0x40010800)
#define GPIOB ((GPIO_TypeDef*)0x40010C00) // dinh dia chi cho GPIO
#define GPIOC ((GPIO_TypeDef*)0x40011000)

// define GPIO config

// define GPIO MODE 
typedef enum
{
 GPIO_MODE_INPUT 				=0, 			// INPUT Mode
 GPIO_MODE_OUTPUT_10 		=1, 	// 10MHZ
 GPIO_MODE_OUTPUT_2 		=2,		// 2HZ
 GPIO_MODE_OUTPUT_50 		=3 	// 50MHz
}GPIO_MODE_t;	
// define Che do chan (CNF)
typedef enum	
{	
	GPIO_CNF_IN_ANALOG 		=0,
	GPIO_CNF_IN_FLOAT 		=1,
	GPIO_CNF_IN_PP				=2, // pull up, pull down
// define che do output
} GPIO_CNF_IN_t;
typedef enum	
{
	GPIO_CNF_OUT_PP 			=0, //push pull
	GPIO_CNF_OUT_OD 			=1, //open drain
	GPIO_CNF_OUT_AF_PP 		=2, //ALterlnate push pull
	GPIO_CNF_OUT_AF_OD 		=3 //ALterlnate open drain
} GPIO_CNF_OUT_t;

// define che do input
typedef enum
{
	GPIO_NOPULL 					=0,
	GPIO_INPUT_PULL_UP 		=1,
	GPIO_INPUT_PULL_DOWM 	=2
}GPIO_PULL_t;
//ham config

void HUNG_GPIO_conf(GPIO_TypeDef *port, uint16_t pin, GPIO_MODE_t mode, uint32_t cnf, GPIO_PULL_t pull);

void HUNG_GPIO_Toogle(GPIO_TypeDef *port, uint16_t pin);

void HUNG_GPIO_WritePin(GPIO_TypeDef *port, uint16_t pin, uint8_t value);

uint16_t HUNG_GPIO_ReadPin(GPIO_TypeDef *port, uint16_t pin);
#endif