#ifndef __HW_CONFIG_H
#define __HW_CONFIG_H 0x0100

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <stdbool.h>
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include "stm32f4xx_conf.h"
#include "platform_config.h"

#include "systick.h"
#include "uart_support.h"

#define countof(a)   (sizeof(a) / sizeof(*(a)))

extern __IO uint16_t CmdKey;
extern void Set_System(void);
extern void NVIC_Configuration(void);

#ifdef __cplusplus
}
#endif

#endif
