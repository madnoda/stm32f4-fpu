#include "stm32f4xx.h"
#include "hw_config.h"
void Set_System(void)
{
	NVIC_Configuration();
}

void KEY_Configuration(void)
{
}

void NVIC_Configuration(void)
{
	NVIC_SetPriority(SysTick_IRQn, 0x0);	
}

