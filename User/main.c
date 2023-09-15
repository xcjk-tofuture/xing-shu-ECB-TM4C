
#include "include.h"


//PF1 2 3  rgb 0 4 key PE3  PB1 PE4 pwm PB7 cap  
//ADC PE2  PE3  PB






  
int main(void)
{

	All_Init();
	Motor_Encoder_Init();
	FREERTOS_Init();
//	
	vTaskStartScheduler();
	while(1)
	{
	
	}

	//static uint8_t trigger=0;      //led��ת��־λ��	
//		// Turn on the LED ��PF1(R),PF2(B),PF3(G)
//		//ʹ�ܶ�Ӧ��λ��Ϊ�ߵ�ƽ ע�����︳��ֵ�����ź��й� 0Ϊ1 1Ϊ2 2Ϊ4��ȵȵ�  �����ú궨���������Ҫ
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,trigger ^= GPIO_PIN_3);
//		// Delay for a bit		
//	//MPU6050��֤ Ҳ��iic��֤
//MPU6050_Read_Data(&Gyro, &Acc, &Temp);
//	printf("3��������:%d\t%d\t%d\r\n",(int16_t)(Gyro.x),(int16_t)(Gyro.y),(int16_t)(Gyro.z));
//	printf("3����ٶ�:%d\t%d\t%d\r\n",(int16_t)(Acc.x),(int16_t)(Acc.y),(int16_t)(Acc.z));
//	printf("IMU�¶ȡ�:%f\r\n",Temp);
//		
//	//��ʱ�����벶����֤	
//	//printf("d: %d %%, p: %d\r\n",duty,freq);
//	
//		
//	 // ����ADCת��
//	ADCProcessorTrigger(ADC0_BASE, 0);

//	// �ȴ�ת�����
//	while(!ADCIntStatus(ADC0_BASE, 0, false)) {}



//	// ��ADC��������ȡ����

//	ADCSequenceDataGet(ADC0_BASE, 0, adcValue);


//	printf("adc1:%d\r\n",adcValue[0]);

//	// ����жϱ�־
//	ADCIntClear(ADC0_BASE, 0);

//  //
		

}

void All_Init()
{
	Sys_Tick_Init();
	GPIO_Init(); 
	
	LCD_IO_Init();
	
	USART_Init();
	
	TIM0_Init(1);//���ö�ʱ����1s����	
	WTIM1_Init(1);//���ö�ʱ����1ms����	
	
	//ADC_Init();
	BAT_ADC_Init();
	
	I2C_Init();
	SSI_Init();
	

//	
//	    
	
	


}


/*
		1��	ѡ���ⲿ��������Ϊϵͳʱ�ӣ�����������PLL��Ƶ(400M)��������Ƶ��Ϊ16MHz��ϵͳʱ�ӷ�Ƶ��Ϊ4��ϵͳʱ��Ƶ��Ϊ400M/2.5/2=80M��
				SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_XTAL_16MHZ|(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN)); 
	
		2��	��ַ���ߵ�[9:2]λ������λ������ֱ�Ӷ�GPIODATA���ݼĴ����Ķ��λ�����޸�
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);	
				��PF base��ַдֵui8LED����3:2:1λ�����޸ģ���ԭ��ͼ������д1����

		3�� SysCtlDelay()����������û�࣬�ṩ�˿�Խ������ʱ�㶨���ӳ١���ʱ3*n��ʱ������
				������SysCtlDelay(n*(SysCtlClockGet()/3000));�㶨��ʱ1ms�������ÿ���ϵͳʱ��Ƶ��
				����Ҫע�⣺�������ĸ�ʱ��Դ��ֻҪ����Ƶ�ʸ���40MHz���ͻᵼ��ʵ����ʱʱ���������ֵ��ԭ�������оƬ�ڲ�Flash�Ķ�ȡƵ�����ֻ�ܴﵽ40M��
										������Ƶ�ʴ���40MHzʱ��ͨ��Ԥȡ�����ֵ�ָ�����ﵽ80M��������Ƶ��
										���ǣ�������SysCtlDelay�������ֶ���תʱ������Բ����ܺܺõĹ�����ÿ�ζ���Ҫ��ȡָ�����ʱ����ӳ���
				Ҳ����˵�����Ƶ����40M��SysCtlDelay(n*(SysCtlClockGet()/3000))�������Ҳ���Ǻ�׼�����Կ�����ROM_SysCtlDelasy()
*/	


/******************************************************************************
      ����˵����ʱ�ӳ�ʼ��  ��Ƶ��Ϊ80MHZ�����Ƶ�ʣ� 400/2/2.5
      ������ݣ���    
      ����ֵ��  ��
******************************************************************************/
void Sys_Tick_Init()
{
  //����ʱ����16MHZ ���ⲿʱ����16MHZ
	
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_XTAL_16MHZ|(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN)); //ϵͳʱ�ӷ�Ƶ��ϵ��|ѡ���ⲿ����Ƶ��|ʹ��PLL���໷��Ϊϵͳʱ��Դ|ʱ��Դ
	//��Ƶϵ��SYSCTL_SYSDIV_1,SYSCTL_SYSDIV_2, SYSCTL_SYSDIV_3, SYSCTL_SYSDIV_64��
	SysCtlPWMClockSet( SYSCTL_PWMDIV_64);
	/*�ⲿ����Ƶ����SYSCTL_XTAL_4MHZ, SYSCTL_XTAL_4_09MHZ, SYSCTL_XTAL_4_91MHZ,

		SYSCTL_XTAL_5MHZ, SYSCTL_XTAL_5_12MHZ, SYSCTL_XTAL_6MHZ,

		SYSCTL_XTAL_6_14MHZ, SYSCTL_XTAL_7_37MHZ, SYSCTL_XTAL_8MHZ,

		SYSCTL_XTAL_8_19MHZ, SYSCTL_XTAL_10MHZ, SYSCTL_XTAL_12MHZ,

		SYSCTL_XTAL_12_2MHZ, SYSCTL_XTAL_13_5MHZ, SYSCTL_XTAL_14_3MHZ,

		SYSCTL_XTAL_16MHZ, SYSCTL_XTAL_16_3MHZ, SYSCTL_XTAL_18MHZ,

		SYSCTL_XTAL_20MHZ, SYSCTL_XTAL_24MHZ, or SYSCTL_XTAL_25MHz. */
	
	// ʹ��pll���໷ʱ��Ƶ��Ϊ400MHZ ����ϵͳ��ͼ 2��Ƶ ��2.5��Ƶ�õ�ϵͳ֧�ֵ����ʱ��Ƶ��80MHZ ��ʹ��pll���໷ ��Ϊ SYSCTL_USE_OSC
	
	
	//ʱ��Դ SYSCTL_OSC_MAIN,	SYSCTL_OSC_INT, SYSCTL_OSC_INT4, SYSCTL_OSC_INT30, or SYSCTL_OSC_EXT32.
	//��������
			/*SYSCTL_OSC_MAIN��ʹ���ⲿ����������Ϊ��ϵͳʱ��Դ��������õ�ѡ������ڴ����Ӧ�ó�����

			SYSCTL_OSC_INT��ʹ���ڲ���Ƶ������Ϊ��ϵͳʱ��Դ������һ��ʡ���ѡ������ڵ͹��ĵ�Ӧ�ã������ܻ�����һЩ���ܡ�

			SYSCTL_OSC_INT4��ʹ���ڲ�4 MHz������Ϊ��ϵͳʱ��Դ������һ�ָ����ܵ�ѡ���������Ҫ����ʱ���ٶȵ�Ӧ�á�

			SYSCTL_OSC_INT30��ʹ���ڲ�30 KHz������Ϊ��ϵͳʱ��Դ������һ�ּ��͹��ĵ�ѡ�������Ҫ�󼫵͹��ĵ�Ӧ�ã���ʱ���ٶȽ�����

			SYSCTL_OSC_EXT32��ʹ���ⲿ32.768 KHz������Ϊ��ϵͳʱ��Դ������һ�ֵ͹���ѡ���������Ҫ��ȷ��ʱ��Ӧ�ã���ʵʱʱ�ӡ�*/
}

/******************************************************************************
      ����˵����ϵͳ��ʱn���� SysCtlDelay(SysCtlClockGet() / n / 3);  //��ʱ����ʱʱ��=1/n��
      ������ݣ���    
      ����ֵ��  ��
******************************************************************************/
void My_Delay_ms(u32 n)
{
	u32 count;
	count=SysCtlClockGet()/1000;		//SysCtlClockGet��ȡʱ��Ƶ�� ����Ϊ80M����λMHz,��10^3��Ƶ��ΪcountKHz��Ҳ����ÿ����1000count��ʱ�����ڣ�ÿ��count��Ӧ�������ڳ�1ms
	SysCtlDelay(n*count/3);					//SysCtlDelay��ʱ��3*��������ʱ�����ڣ�������ʱ3*n*count/3=n*count�����ڣ���n����

}

void My_Delay_us(u32 n)
{
	u32 count;
	count=SysCtlClockGet()/1000000;		//SysCtlClockGet��ȡʱ��Ƶ�� ����Ϊ80M����λMHz,��10^6��Ƶ��ΪcountKHz��Ҳ����ÿ����1count��ʱ�����ڣ�ÿ��count��Ӧ�������ڳ�1us
	SysCtlDelay(n*count/3);					//SysCtlDelay��ʱ��3*��������ʱ�����ڣ�������ʱ3*n*count/3=n*count�����ڣ���n΢��

}