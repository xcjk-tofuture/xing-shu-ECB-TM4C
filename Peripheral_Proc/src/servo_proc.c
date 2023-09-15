#include "servo_proc.h"


//�������˵������ ��Ϊioʵ��ȱ��  ���������· �������и�ԣ��io���Ը��� �������֧��4·PWM       
//Ĭ��PWM1  PE4 PWM2 PE6
void Servo_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Servo_Task_Proc */
  Servo_Init();     //�����ʼ��
	Servo_Enable_All();		//���ʹ��
  for(;;)
  {
		Servo_Diver(2, 200);
		Servo_Diver(1, 200);
     vTaskDelay(1);
  }
  /* USER CODE END Servo_Task_Proc */
}


/******************************************************************************
      ����˵����ʹ��ȫ����� ���ȫ������
      ������ݣ���    
      ����ֵ��  ��
******************************************************************************/
void Servo_Enable_All()
{	
	PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, true);
	PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, true);
	
		
	//����CCR
	 PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*0.075 - 1)); 
	 PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_5,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*0.075 - 1)); 
}



/******************************************************************************
      ����˵����ʧ�ܶ��
      ������ݣ�servo_num   ���id ��Ӧ�����ϵ�1��4            
      ����ֵ��  ��
******************************************************************************/
void Servo_Disable(u8 servo_num)
{
	if(servo_num == 1)
		PWMOutputState(PWM0_BASE, PWM_OUT_4_BIT, false);
	if(servo_num == 2)
		PWMOutputState(PWM0_BASE, PWM_OUT_5_BIT, false);
}



/******************************************************************************
      ����˵����ָ�����ת��Ӧ��Χ  ��Ӧռ�ձ�2.5%-12.5%
      ������ݣ�servo_num   ���id ��Ӧ�����ϵ�1��4
							 range			 ��Χ Ĭ��0-1800
      ����ֵ��  ��
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