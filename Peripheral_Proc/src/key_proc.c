#include "key_proc.h"







void KEY_EXIT_Handler() //sw1 sw2 �жϻص�����
{
	static uint8_t trigger=0;
	
	uint32_t sta  = GPIOIntStatus(GPIO_PORTF_BASE,  true);//��ȡ״̬  �����Ǹ�ture���Ƿ����λ�ԭʼ�ж�״̬����
	GPIOIntClear(GPIO_PORTF_BASE,sta);//���ָ�����ж�Դ
	if((sta & GPIO_PIN_0) == GPIO_PIN_0)  //�ж����ĸ��������ж�Դ
	{
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,trigger ^= GPIO_PIN_1); //SW1
//	LCD_Clear(RED);                                                                 //����1����
	
	}
	if((sta & GPIO_PIN_4) == GPIO_PIN_4)
	{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,trigger ^= GPIO_PIN_3);
//	LCD_Clear(BLUE);	                                                               //����2����
	
	}
}




//Ҳ������ɨ��ķ�ʽ��ѯ ���Ӱ����е��پ��ñ��ش����ж���

void Key_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Key_Task_Proc */
  /* Infinite loop */
  for(;;)
  {
     vTaskDelay(1);
  }
  /* USER CODE END Key_Task_Proc */
}