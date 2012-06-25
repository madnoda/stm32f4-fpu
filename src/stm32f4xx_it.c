#include "stm32f4xx_it.h"
#include "hw_config.h"
void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

void SysTick_Handler(void)
{
	static uint8_t  cntdiskio=0;
#if	defined(USE_ADS7843)
	static uint16_t cnt=0;

	 /* every 100 mSec */
	if( cnt++ >= 100 ) {
		cnt = 0;
		scaned_tc =1;
	}
#endif

	 /* every 10mSec */
	if ( cntdiskio++ >= 10 ) {
		cntdiskio = 0;
	}

	/* every 1mSec */
	TimingDelay_Decrement();
}

void RTC_IRQHandler(void)
{
}

void USART2_IRQHandler(void)
{

	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
	{
		uint16_t tempRX_Head = ((&USART2_Buf)->RX_Head + 1) & (UART_BUFSIZE-1);

		uint16_t tempRX_Tail = (&USART2_Buf)->RX_Tail;
		uint8_t data =  USART_ReceiveData(USART2);

		if (tempRX_Head == tempRX_Tail) {
			USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
		}else{
			(&USART2_Buf)->RX[(&USART2_Buf)->RX_Head] = data;
			(&USART2_Buf)->RX_Head = tempRX_Head;
		}
	}

	if(USART_GetITStatus(USART2, USART_IT_TXE) != RESET)
	{   
		uint16_t tempTX_Tail = (&USART2_Buf)->TX_Tail;
		if ((&USART2_Buf)->TX_Head == tempTX_Tail){
			USART_ITConfig(USART2, USART_IT_TXE, DISABLE);
		}else{
			uint8_t data = (&USART2_Buf)->TX[(&USART2_Buf)->TX_Tail];
			USART2->DR = data;

			(&USART2_Buf)->TX_Tail = ((&USART2_Buf)->TX_Tail + 1) & (UART_BUFSIZE-1);
		}
	}
}

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{
		uint16_t tempRX_Head = ((&USART1_Buf)->RX_Head + 1) & (UART_BUFSIZE-1);
		uint16_t tempRX_Tail = (&USART1_Buf)->RX_Tail;
		uint8_t data =  USART_ReceiveData(USART1);

		if (tempRX_Head == tempRX_Tail) {
			USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
		}else{
			(&USART1_Buf)->RX[(&USART1_Buf)->RX_Head] = data;
			(&USART1_Buf)->RX_Head = tempRX_Head;
		}
	}
	if(USART_GetITStatus(USART1, USART_IT_TXE) != RESET)
	{   
		uint16_t tempTX_Tail = (&USART1_Buf)->TX_Tail;
		if ((&USART1_Buf)->TX_Head == tempTX_Tail){
			USART_ITConfig(USART1, USART_IT_TXE, DISABLE);
		}else{
			uint8_t data = (&USART1_Buf)->TX[(&USART1_Buf)->TX_Tail];
			USART1->DR = data;
			(&USART1_Buf)->TX_Tail = ((&USART1_Buf)->TX_Tail + 1) & (UART_BUFSIZE-1);
		}
	}
}

