#include "rgb_proc.h"






u8 ucLed;





void RGB_Task_Proc(void const * argument)           //RGB����������
{
  /* USER CODE BEGIN RGB_Task_Proc */
  /* Infinite loop */
	ucLed = 0x01;
  for(;;)
  {
    ucLed *= 2;
		if(ucLed > 0x04) ucLed = 0x01;
		RGB_Show_Proc(ucLed);
		//printf("23333\r\n");
		
		vTaskDelay(1000);
  }
  /* USER CODE END RGB_Task_Proc */
}


void RGB_Show_Proc(u8 ucled)                      //0b000 ����λ��1 ����
{
	//
	GPIOPinWrite(RGB_R_GPIO_Port,  RGB_R_Pin, (ucled & 0x04) == 0 ? 0 : RGB_R_Pin);
	GPIOPinWrite(RGB_B_GPIO_Port,  RGB_B_Pin, (ucled & 0x02) == 0 ? 0 : RGB_B_Pin);
	GPIOPinWrite(RGB_G_GPIO_Port,  RGB_G_Pin, (ucled & 0x01) == 0 ? 0 : RGB_G_Pin);

};