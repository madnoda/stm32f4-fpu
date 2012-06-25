#include "systick.h"
__IO uint32_t TimingDelay;

void SysTickInit(__IO uint32_t interval)
{
	SystemCoreClockUpdate();
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	if (SysTick_Config(SystemCoreClock/ interval))
	{ 
		while (1);
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Prescaler = (SystemCoreClock / USEC_INTERVAL) - 1;
	TIM_TimeBaseStructure.TIM_Period = UINT32_MAX; 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM5, ENABLE);
}

void _delay_ms(__IO uint32_t mSec)
{ 
	TimingDelay = mSec;

	while(TimingDelay != 0);
}

void _delay_us(__IO uint32_t uSec)
{

#if 1
	volatile uint16_t start = TIM5->CNT;
	/* use 32 bit count wrap around */
	while((uint16_t)(TIM5->CNT - start) <= uSec);

#else
	/* This is the stupid method */
	while(uSec--){ 
					__NOP();
					__NOP();
					__NOP();
					__NOP();
					__NOP();
					__NOP();
					}
#endif
}

void Delay(__IO uint32_t nCount)
{
	while(nCount--){ 
					__NOP();
					__NOP();
					__NOP();
					__NOP();
					__NOP();
					__NOP();
					}
}

