#include "RCC_conf.h"
#include "stdint.h"

// dung struct MAP de truy cap toi thanh ghi can thiet
// MAP = TRO thanh ghi + mask bit
// tro thanh ghi thuc hien truy cap thanh ghi
// mask bit chua gia tri bit can ghi vao thanh ghi
typedef struct
{
	volatile uint32_t *reg; // khoi tao con tro thanh ghi
	uint32_t mask;
	
} HUNG_RCC_MAP_t;

#define HUNG_RCC_MAP(reg, bit) {(reg), (bit)} // dinh nghia macro phaan mang du lieu trong struct

static const HUNG_RCC_MAP_t hung_rcc_map[] = 
{
	[HUNG_RCC_AFIO] = HUNG_RCC_MAP(&RCC->APB2ENR, RCC_APB2ENR_AFIOEN), // truyen vao dia chir con tro vaf gia tri o nho can ghi
	[HUNG_RCC_GPIOA] = HUNG_RCC_MAP(&RCC->APB2ENR, RCC_APB2ENR_IOPAEN),
	[HUNG_RCC_GPIOB] = HUNG_RCC_MAP(&RCC->APB2ENR, RCC_APB2ENR_IOPBEN),
	[HUNG_RCC_GPIOC] = HUNG_RCC_MAP(&RCC->APB2ENR, RCC_APB2ENR_IOPCEN),
	[HUNG_RCC_GPIOD] = HUNG_RCC_MAP(&RCC->APB2ENR, RCC_APB2ENR_IOPDEN),
	[HUNG_RCC_USART1] = HUNG_RCC_MAP(&RCC->APB2ENR, RCC_APB2ENR_USART1EN),
	[HUNG_RCC_USART2] = HUNG_RCC_MAP(&RCC->APB1ENR, RCC_APB1ENR_USART2EN),
	[HUNG_RCC_USART3] = HUNG_RCC_MAP(&RCC->APB1ENR, RCC_APB1ENR_USART3EN)
};

void HUNG_RCC_En(HUNG_RCC_Periph_t periph)
{
	const HUNG_RCC_MAP_t *m = &hung_rcc_map[periph];
	*m->reg |= m->mask; // ghi noi dung truong mask vao thanh ghi reg
	(void) *m->reg; // kiem tra lai thanh ghi vua ghi
}