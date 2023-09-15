#include "k210_proc.h"


extern u8 Uart6_RX[200];
extern u8 Uart6_TX[200];


//∑¢ÀÕ”√Uart6_Transmit

void K210_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN K210_Task_Proc */
  /* Infinite loop */
  for(;;)
  {
     vTaskDelay(1);
  }
  /* USER CODE END K210_Task_Proc */
}