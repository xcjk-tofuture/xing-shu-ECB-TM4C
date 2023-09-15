#include "buzzer_proc.h"



// ������������Ƶ��
#define DO 523
#define RE 587
#define MI 659
#define FA 698
#define SO 784
#define LA 880
#define SI 988

uint32_t adcValue[3];
float BatValue;
//������ PC4
void Buzzer_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Buzzier_Task_Proc */
  /* Infinite loop */
	Buzzer_Init();
//������Ч
	Music_Play_StartUp();

	
  for(;;)
  {
	ADCProcessorTrigger(ADC0_BASE, 0);

	// �ȴ�ת�����
	while(!ADCIntStatus(ADC0_BASE, 0, false)) {}



	// ��ADC��������ȡ����

	ADCSequenceDataGet(ADC0_BASE, 0, adcValue);

	BatValue = ((float)adcValue[0] * 10 )/ 4096 * 3.3;
//	printf("adc1:%d\r\n",adcValue[0]);
//	printf("BAT_Value:%.2fV\r\n",BatValue);

	// ����жϱ�־
	ADCIntClear(ADC0_BASE, 0);
  if(BatValue < 10.6 && BatValue > 4.5) //��ѹ���㱨��
	{
	 Music_Play_Lowbattery();
	}
    vTaskDelay(100);
  }
  /* USER CODE END Buzzier_Task_Proc */
}

//������������
void driveBuzzer(uint16_t frequency, uint32_t duration) 
	{ 

		PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true); //ʹ�ܷ�����
	  PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_3, (10000000 / 8)  /frequency );
		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_6,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3)*0.5 - 1));  
		vTaskDelay(duration); 
		PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false); //ʧ�ܷ�����
}


void Music_Play_StartUp()  //��������
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

void Music_Play_Lowbattery()  //���������������
{
	driveBuzzer(MI, 200);
	driveBuzzer(RE, 200);
  driveBuzzer(DO, 200);
	
	driveBuzzer(MI, 200);
	driveBuzzer(RE, 200);
  driveBuzzer(DO, 200);
	

}




