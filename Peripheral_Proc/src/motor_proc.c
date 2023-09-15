#include "motor_proc.h"



MOTOR MotorA, MotorB;  //��Ŷ�Ӧ 0 1 





void Motor_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Motor_Task_Proc */
	MotorA.Num = 0;
	MotorB.Num = 1;
	Motor_Init();  //�����ʼ��
  for(;;)
  {

		Motor_Speed_Set(&MotorA, -4000);
		Motor_Speed_Set(&MotorB, 6000);
	
    vTaskDelay(1000);
  }
  /* USER CODE END Motor_Task_Proc */
}

void Encoder_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Encoder_Task_Proc */
  /* Infinite loop */
	Motor_Encoder_Init(); //������ģʽ��ʼ��
  for(;;)
  {
 Motor_Get_Value(&MotorA);
 Motor_Get_Value(&MotorB);
	printf("MotorA: %d\r\n", MotorA.Trig);
	printf("MotorB: %d\r\n", MotorB.Trig);		
   vTaskDelay(20);
  }
  /* USER CODE END Encoder_Task_Proc */
}


//��ȡ���������ֵ ����  ��ת��Ϊ�ٶ� ��� A B C D ��Ӧ 0 1 2 3
/******************************************************************************
      ����˵�����ı�Ƶ�ⲿ�жϷ� M���ٷ� ��ȡ���������ֵ ����  ��ת��Ϊ�ٶ� ��� A B C D ��Ӧ 0 1 2 3
      ������ݣ�����ṹ��ָ��    
      ����ֵ��  ��
******************************************************************************/
void Motor_Get_Value(MOTOR  *motor)
{
	switch(motor->Num) 
	{
		case 0: motor->Trig = QEIVelocityGet(QEI0_BASE);//��ȡ����ֵ  
						motor->direction = QEIDirectionGet(QEI0_BASE);//��ȡ����		
						motor->Speed = motor->Trig * 3.25 ;
						break;
		case 1: motor->Trig = QEIVelocityGet(QEI1_BASE);//��ȡ����ֵ  
						motor->direction = QEIDirectionGet(QEI1_BASE);//��ȡ����	
						motor->direction = !motor->direction;  //ǿ��ȡ��
						motor->Trig = -motor->Trig;						//ǿ��ȡ��
						motor->Speed = motor->Trig * 3.25 ;
						break;
	}
					
}


/******************************************************************************
      ����˵��������ֵ����
      ������ݣ���ֵ    
      ����ֵ��  ��
******************************************************************************/
int ABS(int a)
{
	a = a>0?a:(-a);
	return a;

}

/******************************************************************************
      ����˵��������ֵ���� ������
      ������ݣ���ֵ    
      ����ֵ��  ��
******************************************************************************/
float FABS(float a)
{
	a = a>0?a:(-a);
	return a;

}


/******************************************************************************
      ����˵��������ٶ����ú��� ���õ���ٶ�  ��Χ -9999 - +9999
      ������ݣ�����ṹ��ָ��   �ٶ�    
      ����ֵ��  ��
******************************************************************************/
void Motor_Speed_Set(MOTOR *motor, s16 speed)
{
	

	if(speed >= 10000 ) speed = 9999;
	if(speed <= -10000 ) speed = -9999;   //�޷�
	switch(motor->Num)
	{
		case 0: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //�жϷ���   0Ϊ�� 1Ϊ��
						if(!motor->SetDirection) //����
						{
						
				
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_0,                             
														(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_1, 1);			
						
						}
					else if(motor->SetDirection) //����
					{
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_1, 
														(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);                           
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_0, 1);				

						}
						break;
		case 1: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //�жϷ���
						if(!motor->SetDirection) //����
						{
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_3, 
															(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);                           
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_2, 1);			
							

						}
					else if(motor->SetDirection) //����
					{
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_2, 
															(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);                           
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_3, 1);	
					
					}
						break;
	}
					

}