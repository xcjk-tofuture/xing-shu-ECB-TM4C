#include "bsp_tim.h"

u32 uwTick;


//TI�ҵĶ�ʱ����Ϊ16/32 ��ʱ�� �� 32/64��ʱ������  �ɷֱ���/����ʹ��
/************������ʱ��ʹ��***************/
/************����TIM0����ʹ�� 32λ��ʱ��ʾ��***************/	
void TIM0_Init(u16  fre)  //��ʱ��3����ʹ�ó�ʼ��
{
	

    //ʹ��TIMER3����
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    //TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);  //���μ���ģʽ
    //TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);//�����ڼ���ģʽ
    TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);  //�����Լ���ģʽ
 
     //һ����˵��ʱ������ֵΪSysCtlClockGet()/N-1����ʱʱ��Ϊ1/N�롣
    TimerLoadSet(TIMER3_BASE, TIMER_A,(SysCtlClockGet() / fre) - 1);
 
    //ʹ��Timer3A���ж�
    IntEnable(INT_TIMER3A);
 
    //�����ж�Դ������Ϊ��ʱʱ�����ж�
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
 
    //ʹ�ܶԴ��������ж�
    IntMasterEnable();
 
   //ΪTimer3Aע���жϴ�����   �����������Ĭ�϶������ö�ʱ��A
    TimerIntRegister(TIMER3_BASE,TIMER_A,TIM0_Period_Handler);
 
    //ʹ��TIMER3A
		TimerEnable( TIMER3_BASE,  TIMER_A);
		
}	



void TIM0_Period_Handler()  //��ʱ��3  32λ������ʱ��
{
	 static uint32_t time_count=0;  //��ʱ��
	// static uint8_t trigger=0;      //led��ת��־λ��
	

	
	
  uint32_t status=TimerIntStatus( TIMER3_BASE,  true); //��ȡ״̬  �����Ǹ�ture���Ƿ����λ�ԭʼ�ж�״̬����
	TimerIntClear( TIMER3_BASE,  status);  //����жϱ�־λ

	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,trigger ^= GPIO_PIN_2);
}
/********************************************************/	


/************����WTIM1���ʹ�� 64/2 = 32λ��ʱ��ʾ��***************/	
void WTIM1_Init(u16  fre) //��ʱ��1������ʱ����ʼ��
{
	   //ʹ��TIMER1����
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);
    //TimerConfigure(TIMER1_BASE, TIMER_CFG_ONE_SHOT);  //���μ���ģʽ
    //TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);//�����ڼ���ģʽ
    TimerConfigure(WTIMER1_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC);  //�����Լ���ģʽ ���ö�ʱ����ֺ���Ҫʹ�õĶ�ʱ��ģʽ

		//һ����˵��ʱ������ֵΪSysCtlClockGet()/N-1����ʱʱ��Ϊ1/���롣
		TimerLoadSet( WTIMER1_BASE,  TIMER_A,
                          SysCtlClockGet()/(1000 * fre)-1);

			//Ϊ��ʱ��Aע���жϺ���
		TimerIntRegister( WTIMER1_BASE,  TIMER_A,
															 WTIM1_Period_Handler);
			//ʹ��time0�Ķ�ʱ��AΪ��ʱ�ж�
		TimerIntEnable( WTIMER1_BASE,  TIMER_TIMA_TIMEOUT);
			//�����ж����ȼ�
		IntPrioritySet(INT_WTIMER1A,  0);
			//ʹ���ж�
		IntEnable( INT_WTIMER1A);
		IntMasterEnable();
			//ʹ�ܶ�ʱ��
		TimerEnable( WTIMER1_BASE,  TIMER_A);


			
}
void WTIM1_Period_Handler() //��ʱ��1  32λ��ֶ�ʱ��AS�жϴ�����
{

	static uint32_t time_count=0;  //��ʱ��
	static uint8_t trigger=0;      //led��ת��־λ��
	
	
  
	uint32_t status=TimerIntStatus( WTIMER1_BASE,  true); //��ȡ״̬  �����Ǹ�ture���Ƿ����λ�ԭʼ�ж�״̬����
	TimerIntClear( WTIMER1_BASE,  status);  //����жϱ�־λ

	uwTick++;
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,trigger ^= GPIO_PIN_2);

}
/********************************************************/	



///************PWM����ʹ�� ʾ�� PD1 PE4***************/
//void PWM1_Init()
//{
//	    //��Ϊ������ʱ��������80MHz�������������һ��Ƶ����Ϊ80��Ƶ����ôPWMʱ�Ӿ���10MHz
//	SysCtlPWMClockSet( SYSCTL_PWMDIV_8);
//    //ʹ��GPIOF��PWM1
//  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD);
//	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE);
//	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
//    //ΪGPIOA_PIN_1��GPIOA_PIN_6����PWM�ź�
//	GPIOPinTypePWM( GPIO_PORTD_BASE,  GPIO_PIN_1);
//	GPIOPinTypePWM( GPIO_PORTE_BASE,  GPIO_PIN_4);
//    //��GPIOF_PIN_2��GPIOF_PIN_3ʹ�����Ÿ���
//	GPIOPinConfigure( GPIO_PD1_M1PWM1);
//	GPIOPinConfigure( GPIO_PE4_M1PWM2);
//    //����PWM1ģ��ĵ��ĸ�������Ϊ���¼����벻ͬ������  ͬ���������ǲ���һģһ����PWM����
//	PWMGenConfigure( PWM1_BASE,  PWM_GEN_0,
//                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
//	PWMGenConfigure( PWM1_BASE,  PWM_GEN_1,
//                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
//    //����PWM1ģ��ĵ�1��������ÿ����������Ϊ10000��������PWMʱ��Ϊ10MHz��
//    // ��ôPWM���Ƶ�ʾ���10^7/10000Ϊ1KHz�����������Ϊ16λ�Ĵ��������ܳ���65535  �����32��ARR
//	PWMGenPeriodSet( PWM1_BASE,  PWM_GEN_0,
//                             10000);
//		//����PWM1ģ��ĵ�1��������ÿ����������Ϊ20000��������PWMʱ��Ϊ10MHz��
//    // ��ôPWM���Ƶ�ʾ���10^7/20000Ϊ500Hz�����������Ϊ16λ�Ĵ��������ܳ���65535  �����32��TIM ARR
//	PWMGenPeriodSet( PWM1_BASE,  PWM_GEN_1,
//                             20000);
//    //����PWM1ģ��ĵڶ���ͨ����ռ�ձ�Ϊ10%����������ĵ���������Ϊ�����ڵĸߵ�ƽ���� �����32��TIM��CRR
//   // ���Կ���ͨ��PWMGenPeriodGet�ó�һ�������ڵļ��������ٳ�0.1Ȼ���1����
//	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_1,
//                              PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)*0.1 - 1);
//    //ͬ��ֻ���������õ�����ͨ�� ռ�ձ�Ϊ90%
//	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_2,
//                              PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*0.9 - 1);
//    //ʹ�ܵڶ���ͨ��
//	PWMOutputState( PWM1_BASE,  PWM_OUT_1_BIT,
//                            true);         //��Ϊfalse ����
//		//ʹ�ܵ�����ͨ��
//	PWMOutputState( PWM1_BASE,  PWM_OUT_2_BIT,
//                            true);
//    //ʹ�ܵ�����������
//	PWMGenEnable( PWM1_BASE,  PWM_GEN_0);
//	PWMGenEnable( PWM1_BASE,  PWM_GEN_1);
//}


/********************************************************/	



void Motor_Init()
{
	    //��Ϊ������ʱ��������80MHz�������������һ��Ƶ����Ϊ80��Ƶ����ôPWMʱ�Ӿ���10MHz
	//SysCtlPWMClockSet( SYSCTL_PWMDIV_8);
    //ʹ��GPIOB��PWM0
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0);
	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	GPIOPinConfigure(GPIO_PB5_M0PWM3);
	GPIOPinConfigure(GPIO_PB6_M0PWM0);
	GPIOPinConfigure(GPIO_PB7_M0PWM1);
    //ΪGPIOB_PIN_4��GPIOB_PIN_5����PWM�ź�
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_5);
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_4);
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_6);
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_7);


	PWMGenConfigure( PWM0_BASE,  PWM_GEN_0,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure( PWM0_BASE,  PWM_GEN_1,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);


   // ��ôPWM���Ƶ�ʾ���10^7/10000Ϊ1KHz�����������Ϊ16λ�Ĵ��������ܳ���65535  �����32��ARR
	PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_0,
                             SysCtlClockGet() / 64 / 1000 - 1);
	
	PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_1,
                             SysCtlClockGet() / 64 / 1000 - 1);
	
	//����CCR
		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_0,                             
														1);

		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_1,                             
														1);
	
		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_2,                             
														1);

		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_3,
                            1);
	
		 //ʹ�ܵ�һ��ͨ��
	PWMOutputState( PWM0_BASE,  PWM_OUT_0_BIT,
                           true);         //��Ϊfalse ����

	    //ʹ�ܵڶ���ͨ��
	PWMOutputState( PWM0_BASE,  PWM_OUT_1_BIT,
                           true);         //��Ϊfalse ����
		//ʹ�ܵ�����ͨ��
	PWMOutputState( PWM0_BASE,  PWM_OUT_2_BIT,
                            true);
		//ʹ�ܵ��ĸ�ͨ��
	PWMOutputState( PWM0_BASE,  PWM_OUT_3_BIT,
                            true);
														
	PWMGenEnable( PWM0_BASE,  PWM_GEN_0);
	PWMGenEnable( PWM0_BASE,  PWM_GEN_1);

}	

void Servo_Init()  //PE4 PE5
{
	//��Ϊ������ʱ��������80MHz�������������һ��Ƶ����Ϊ8��Ƶ����ôPWMʱ�Ӿ���10MHz
  
    //ʹ��GPIOB��PWM0
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0);


	
	GPIOPinConfigure(GPIO_PE4_M0PWM4);
	GPIOPinConfigure(GPIO_PE5_M0PWM5);
	
	GPIOPinTypePWM( GPIO_PORTE_BASE,  GPIO_PIN_4);
	GPIOPinTypePWM( GPIO_PORTE_BASE,  GPIO_PIN_5);
	
		PWMGenConfigure(PWM0_BASE,  PWM_GEN_2,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	 //����50HZ����
		PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_2,
                             SysCtlClockGet() / 64 / 50 - 1);
	
		//����CCR
	  PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_4,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*0.5 - 1));                             
		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_5,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_2)*0.5 - 1));				

		PWMOutputState( PWM0_BASE,  PWM_OUT_4_BIT,
													true);
													
		PWMOutputState( PWM0_BASE,  PWM_OUT_5_BIT,
													true);
													
		PWMGenEnable( PWM0_BASE,  PWM_GEN_2);

}

void Buzzer_Init() //PC4
{
		//��Ϊ������ʱ��������80MHz�������������һ��Ƶ����Ϊ80��Ƶ����ôPWMʱ�Ӿ���10MHz
	//SysCtlPWMClockSet( SYSCTL_PWMDIV_8);
    //ʹ��GPIOB��PWM0
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0);

	GPIOPinConfigure(GPIO_PC4_M0PWM6);
	GPIOPinTypePWM( GPIO_PORTC_BASE,  GPIO_PIN_4);
	
		PWMGenConfigure(PWM0_BASE,  PWM_GEN_3,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	 //����50HZ����
		PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_3,
                             (10000 * 20));
	
		//����CCR
	  PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_6,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3)*0.5 - 1));                             
			

		PWMOutputState( PWM0_BASE,  PWM_OUT_6_BIT,
													true);
													
													
		PWMGenEnable( PWM0_BASE,  PWM_GEN_3);

}

/************��ʱ��PWM���벶��ʹ�� ʾ��***************/

//void TIM_Capture_Init()
//{
//	
//	
//	//ʹ�ܶ�ʱ����GPIO
//   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    //ʹ�����Ÿ���
//	GPIOPinConfigure(GPIO_PB7_T0CCP1);
//    //���������ź�
//	GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_7);
//    //�������ŷ���ע����Ȼ�������벶�񣬵�������������PWM�źſ��ƣ�����Ӳ�����ƣ�Ҫ����ΪGPIO_DIR_MODE_HW
////	GPIODirModeSet( GPIO_PORTB_BASE,  GPIO_PIN_7,
////                            GPIO_DIR_MODE_HW);
//    //����Ϊ������������
//	GPIOPadConfigSet( GPIO_PORTB_BASE,  GPIO_PIN_7,
//                              GPIO_STRENGTH_2MA,  GPIO_PIN_TYPE_STD_WPU);
//    //��Ϊ�����벶��ֻ���ڲ��ģʽ�¿��������벶�����Խ�TIMER_CFG_SPLIT_PAIR��A���ڼ������л�����
//	TimerConfigure( TIMER0_BASE,  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP);
//	//����Ϊ�����ش���
//	TimerControlEvent( TIMER0_BASE,  TIMER_B,
//                               TIMER_EVENT_POS_EDGE);
//    //ע���жϺ���
//	TimerIntRegister( TIMER0_BASE,  TIMER_B,
//                             PWM_IN_IRQHandler);
//    //�����ж����ȼ�
//	IntPrioritySet( INT_TIMER0B,
//                            0);
//    //ʹ�ܶ�ʱ���жϵļ�ʱ�ж�
//	TimerIntEnable( TIMER0_BASE,  TIMER_CAPB_EVENT);
//    //ʹ���ж�
//	IntEnable( INT_TIMER0B);
//	IntMasterEnable();
//	TimerEnable( TIMER0_BASE,  TIMER_B);
//    /*����װ��ֵ���ڱ��ؼ�ʱģʽ�¿���ʡ�ԣ����Լ�����Ĭ��ֵ��
//    ���������Ԥ��Ƶֵ����ôĬ��װ��ֵ����2^24,���û��Ԥ��Ƶֵ����ôĬ��װ��ֵ����2^16��
//    �൱��STM32��ʹ����oc����toggleģʽ��Ĭ��Ԥװ��ֵ��д65535*/
//    //TimerLoadSet(TIMER0_BASE, TIMER_A, Capture_LoadSet);

//}

// uint32_t capture_1=0,capture_2=0,capture_3=0;
// uint32_t timer_flag=0;          //��־λ
// uint32_t duty=0;              //ռ�ձ�
// uint32_t freq=0;             //Ƶ��
// uint32_t up_count=0,down_count=0;  //����ֵ
//void PWM_IN_IRQHandler()
//{
//	//��ȡ�ж�״̬
//   uint32_t status=TimerIntStatus( TIMER0_BASE,  true);
//    //����жϱ�־λ
//	TimerIntClear( TIMER0_BASE,  status);
//    //��һ�ν��ж������ڼ�⵽�������أ�Ȼ�󽫼�ʱֵ��ȡ���������ؼ���Ϊ�½���
//	if(timer_flag==0)
//	{
//		TimerControlEvent( TIMER0_BASE,  TIMER_B,
//                               TIMER_EVENT_NEG_EDGE);
//		capture_1=TimerValueGet( TIMER0_BASE,  TIMER_B);
//		timer_flag=1;
//	}
//    //�ڶ��ν��ж�����Ϊ��⵽���½��أ�Ȼ�󽫼�ʱֵ��ȡ����ʱ���Ѿ�����˸ߵ�ƽ����
//    //���Լ����ռ�ձȣ��������ؼ���Ϊ������
//	else if(timer_flag==1)
//	{
//		TimerControlEvent( TIMER0_BASE,  TIMER_B,
//                               TIMER_EVENT_POS_EDGE);
//		capture_2=TimerValueGet( TIMER0_BASE,  TIMER_B);
//		timer_flag=2;
//	}
//    //�����ν��ж�ʱ��Ϊ��⵽�������أ����ˣ��Ѿ���⵽�����������أ�Ҳ�Ϳ��Եõ�����ֵ
//	else if(timer_flag==2)
//	{
//	    timer_flag=0;
//		capture_3=TimerValueGet( TIMER0_BASE,  TIMER_B);
//        /* ____   ___ capture_1�൱�ڼ�⵽��һ�������ؼǵ�����
//           |  |   |   capture_2�൱�ڼ�⵽��һ���½��ؼǵ���
//          _|  |___|   ����capture_2��capture_1֮�伴Ϊ�ߵ�ƽ��
//        capture_3�൱�ڼ�⵽�ڶ��������ؼǵ���������capture_3��capture_1֮��Ϊ������*/
//        /*  /|   /| ����Ҫ��ռ�ձȺ�Ƶ�ʣ���Ϊ���õ��Ƕ�ʱ��A�����ԼӼ�����
//           / |  / | ��ʱ��A�ǵ����ȵ����Ȼ���ٴ�0��ʼ����������ͨ����ߵ�ƽ�͵͵�ƽʱ��������
//          /  | /  | ���capture_1��capture_2���ڵ�һ���������ڵ������׶Σ���1��2�Ĳ���Ǹߵ�ƽ
//         /   |/   | ���1��2�ֱ������������ڵ������׶Σ��Ǹߵ�ƽ��Ҫͨ��0xffff-capture_1+capture_2��á�
//        ���capture_2��capture_3���ڵ�һ���������ڵ������׶Σ���2��3�Ĳ���ǵ͵�ƽ��
//        ����ֱ������������������׶Σ��͵�ƽ��Ҫͨ��0xffff-capture_2+capture_3�����*/
//		if(capture_2>capture_1)
//		{
//		    up_count=capture_2-capture_1;
//		}
//		else
//		{
//			printf("flag1");
//		    up_count=0xffff-capture_1+capture_2;
//		}
//		if(capture_3>capture_2)
//		{
//		    down_count=capture_3-capture_2;
//		}
//		else 
//		{
//			printf("flag2");
//		    down_count=0xffff-capture_2+capture_3;
//		}
//        //Ƶ������Ƶ�����ڼ��ɵõ�
//		freq=SysCtlClockGet()/(up_count+down_count);
//        //ռ�ձ�Ϊ�ߵ�ƽռ���ڵı�ֵ���ɵõ�
//		duty=up_count*100/(up_count+down_count);
//	}



//}

/********************************************************/

/********************QEIģʽ����****************************/


void Motor_Encoder_Init(void)
{
	//����QEI0��GPIOD������ʱ��
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	
	//����PD7  TM4C123x��PF0��PD7���������ڽ����󷽿���ָ���ܽŹ���
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //����
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80; //ȷ��
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;  //��������
	
	//����QEIʹ�õ�GPIO��
	GPIOPinTypeQEI(GPIO_PORTD_BASE , GPIO_PIN_6 | GPIO_PIN_7);
	GPIOPinTypeQEI(GPIO_PORTC_BASE , GPIO_PIN_5 | GPIO_PIN_6);
	
	//����GPIO�ڱ��ýӿ�
	GPIOPinConfigure(GPIO_PD7_PHB0);
	GPIOPinConfigure(GPIO_PD6_PHA0);
	GPIOPinConfigure(GPIO_PC5_PHA1);
	GPIOPinConfigure(GPIO_PC6_PHB1);
	
	//����QEI������ʹ��ABͨ����ʹ���������񡢲���ǰABͨ�����ý�����һȦ����������Ϊ0
	QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 12000);
	QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 12000);
	QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1,  SysCtlClockGet()/100); //����QEI�ٶȲ���ģʽ
	QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1,  SysCtlClockGet()/100); //����QEI�ٶȲ���ģʽ
	QEIVelocityEnable(QEI0_BASE);  //ʹ���ٶȲ���
	QEIVelocityEnable(QEI1_BASE);  //ʹ���ٶȲ���
	QEIEnable(QEI0_BASE); //ʹ��QEI
	QEIEnable(QEI1_BASE); //ʹ��QEI
	//��������ʼֵ
	QEIPositionSet(QEI0_BASE , 0);
	QEIPositionSet(QEI1_BASE , 0);
	
	//��ʼ����ʱ��0����QEI0����
	//TimerQEIinit();
}

void TimerQEIinit(void)
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3); // ʹ�ܶ�ʱ��3����
IntMasterEnable(); // ʹ��ȫ���ж�
TimerConfigure(TIMER3_BASE , TIMER_CFG_PERIODIC); // ���ö�ʱ��3Ϊ����ģʽ
TimerLoadSet(TIMER3_BASE , TIMER_A , SysCtlClockGet() / 100); // ���ö�ʱ��3�ļ���ֵ
IntEnable(INT_TIMER3A); // ʹ�ܶ�ʱ��3�Ķ�ʱ��A�ж�
TimerEnable(TIMER3_BASE , TIMER_A); // ������ʱ��3�Ķ�ʱ��A
TimerIntEnable(TIMER3_BASE , TIMER_TIMA_TIMEOUT); // ʹ�ܶ�ʱ��3�Ķ�ʱ��A��ʱ�ж�
QEIVelocityGet(QEI0_BASE); // ��ȡQEI0���ٶ�
QEIVelocityGet(QEI1_BASE); // ��ȡQEI1���ٶ�
TimerEnable(TIMER3_BASE , TIMER_A); // ����������ʱ��3�Ķ�ʱ��A
TimerIntRegister(TIMER3_BASE , TIMER_A , QQ_Handler); // ע�ᶨʱ��3�Ķ�ʱ��A�жϴ�����
	printf("TIME3 OK \r\n");
}

void QQ_Handler(void)
{
	uint8_t Velocity;
	int Ture_V;
	TimerIntClear(TIMER3_BASE , TIMER_TIMA_TIMEOUT);
	Velocity = QEIVelocityGet(QEI1_BASE);
	Ture_V = QEIDirectionGet(QEI1_BASE) * Velocity;
	printf("�ٶ���:%d\r\n" , Ture_V);
	//SysCtlDelay(200);
}

/********************************************************/
