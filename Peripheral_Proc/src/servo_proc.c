#include "servo_proc.h"


//舵机这里说明几点 因为io实在缺少  就设计了两路 单好在有富裕的io可以复用 所以最大支持4路PWM       
//默认PWM1  PE4 PWM2 PE6
void Servo_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Servo_Task_Proc */
  Servo_Init();     //舵机初始化
	Servo_Enable_All();		//舵机使能
  for(;;)
  {
		Servo_Diver(2, 200);
		Servo_Diver(1, 200);
     vTaskDelay(1);
  }
  /* USER CODE END Servo_Task_Proc */
}


/******************************************************************************
      函数说明：使能全部舵机 舵机全部回中
      入口数据：无    
      返回值：  无
******************************************************************************/
void Servo_Enable_All()
{	
	PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
	PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);
	
		
	//设置CCR
	 PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*0.075 - 1)); 
	 PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_5,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*0.075 - 1)); 
}



/******************************************************************************
      函数说明：失能舵机
      入口数据：servo_num   舵机id 对应板子上的1到4            
      返回值：  无
******************************************************************************/
void Servo_Disable(u8 servo_num)
{
	if(servo_num == 1)
		PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
	if(servo_num == 2)
		PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, false);
}



/******************************************************************************
      函数说明：指定舵机转相应范围  对应占空比2.5%-12.5%
      入口数据：servo_num   舵机id 对应板子上的1到4
							 range			 范围 默认0-1800
      返回值：  无
******************************************************************************/
void Servo_Diver(u8 servo_num, u16 range)
{
		if(servo_num == 1)
		{   
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_4, (PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*(0.025 + (float)range/18000 )) - 1);
				//printf("%d\r\n",TIM1->CCR1);
		}
		else if(servo_num == 2)
		{
				
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_5, (PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*(0.025 + (float)range/18000 )) - 1); 
				//printf("%d\r\n",TIM1->CCR2);
		}
		else if(servo_num == 3)
		{
				
				//printf("%d\r\n",TIM1->CCR3);
		}
		else if(servo_num == 4)
		{
				
				//printf("%d\r\n",TIM1->CCR4);
		}
		else
		{
				printf("select servo error\r\n");
		}
}