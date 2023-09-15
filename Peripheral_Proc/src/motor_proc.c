#include "motor_proc.h"



MOTOR MotorA, MotorB;  //编号对应 0 1 





void Motor_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Motor_Task_Proc */
	MotorA.Num = 0;
	MotorB.Num = 1;
	Motor_Init();  //电机初始化
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
	Motor_Encoder_Init(); //编码器模式初始化
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


//获取电机的脉冲值 方向  并转换为速度 电机 A B C D 对应 0 1 2 3
/******************************************************************************
      函数说明：四倍频外部中断法 M测速法 获取电机的脉冲值 方向  并转换为速度 电机 A B C D 对应 0 1 2 3
      入口数据：电机结构体指针    
      返回值：  无
******************************************************************************/
void Motor_Get_Value(MOTOR  *motor)
{
	switch(motor->Num) 
	{
		case 0: motor->Trig = QEIVelocityGet(QEI0_BASE);//获取计数值  
						motor->direction = QEIDirectionGet(QEI0_BASE);//获取方向		
						motor->Speed = motor->Trig * 3.25 ;
						break;
		case 1: motor->Trig = QEIVelocityGet(QEI1_BASE);//获取计数值  
						motor->direction = QEIDirectionGet(QEI1_BASE);//获取方向	
						motor->direction = !motor->direction;  //强制取反
						motor->Trig = -motor->Trig;						//强制取反
						motor->Speed = motor->Trig * 3.25 ;
						break;
	}
					
}


/******************************************************************************
      函数说明：绝对值函数
      入口数据：数值    
      返回值：  无
******************************************************************************/
int ABS(int a)
{
	a = a>0?a:(-a);
	return a;

}

/******************************************************************************
      函数说明：绝对值函数 浮点数
      入口数据：数值    
      返回值：  无
******************************************************************************/
float FABS(float a)
{
	a = a>0?a:(-a);
	return a;

}


/******************************************************************************
      函数说明：电机速度设置函数 设置电机速度  范围 -9999 - +9999
      入口数据：电机结构体指针   速度    
      返回值：  无
******************************************************************************/
void Motor_Speed_Set(MOTOR *motor, s16 speed)
{
	

	if(speed >= 10000 ) speed = 9999;
	if(speed <= -10000 ) speed = -9999;   //限幅
	switch(motor->Num)
	{
		case 0: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //判断方向   0为正 1为负
						if(!motor->SetDirection) //正向
						{
						
				
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_0,                             
														(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_1, 1);			
						
						}
					else if(motor->SetDirection) //反向
					{
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_1, 
														(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_0)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);                           
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_0, 1);				

						}
						break;
		case 1: motor->SetSpeedRange = speed;
						motor->SetDirection =  motor->SetSpeedRange >= 0 ? 0 : 1;  //判断方向
						if(!motor->SetDirection) //正向
						{
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_3, 
															(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);                           
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_2, 1);			
							

						}
					else if(motor->SetDirection) //反向
					{
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_2, 
															(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_1)) * FABS((float)motor->SetSpeedRange/ 10000) - 1);                           
				PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_3, 1);	
					
					}
						break;
	}
					

}