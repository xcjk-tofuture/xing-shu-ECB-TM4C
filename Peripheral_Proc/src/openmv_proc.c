#include "openmv_proc.h"


extern u8 Uart7_RX[200];
extern u8 Uart7_TX[200];

//∑¢ÀÕ”√Uart7_Transmit

void OpenMV_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN OpenMV_Task_Proc */
  /* Infinite loop */
  for(;;)
  {
     vTaskDelay(1);
  }
  /* USER CODE END OpenMV_Task_Proc */
}