#ifndef __UART_SUPPORT_H
#define __UART_SUPPORT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <inttypes.h>

#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"

#define UART_BUFSIZE		256
#define UART_BAUDLATE		38400UL
#ifndef UART_DEFAULT_NUM
#error "UART_DEFAULT_NUM should be setted 1 or 2 !!"
#endif

#define countof(a)   (sizeof(a) / sizeof(*(a)))

extern void conio_init(uint32_t port, uint32_t baudrate);
extern void putch(uint8_t c);
extern uint8_t getch(void);
extern uint8_t keypressed(void);
extern void cputs(char *s);
extern void cgets(char *s, int bufsize);

typedef struct USART_Buffer
{
	volatile uint8_t RX[UART_BUFSIZE];
	volatile uint8_t TX[UART_BUFSIZE];
	volatile uint16_t RX_Head;
	volatile uint16_t RX_Tail;
	volatile uint16_t TX_Head;
	volatile uint16_t TX_Tail;
} USART_Buffer_t;

extern USART_InitTypeDef USART_InitStructure;
extern USART_Buffer_t USART1_Buf;
extern USART_Buffer_t USART2_Buf;
#ifdef __cplusplus
}
#endif

#endif

