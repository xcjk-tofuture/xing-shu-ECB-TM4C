#include "bsp_tim.h"

u32 uwTick;


//TI家的定时器分为16/32 定时器 和 32/64宽定时器两种  可分别拆分/级联使用
/************基本定时器使用***************/
/************配置TIM0级联使用 32位定时器示例***************/	
void TIM0_Init(u16  fre)  //定时器3级联使用初始化
{
	

    //使能TIMER3外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    //TimerConfigure(TIMER0_BASE, TIMER_CFG_ONE_SHOT);  //单次计数模式
    //TimerConfigure(TIMER0_BASE, TIMER_CFG_A_PERIODIC);//单周期计数模式
    TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);  //周期性计数模式
 
     //一般来说定时器加载值为SysCtlClockGet()/N-1，定时时间为1/N秒。
    TimerLoadSet(TIMER3_BASE, TIMER_A,(SysCtlClockGet() / fre) - 1);
 
    //使能Timer3A的中断
    IntEnable(INT_TIMER3A);
 
    //配置中断源，配置为超时时产生中断
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
 
    //使能对处理器的中断
    IntMasterEnable();
 
   //为Timer3A注册中断处理函数   级联的情况下默认都是设置定时器A
    TimerIntRegister(TIMER3_BASE,TIMER_A,TIM0_Period_Handler);
 
    //使能TIMER3A
		TimerEnable( TIMER3_BASE,  TIMER_A);
		
}	



void TIM0_Period_Handler()  //定时器3  32位级联定时器
{
	 static uint32_t time_count=0;  //计时数
	// static uint8_t trigger=0;      //led翻转标志位置
	

	
	
  uint32_t status=TimerIntStatus( TIMER3_BASE,  true); //获取状态  后面那个ture是是否屏蔽或原始中断状态返回
	TimerIntClear( TIMER3_BASE,  status);  //清除中断标志位

	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,trigger ^= GPIO_PIN_2);
}
/********************************************************/	


/************配置WTIM1拆分使用 64/2 = 32位定时器示例***************/	
void WTIM1_Init(u16  fre) //定时器1级联定时器初始化
{
	   //使能TIMER1外设
    SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER1);
    //TimerConfigure(TIMER1_BASE, TIMER_CFG_ONE_SHOT);  //单次计数模式
    //TimerConfigure(TIMER1_BASE, TIMER_CFG_A_PERIODIC);//单周期计数模式
    TimerConfigure(WTIMER1_BASE, TIMER_CFG_SPLIT_PAIR|TIMER_CFG_A_PERIODIC);  //周期性计数模式 配置定时器拆分和需要使用的定时器模式

		//一般来说定时器加载值为SysCtlClockGet()/N-1，定时时间为1/毫秒。
		TimerLoadSet( WTIMER1_BASE,  TIMER_A,
                          SysCtlClockGet()/(1000 * fre)-1);

			//为定时器A注册中断函数
		TimerIntRegister( WTIMER1_BASE,  TIMER_A,
															 WTIM1_Period_Handler);
			//使能time0的定时器A为超时中断
		TimerIntEnable( WTIMER1_BASE,  TIMER_TIMA_TIMEOUT);
			//设置中断优先级
		IntPrioritySet(INT_WTIMER1A,  0);
			//使能中断
		IntEnable( INT_WTIMER1A);
		IntMasterEnable();
			//使能定时器
		TimerEnable( WTIMER1_BASE,  TIMER_A);


			
}
void WTIM1_Period_Handler() //定时器1  32位拆分定时器AS中断处理函数
{

	static uint32_t time_count=0;  //计时数
	static uint8_t trigger=0;      //led翻转标志位置
	
	
  
	uint32_t status=TimerIntStatus( WTIMER1_BASE,  true); //获取状态  后面那个ture是是否屏蔽或原始中断状态返回
	TimerIntClear( WTIMER1_BASE,  status);  //清除中断标志位

	uwTick++;
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2,trigger ^= GPIO_PIN_2);

}
/********************************************************/	



///************PWM生成使用 示例 PD1 PE4***************/
//void PWM1_Init()
//{
//	    //因为设置了时钟总线是80MHz，所以在这里分一下频设置为80分频，那么PWM时钟就是10MHz
//	SysCtlPWMClockSet( SYSCTL_PWMDIV_8);
//    //使能GPIOF与PWM1
//  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD);
//	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE);
//	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM1);
//    //为GPIOA_PIN_1与GPIOA_PIN_6分配PWM信号
//	GPIOPinTypePWM( GPIO_PORTD_BASE,  GPIO_PIN_1);
//	GPIOPinTypePWM( GPIO_PORTE_BASE,  GPIO_PIN_4);
//    //对GPIOF_PIN_2与GPIOF_PIN_3使能引脚复用
//	GPIOPinConfigure( GPIO_PD1_M1PWM1);
//	GPIOPinConfigure( GPIO_PE4_M1PWM2);
//    //设置PWM1模块的第四个发生器为向下计数与不同步计数  同步计数就是产生一模一样的PWM波形
//	PWMGenConfigure( PWM1_BASE,  PWM_GEN_0,
//                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
//	PWMGenConfigure( PWM1_BASE,  PWM_GEN_1,
//                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
//    //设置PWM1模块的第1个发生器每个计数周期为10000个数，而PWM时钟为10MHz，
//    // 那么PWM输出频率就是10^7/10000为1KHz，但是这个数为16位寄存器，不能超过65535  类比于32的ARR
//	PWMGenPeriodSet( PWM1_BASE,  PWM_GEN_0,
//                             10000);
//		//设置PWM1模块的第1个发生器每个计数周期为20000个数，而PWM时钟为10MHz，
//    // 那么PWM输出频率就是10^7/20000为500Hz，但是这个数为16位寄存器，不能超过65535  类比于32的TIM ARR
//	PWMGenPeriodSet( PWM1_BASE,  PWM_GEN_1,
//                             20000);
//    //设置PWM1模块的第二个通道的占空比为10%，这个函数的第三个参数为周期内的高电平数， 类比与32的TIM的CRR
//   // 所以可以通过PWMGenPeriodGet得出一个周期内的计数总数再乘0.1然后减1就行
//	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_1,
//                              PWMGenPeriodGet(PWM1_BASE, PWM_GEN_0)*0.1 - 1);
//    //同理，只不过是设置第三个通道 占空比为90%
//	PWMPulseWidthSet( PWM1_BASE,  PWM_OUT_2,
//                              PWMGenPeriodGet(PWM1_BASE, PWM_GEN_1)*0.9 - 1);
//    //使能第二个通道
//	PWMOutputState( PWM1_BASE,  PWM_OUT_1_BIT,
//                            true);         //若为false 则反向
//		//使能第三个通道
//	PWMOutputState( PWM1_BASE,  PWM_OUT_2_BIT,
//                            true);
//    //使能第三个发生器
//	PWMGenEnable( PWM1_BASE,  PWM_GEN_0);
//	PWMGenEnable( PWM1_BASE,  PWM_GEN_1);
//}


/********************************************************/	



void Motor_Init()
{
	    //因为设置了时钟总线是80MHz，所以在这里分一下频设置为80分频，那么PWM时钟就是10MHz
	//SysCtlPWMClockSet( SYSCTL_PWMDIV_8);
    //使能GPIOB与PWM0
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0);
	GPIOPinConfigure(GPIO_PB4_M0PWM2);
	GPIOPinConfigure(GPIO_PB5_M0PWM3);
	GPIOPinConfigure(GPIO_PB6_M0PWM0);
	GPIOPinConfigure(GPIO_PB7_M0PWM1);
    //为GPIOB_PIN_4与GPIOB_PIN_5分配PWM信号
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_5);
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_4);
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_6);
	GPIOPinTypePWM( GPIO_PORTB_BASE,  GPIO_PIN_7);


	PWMGenConfigure( PWM0_BASE,  PWM_GEN_0,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	PWMGenConfigure( PWM0_BASE,  PWM_GEN_1,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);


   // 那么PWM输出频率就是10^7/10000为1KHz，但是这个数为16位寄存器，不能超过65535  类比于32的ARR
	PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_0,
                             SysCtlClockGet() / 64 / 1000 - 1);
	
	PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_1,
                             SysCtlClockGet() / 64 / 1000 - 1);
	
	//设置CCR
		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_0,                             
														1);

		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_1,                             
														1);
	
		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_2,                             
														1);

		PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_3,
                            1);
	
		 //使能第一个通道
	PWMOutputState( PWM0_BASE,  PWM_OUT_0_BIT,
                           true);         //若为false 则反向

	    //使能第二个通道
	PWMOutputState( PWM0_BASE,  PWM_OUT_1_BIT,
                           true);         //若为false 则反向
		//使能第三个通道
	PWMOutputState( PWM0_BASE,  PWM_OUT_2_BIT,
                            true);
		//使能第四个通道
	PWMOutputState( PWM0_BASE,  PWM_OUT_3_BIT,
                            true);
														
	PWMGenEnable( PWM0_BASE,  PWM_GEN_0);
	PWMGenEnable( PWM0_BASE,  PWM_GEN_1);

}	

void Servo_Init()  //PE4 PE5
{
	//因为设置了时钟总线是80MHz，所以在这里分一下频设置为8分频，那么PWM时钟就是10MHz
  
    //使能GPIOB与PWM0
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0);


	
	GPIOPinConfigure(GPIO_PE4_M0PWM4);
	GPIOPinConfigure(GPIO_PE5_M0PWM5);
	
	GPIOPinTypePWM( GPIO_PORTE_BASE,  GPIO_PIN_4);
	GPIOPinTypePWM( GPIO_PORTE_BASE,  GPIO_PIN_5);
	
		PWMGenConfigure(PWM0_BASE,  PWM_GEN_2,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	 //生成50HZ波形
		PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_2,
                             SysCtlClockGet() / 64 / 50 - 1);
	
		//设置CCR
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
		//因为设置了时钟总线是80MHz，所以在这里分一下频设置为80分频，那么PWM时钟就是10MHz
	//SysCtlPWMClockSet( SYSCTL_PWMDIV_8);
    //使能GPIOB与PWM0
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_PWM0);

	GPIOPinConfigure(GPIO_PC4_M0PWM6);
	GPIOPinTypePWM( GPIO_PORTC_BASE,  GPIO_PIN_4);
	
		PWMGenConfigure(PWM0_BASE,  PWM_GEN_3,
                             PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);
	 //生成50HZ波形
		PWMGenPeriodSet( PWM0_BASE,  PWM_GEN_3,
                             (10000 * 20));
	
		//设置CCR
	  PWMPulseWidthSet( PWM0_BASE,  PWM_OUT_6,(PWMGenPeriodGet(PWM0_BASE, PWM_GEN_3)*0.5 - 1));                             
			

		PWMOutputState( PWM0_BASE,  PWM_OUT_6_BIT,
													true);
													
													
		PWMGenEnable( PWM0_BASE,  PWM_GEN_3);

}

/************定时器PWM输入捕获使用 示例***************/

//void TIM_Capture_Init()
//{
//	
//	
//	//使能定时器与GPIO
//   SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//	SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
//    //使能引脚复用
//	GPIOPinConfigure(GPIO_PB7_T0CCP1);
//    //分配引脚信号
//	GPIOPinTypeTimer(GPIO_PORTB_BASE, GPIO_PIN_7);
//    //设置引脚方向，注意虽然这是输入捕获，但是这是由外界的PWM信号控制，属于硬件控制，要设置为GPIO_DIR_MODE_HW
////	GPIODirModeSet( GPIO_PORTB_BASE,  GPIO_PIN_7,
////                            GPIO_DIR_MODE_HW);
//    //设置为推挽上拉输入
//	GPIOPadConfigSet( GPIO_PORTB_BASE,  GPIO_PIN_7,
//                              GPIO_STRENGTH_2MA,  GPIO_PIN_TYPE_STD_WPU);
//    //因为是输入捕获，只有在拆分模式下可以用输入捕获，所以将TIMER_CFG_SPLIT_PAIR与A周期计数进行或运算
//	TimerConfigure( TIMER0_BASE,  TIMER_CFG_SPLIT_PAIR|TIMER_CFG_B_CAP_TIME_UP);
//	//设置为上升沿触发
//	TimerControlEvent( TIMER0_BASE,  TIMER_B,
//                               TIMER_EVENT_POS_EDGE);
//    //注册中断函数
//	TimerIntRegister( TIMER0_BASE,  TIMER_B,
//                             PWM_IN_IRQHandler);
//    //设置中断优先级
//	IntPrioritySet( INT_TIMER0B,
//                            0);
//    //使能定时器中断的计时中断
//	TimerIntEnable( TIMER0_BASE,  TIMER_CAPB_EVENT);
//    //使能中断
//	IntEnable( INT_TIMER0B);
//	IntMasterEnable();
//	TimerEnable( TIMER0_BASE,  TIMER_B);
//    /*设置装载值，在边沿计时模式下可以省略，会自己填入默认值。
//    如果设置了预分频值，那么默认装载值就是2^24,如果没有预分频值，那么默认装载值就是2^16。
//    相当于STM32中使用了oc——toggle模式，默认预装载值填写65535*/
//    //TimerLoadSet(TIMER0_BASE, TIMER_A, Capture_LoadSet);

//}

// uint32_t capture_1=0,capture_2=0,capture_3=0;
// uint32_t timer_flag=0;          //标志位
// uint32_t duty=0;              //占空比
// uint32_t freq=0;             //频率
// uint32_t up_count=0,down_count=0;  //计数值
//void PWM_IN_IRQHandler()
//{
//	//读取中断状态
//   uint32_t status=TimerIntStatus( TIMER0_BASE,  true);
//    //清除中断标志位
//	TimerIntClear( TIMER0_BASE,  status);
//    //第一次进中断是由于检测到了上升沿，然后将计时值读取，并将边沿检测变为下降沿
//	if(timer_flag==0)
//	{
//		TimerControlEvent( TIMER0_BASE,  TIMER_B,
//                               TIMER_EVENT_NEG_EDGE);
//		capture_1=TimerValueGet( TIMER0_BASE,  TIMER_B);
//		timer_flag=1;
//	}
//    //第二次进中断是因为检测到了下降沿，然后将计时值读取，这时就已经获得了高电平数，
//    //可以计算出占空比，并将边沿检测变为上升沿
//	else if(timer_flag==1)
//	{
//		TimerControlEvent( TIMER0_BASE,  TIMER_B,
//                               TIMER_EVENT_POS_EDGE);
//		capture_2=TimerValueGet( TIMER0_BASE,  TIMER_B);
//		timer_flag=2;
//	}
//    //第三次进中断时因为检测到了上升沿，至此，已经检测到了两个上升沿，也就可以得到周期值
//	else if(timer_flag==2)
//	{
//	    timer_flag=0;
//		capture_3=TimerValueGet( TIMER0_BASE,  TIMER_B);
//        /* ____   ___ capture_1相当于检测到第一个上升沿记的数，
//           |  |   |   capture_2相当于检测到第一个下降沿记的数
//          _|  |___|   所以capture_2与capture_1之间即为高电平数
//        capture_3相当于检测到第二个上升沿记的数，所以capture_3与capture_1之间为周期数*/
//        /*  /|   /| 现在要求占空比和频率，因为设置的是定时器A周期性加计数，
//           / |  / | 定时器A记的数先到最大然后再从0开始计数，现在通过求高电平和低电平时间来计算
//          /  | /  | 如果capture_1与capture_2都在第一个计数周期的上升阶段，那1与2的差就是高电平
//         /   |/   | 如果1与2分别落在两个周期的上升阶段，那高电平就要通过0xffff-capture_1+capture_2获得。
//        如果capture_2与capture_3都在第一个计数周期的上升阶段，那2与3的差就是低电平，
//        如果分别落在两个周期上升阶段，低电平就要通过0xffff-capture_2+capture_3来获得*/
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
//        //频率用主频除周期即可得到
//		freq=SysCtlClockGet()/(up_count+down_count);
//        //占空比为高电平占周期的比值即可得到
//		duty=up_count*100/(up_count+down_count);
//	}



//}

/********************************************************/

/********************QEI模式举例****************************/


void Motor_Encoder_Init(void)
{
	//启动QEI0和GPIOD的总线时钟
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	
	//解锁PD7  TM4C123x的PF0和PD7脚有锁，在解锁后方可以指定管脚功能
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY; //解锁
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR) |= 0x80; //确认
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0;  //重新锁定
	
	//配置QEI使用的GPIO口
	GPIOPinTypeQEI(GPIO_PORTD_BASE , GPIO_PIN_6 | GPIO_PIN_7);
	GPIOPinTypeQEI(GPIO_PORTC_BASE , GPIO_PIN_5 | GPIO_PIN_6);
	
	//配置GPIO口备用接口
	GPIOPinConfigure(GPIO_PD7_PHB0);
	GPIOPinConfigure(GPIO_PD6_PHA0);
	GPIOPinConfigure(GPIO_PC5_PHA1);
	GPIOPinConfigure(GPIO_PC6_PHB1);
	
	//配置QEI参数：使用AB通道、使用正交捕获、捕获前AB通道不用交换、一圈脉冲数设置为0
	QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 12000);
	QEIConfigure(QEI0_BASE, QEI_CONFIG_CAPTURE_A_B |QEI_CONFIG_NO_RESET| QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP, 12000);
	QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1,  SysCtlClockGet()/100); //配置QEI速度捕获模式
	QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1,  SysCtlClockGet()/100); //配置QEI速度捕获模式
	QEIVelocityEnable(QEI0_BASE);  //使能速度捕获
	QEIVelocityEnable(QEI1_BASE);  //使能速度捕获
	QEIEnable(QEI0_BASE); //使能QEI
	QEIEnable(QEI1_BASE); //使能QEI
	//编码器初始值
	QEIPositionSet(QEI0_BASE , 0);
	QEIPositionSet(QEI1_BASE , 0);
	
	//初始化定时器0用于QEI0捕获
	//TimerQEIinit();
}

void TimerQEIinit(void)
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3); // 使能定时器3外设
IntMasterEnable(); // 使能全局中断
TimerConfigure(TIMER3_BASE , TIMER_CFG_PERIODIC); // 配置定时器3为周期模式
TimerLoadSet(TIMER3_BASE , TIMER_A , SysCtlClockGet() / 100); // 设置定时器3的加载值
IntEnable(INT_TIMER3A); // 使能定时器3的定时器A中断
TimerEnable(TIMER3_BASE , TIMER_A); // 启动定时器3的定时器A
TimerIntEnable(TIMER3_BASE , TIMER_TIMA_TIMEOUT); // 使能定时器3的定时器A超时中断
QEIVelocityGet(QEI0_BASE); // 获取QEI0的速度
QEIVelocityGet(QEI1_BASE); // 获取QEI1的速度
TimerEnable(TIMER3_BASE , TIMER_A); // 继续启动定时器3的定时器A
TimerIntRegister(TIMER3_BASE , TIMER_A , QQ_Handler); // 注册定时器3的定时器A中断处理函数
	printf("TIME3 OK \r\n");
}

void QQ_Handler(void)
{
	uint8_t Velocity;
	int Ture_V;
	TimerIntClear(TIMER3_BASE , TIMER_TIMA_TIMEOUT);
	Velocity = QEIVelocityGet(QEI1_BASE);
	Ture_V = QEIDirectionGet(QEI1_BASE) * Velocity;
	printf("速度是:%d\r\n" , Ture_V);
	//SysCtlDelay(200);
}

/********************************************************/
