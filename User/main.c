
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

	//static uint8_t trigger=0;      //led翻转标志位置	
//		// Turn on the LED ：PF1(R),PF2(B),PF3(G)
//		//使能对应的位置为高电平 注意这里赋的值与引脚号有关 0为1 1为2 2为4类比等等  所以用宏定义就显着重要
	//GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3,trigger ^= GPIO_PIN_3);
//		// Delay for a bit		
//	//MPU6050验证 也是iic验证
//MPU6050_Read_Data(&Gyro, &Acc, &Temp);
//	printf("3轴陀螺仪:%d\t%d\t%d\r\n",(int16_t)(Gyro.x),(int16_t)(Gyro.y),(int16_t)(Gyro.z));
//	printf("3轴加速度:%d\t%d\t%d\r\n",(int16_t)(Acc.x),(int16_t)(Acc.y),(int16_t)(Acc.z));
//	printf("IMU温度℃:%f\r\n",Temp);
//		
//	//定时器输入捕获验证	
//	//printf("d: %d %%, p: %d\r\n",duty,freq);
//	
//		
//	 // 启动ADC转换
//	ADCProcessorTrigger(ADC0_BASE, 0);

//	// 等待转换完成
//	while(!ADCIntStatus(ADC0_BASE, 0, false)) {}



//	// 从ADC缓冲区读取数据

//	ADCSequenceDataGet(ADC0_BASE, 0, adcValue);


//	printf("adc1:%d\r\n",adcValue[0]);

//	// 清除中断标志
//	ADCIntClear(ADC0_BASE, 0);

//  //
		

}

void All_Init()
{
	Sys_Tick_Init();
	GPIO_Init(); 
	
	LCD_IO_Init();
	
	USART_Init();
	
	TIM0_Init(1);//配置定时器以1s运行	
	WTIM1_Init(1);//配置定时器以1ms运行	
	
	//ADC_Init();
	BAT_ADC_Init();
	
	I2C_Init();
	SSI_Init();
	

//	
//	    
	
	


}


/*
		1、	选择外部主震荡器作为系统时钟，并用来驱动PLL倍频(400M)，设置其频率为16MHz，系统时钟分频数为4（系统时钟频率为400M/2.5/2=80M）
				SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_XTAL_16MHZ|(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN)); 
	
		2、	地址总线的[9:2]位是屏蔽位，可以直接对GPIODATA数据寄存器的多个位进行修改
				GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3, ui8LED);	
				向PF base地址写值ui8LED，第3:2:1位关联修改，按原理图分析，写1亮灯

		3、 SysCtlDelay()这个函数利用汇编，提供了跨越工具链时恒定的延迟。延时3*n个时钟周期
				可以用SysCtlDelay(n*(SysCtlClockGet()/3000));恒定延时1ms，而不用考虑系统时钟频率
				但是要注意：不管用哪个时钟源，只要工作频率高于40MHz，就会导致实际延时时间大于设置值。原因好像是芯片内部Flash的读取频率最大只能达到40M，
										当工作频率大于40MHz时，通过预取两个字的指令来达到80M的运行主频。
										但是，当遇到SysCtlDelay函数这种短跳转时这个特性并不能很好的工作，每次都需要读取指令，所以时间就延长了
				也就是说如果主频大于40M，SysCtlDelay(n*(SysCtlClockGet()/3000))这个方法也不是很准，可以考虑用ROM_SysCtlDelasy()
*/	


/******************************************************************************
      函数说明：时钟初始化  主频率为80MHZ（最大频率） 400/2/2.5
      入口数据：无    
      返回值：  无
******************************************************************************/
void Sys_Tick_Init()
{
  //板子时钟是16MHZ 故外部时钟用16MHZ
	
	SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_XTAL_16MHZ|(SYSCTL_USE_PLL|SYSCTL_OSC_MAIN)); //系统时钟分频器系数|选择外部晶振频率|使用PLL锁相环作为系统时钟源|时钟源
	//分频系数SYSCTL_SYSDIV_1,SYSCTL_SYSDIV_2, SYSCTL_SYSDIV_3, SYSCTL_SYSDIV_64…
	SysCtlPWMClockSet( SYSCTL_PWMDIV_64);
	/*外部晶振频率有SYSCTL_XTAL_4MHZ, SYSCTL_XTAL_4_09MHZ, SYSCTL_XTAL_4_91MHZ,

		SYSCTL_XTAL_5MHZ, SYSCTL_XTAL_5_12MHZ, SYSCTL_XTAL_6MHZ,

		SYSCTL_XTAL_6_14MHZ, SYSCTL_XTAL_7_37MHZ, SYSCTL_XTAL_8MHZ,

		SYSCTL_XTAL_8_19MHZ, SYSCTL_XTAL_10MHZ, SYSCTL_XTAL_12MHZ,

		SYSCTL_XTAL_12_2MHZ, SYSCTL_XTAL_13_5MHZ, SYSCTL_XTAL_14_3MHZ,

		SYSCTL_XTAL_16MHZ, SYSCTL_XTAL_16_3MHZ, SYSCTL_XTAL_18MHZ,

		SYSCTL_XTAL_20MHZ, SYSCTL_XTAL_24MHZ, or SYSCTL_XTAL_25MHz. */
	
	// 使用pll锁相环时钟频率为400MHZ 经过系统框图 2分频 再2.5分频得到系统支持的最大时钟频率80MHZ 不使用pll锁相环 则为 SYSCTL_USE_OSC
	
	
	//时钟源 SYSCTL_OSC_MAIN,	SYSCTL_OSC_INT, SYSCTL_OSC_INT4, SYSCTL_OSC_INT30, or SYSCTL_OSC_EXT32.
	//区别如下
			/*SYSCTL_OSC_MAIN：使用外部晶体振荡器作为主系统时钟源。这是最常用的选项，适用于大多数应用场景。

			SYSCTL_OSC_INT：使用内部低频振荡器作为主系统时钟源。这是一种省电的选项，适用于低功耗的应用，但可能会牺牲一些性能。

			SYSCTL_OSC_INT4：使用内部4 MHz振荡器作为主系统时钟源。这是一种高性能的选项，适用于需要更快时钟速度的应用。

			SYSCTL_OSC_INT30：使用内部30 KHz振荡器作为主系统时钟源。这是一种极低功耗的选项，适用于要求极低功耗的应用，但时钟速度较慢。

			SYSCTL_OSC_EXT32：使用外部32.768 KHz振荡器作为主系统时钟源。这是一种低功耗选项，适用于需要精确计时的应用，如实时时钟。*/
}

/******************************************************************************
      函数说明：系统延时n毫秒 SysCtlDelay(SysCtlClockGet() / n / 3);  //延时，延时时间=1/n秒
      入口数据：无    
      返回值：  无
******************************************************************************/
void My_Delay_ms(u32 n)
{
	u32 count;
	count=SysCtlClockGet()/1000;		//SysCtlClockGet获取时钟频率 这是为80M，单位MHz,除10^3，频率为countKHz。也就是每秒有1000count个时钟周期，每个count对应的总周期长1ms
	SysCtlDelay(n*count/3);					//SysCtlDelay延时（3*参数）个时钟周期，这里延时3*n*count/3=n*count个周期，即n毫秒

}

void My_Delay_us(u32 n)
{
	u32 count;
	count=SysCtlClockGet()/1000000;		//SysCtlClockGet获取时钟频率 这是为80M，单位MHz,除10^6，频率为countKHz。也就是每秒有1count个时钟周期，每个count对应的总周期长1us
	SysCtlDelay(n*count/3);					//SysCtlDelay延时（3*参数）个时钟周期，这里延时3*n*count/3=n*count个周期，即n微秒

}