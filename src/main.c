#include "stm32f4xx.h"
#include "platform_config.h"
#include "hw_config.h"

int main(void)
{
	volatile float fnk1,fnk2,fnk3=0;
        int i;

	Set_System();
	
	SysTickInit(INTERVAL);
	
	conio_init(UART_DEFAULT_NUM,UART_BAUDLATE);
	printf("\n");
	printf("Welcome to %s test program !!\n",MPU_SUBMODEL);
	printf("Version %s!!\n",APP_VERSION);
	printf("Build Date : %s\n",__DATE__);

	fnk1 = 14.0;
	fnk2 = 9.0;
	fnk3 = fnk1/fnk2;
	printf("Floating point calculation: %f/%f=%f\n",fnk1,fnk2,fnk3);
	printf("\n");
        fnk1 = 0.0;
        for (i = 1;i < 50000000;i += 4) {
          fnk1 += 4.0f / (float)(i) - 4.0f / (float)(i + 2);
        }
	printf("pi: %f\n",fnk1);
	printf("\n");

	/* Main Loop */
	while (1)
	{
		_delay_ms(100);
		_delay_ms(100);
	}
}

