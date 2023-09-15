#include "pc_proc.h"

extern u8 Uart0_RX[200];
extern u8 Uart0_TX[200];

//∑¢ÀÕ”√Uart0_Transmit

void PC_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN PC_Task_Proc */
  /* Infinite loop */
  for(;;)
  {
		//printf("test--- %c",Uart0_RX[1]);

  vTaskDelay(1000);
  }
  /* USER CODE END PC_Task_Proc */
	
}





