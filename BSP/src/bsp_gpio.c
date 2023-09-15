

#include "bsp_gpio.h"
#include "lcd.h"


void GPIO_Init()
{
  /************配置PF1 PF2 PF3 输出RGB （io口输出示例）***************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);																				//使能PF时钟
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);						//配置引脚为GPIO输出，底层是GPIOPadConfigSet和GPIODirModeSet  //para1: 总线地址 para2: io口地址      
	//SysCtlPeripheralReady(); 常用检测时钟配置 while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  //GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); //io口输出模式配置  //para1: 总线地址 para2: io口地址 para3: 输出电流大小  para4:输出模式
	/*GPIO_PIN_TYPE_STD_WPU弱上拉
		GPIO_PIN_TYPE_STD_WPD弱下拉
		GPIO_PIN_TYPE_STD为推挽引脚
		GPIO_PIN_TYPE_OD为开漏
		GPIO_PIN_TYPE_ANALOG模拟输入
		GPIO_PIN_TYPE_WAKE_HIGH高电平唤醒
		GPIO_PIN_TYPE_WAKE_LOW低电平唤醒	*/
	/**********************************************/
	
	
	

	/************配置PF4 PF0 SW1 SW2开关输入(外部中断示例)  注意PF0有上锁***************/
	HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;  //解锁PF0
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);										//使能PF时钟
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);  //配置输入模式
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//推挽上拉(按理说上面那个已经内部自带这个推挽输出 但是不知道为什么不再加这个函数一次按键就会异常)
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE); //配置中断模式 下降沿触发
	
	GPIOIntRegister(GPIO_PORTF_BASE, KEY_EXIT_Handler);  //注册中断 绑定中断处理函数
	
	IntPrioritySet(INT_GPIOF|GPIO_PIN_4, 0); // 设置中断优先级，TM4C123G的中断优先级有8个，0最高
	//下面是开始三启中断三件套
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //IO中断口使能
	IntEnable(INT_GPIOF);  //Port中断使能 发现了一个东西 这个不能和 #include "inc/hw_ints.h" 头文件连用 连用就报错
	IntMasterEnable();			//开启总中断
	/**********************************************/
	
}



void LCD_IO_Init()
{
/******************LCD IO口初始化 ***************************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);																				//使能PB时钟
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);																				//使能PB时钟
	GPIOPinTypeGPIOOutput(LCD_DC_GPIO_Port, LCD_DC_Pin);	
	GPIOPinTypeGPIOOutput(LCD_RES_GPIO_Port, LCD_RES_Pin);
	GPIOPinTypeGPIOOutput(LCD_CS_GPIO_Port, LCD_CS_Pin);

	GPIOPinWrite(LCD_CS_GPIO_Port, LCD_CS_Pin, LCD_CS_Pin);  //拉高lcd cs片选脚
}










