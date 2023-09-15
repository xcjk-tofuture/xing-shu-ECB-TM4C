#include "key_proc.h"







void KEY_EXIT_Handler() //sw1 sw2 中断回调函数
{
	static uint8_t trigger=0;
	
	uint32_t sta  = GPIOIntStatus(GPIO_PORTF_BASE,  true);//获取状态  后面那个ture是是否屏蔽或原始中断状态返回
	GPIOIntClear(GPIO_PORTF_BASE,sta);//清除指定的中断源
	if((sta & GPIO_PIN_0) == GPIO_PIN_0)  //判断是哪个触发的中断源
	{
  GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1,trigger ^= GPIO_PIN_1); //SW1
//	LCD_Clear(RED);                                                                 //按键1按下
	
	}
	if((sta & GPIO_PIN_4) == GPIO_PIN_4)
	{
	GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,trigger ^= GPIO_PIN_3);
//	LCD_Clear(BLUE);	                                                               //按键2按下
	
	}
}




//也可以用扫描的方式查询 我嫌按键有点少就用边沿触发中断了

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