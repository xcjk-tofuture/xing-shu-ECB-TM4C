#include "buzzer_proc.h"



// 定义七种音的频率
#define DO 523
#define RE 587
#define MI 659
#define FA 698
#define SO 784
#define LA 880
#define SI 988

uint32_t adcValue[3];
float BatValue;
//蜂鸣器 PC4
void Buzzer_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Buzzier_Task_Proc */
  /* Infinite loop */
	Buzzer_Init();
//开机音效
	Music_Play_StartUp();

	
  for(;;)
  {
	ADCProcessorTrigger(ADC0_BASE, 0);

	// 等待转换完成
	while(!ADCIntStatus(ADC0_BASE, 0, false)) {}



	// 从ADC缓冲区读取数据

	ADCSequenceDataGet(ADC0_BASE, 0, adcValue);

	BatValue = ((float)adcValue[0] * 10 )/ 4096 * 3.3;
//	printf("adc1:%d\r\n",adcValue[0]);
//	printf("BAT_Value:%.2fV\r\n",BatValue);

	// 清除中断标志
	ADCIntClear(ADC0_BASE, 0);
  if(BatValue < 10.6 && BatValue > 4.5) //电压不足报警
	{
	 Music_Play_Lowbattery();
	}
    vTaskDelay(100);
  }
  /* USER CODE END Buzzier_Task_Proc */
}

//驱动发生音乐
void driveBuzzer(uint16_t frequency, uint32_t duration) 
	{ 

		PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true); //使能蜂鸣器
	  PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_3, (10000000 / 8)  /frequency );
		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_6,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3)*0.5 - 1));  
		vTaskDelay(duration); 
		PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false); //失能蜂鸣器
}


void Music_Play_StartUp()  //开机音乐
{
  driveBuzzer(DO, 200);
	driveBuzzer(RE, 200);
	driveBuzzer(MI, 200);
	driveBuzzer(DO, 200);
	driveBuzzer(RE, 200);
	driveBuzzer(MI, 200);
	driveBuzzer(SO, 200);
	driveBuzzer(FA, 200);

}

void Music_Play_Lowbattery()  //电机电量不足音乐
{
	driveBuzzer(MI, 200);
	driveBuzzer(RE, 200);
  driveBuzzer(DO, 200);
	
	driveBuzzer(MI, 200);
	driveBuzzer(RE, 200);
  driveBuzzer(DO, 200);
	

}




