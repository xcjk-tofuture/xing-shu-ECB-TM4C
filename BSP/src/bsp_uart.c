/*
	1、串口配置流程：
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);							//Enable UART0 module
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);							//for UART
		GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);	//PA0&PA1 forUART0
		UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);					//configure the baud clock source theprecision internal oscillator(UART_CLOCK_PIOSC)																											
		UARTStdioConfig(0,9600, 16000000);												//这个函数也是在uartstdio.c里定义的，可以打开文件查看源代码
		
	2、HWREG表示操作硬件寄存器
		
	3、s = GPIOIntStatus(GPIO_PORTF_BASE, true);
		 读取中断状态。TM4C可以设置某些中断被屏蔽，屏蔽的中断信号不会被送到中断控制器，屏蔽位存在GPIOIM寄存器
		 第二个参数写1，则返回不含已屏蔽中断的联合中断状态 return(HWREG(ui32Port + GPIO_O_MIS)); 其中ui32Port + GPIO_O_MIS指出了Reg GPIOMIS的地址，HWREG(ui32Port + GPIO_O_MIS)即为取值
							 写0，则返回包含已屏蔽中断的联合中断状态 return(HWREG(ui32Port + GPIO_O_RIS));
		
		 这个函数读到的是所有联合中断信号的综合信息（比如这里是PF的所有pin有没有发生中断），通过s & GPIO_PIN_4这样的方法取其中某位进行单独判断
			
	4、GPIOIntClear(GPIO_PORTF_BASE, s);
		 清除所有发生置位的中断标志
				
*/
//#include "inc/hw_ints.h"



#include "include.h"
#include "bsp_uart.h"


u8 Uart0_TX[200];
u8 Uart1_TX[200];
u8 Uart6_TX[200];
u8 Uart7_TX[200];

u8 Uart0_RX[200];
u8 Uart1_RX[200];
u8 Uart6_RX[200];
u8 Uart7_RX[200];

void USART0_IRQHandler(void);
void USART_Init(void)
{
	/**********************使能uart0 ********************************/
    //使能外设
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0);
    //使能复用
	GPIOPinConfigure( GPIO_PA0_U0RX);
	GPIOPinConfigure( GPIO_PA1_U0TX);
    //分配信号
	GPIOPinTypeUART( GPIO_PORTA_BASE,  GPIO_PIN_0);
	GPIOPinTypeUART( GPIO_PORTA_BASE,  GPIO_PIN_1);
    /*搭配UARTprintf使用*/
    //设置串口0的时钟为UART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //设置串口0波特率与波特时钟
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*与UARTCharPut，UARTCharPutNonBlocking等搭配使用*/
    //配置串口0波特率与校验位，停止位，字长等
	UARTConfigSetExpClk( UART0_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //失能FIFO
	UARTFIFODisable( UART0_BASE);
//    //接收发送的FIFO都为1/4，也就是16*1/4=4个字节
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //使能串口的接收与接收超时中断
	UARTIntEnable( UART0_BASE,  UART_INT_RX|UART_INT_RT);
    //注册中断函数
	UARTIntRegister( UART0_BASE, USART0_IRQHandler);
    //设置中断优先级
	IntPrioritySet( INT_UART0,  0);
    //开启中断
	IntEnable( INT_UART0);
	IntMasterEnable();
    //使能串口
    UARTEnable( UART0_BASE);
		
		
		
		
		
		/**********************使能uart1 ********************************/
		   //使能外设
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART1);
    //使能复用
	GPIOPinConfigure( GPIO_PB0_U1RX);
	GPIOPinConfigure( GPIO_PB1_U1TX);
    //分配信号
	GPIOPinTypeUART( GPIO_PORTB_BASE,  GPIO_PIN_0);
	GPIOPinTypeUART( GPIO_PORTB_BASE,  GPIO_PIN_1);
    /*搭配UARTprintf使用*/
    //设置串口0的时钟为UART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //设置串口0波特率与波特时钟
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*与UARTCharPut，UARTCharPutNonBlocking等搭配使用*/
    //配置串口0波特率与校验位，停止位，字长等
	UARTConfigSetExpClk( UART1_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //失能FIFO
	UARTFIFODisable( UART1_BASE);
//    //接收发送的FIFO都为1/4，也就是16*1/4=4个字节
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //使能串口的接收与接收超时中断
	UARTIntEnable( UART1_BASE,  UART_INT_RX|UART_INT_RT);
    //注册中断函数
	UARTIntRegister(UART1_BASE, USART1_IRQHandler);
    //设置中断优先级
	IntPrioritySet( INT_UART1,  0);
    //开启中断
	IntEnable( INT_UART1);
	IntMasterEnable();
    //使能串口
    UARTEnable( UART1_BASE);



		
		/**********************使能uart6 ********************************/
	   //使能外设
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART6);
    //使能复用
	GPIOPinConfigure( GPIO_PD4_U6RX);
	GPIOPinConfigure( GPIO_PD5_U6TX);
    //分配信号
	GPIOPinTypeUART( GPIO_PORTD_BASE,  GPIO_PIN_4);
	GPIOPinTypeUART( GPIO_PORTD_BASE,  GPIO_PIN_5);
    /*搭配UARTprintf使用*/
    //设置串口0的时钟为UART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //设置串口0波特率与波特时钟
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*与UARTCharPut，UARTCharPutNonBlocking等搭配使用*/
    //配置串口0波特率与校验位，停止位，字长等
	UARTConfigSetExpClk( UART6_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //失能FIFO
	UARTFIFODisable( UART6_BASE);
//    //接收发送的FIFO都为1/4，也就是16*1/4=4个字节
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //使能串口的接收与接收超时中断
	UARTIntEnable( UART6_BASE,  UART_INT_RX|UART_INT_RT);
    //注册中断函数
	UARTIntRegister( UART6_BASE, USART6_IRQHandler);
    //设置中断优先级
	IntPrioritySet( INT_UART6,  0);
    //开启中断
	IntEnable( INT_UART6);
	IntMasterEnable();
    //使能串口
    UARTEnable( UART6_BASE);	
		
		
		/**********************使能uart7 ********************************/
	   //使能外设
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART7);
    //使能复用
	GPIOPinConfigure( GPIO_PE0_U7RX);
	GPIOPinConfigure( GPIO_PE1_U7TX);
    //分配信号
	GPIOPinTypeUART( GPIO_PORTE_BASE,  GPIO_PIN_0);
	GPIOPinTypeUART( GPIO_PORTE_BASE,  GPIO_PIN_1);
    /*搭配UARTprintf使用*/
    //设置串口0的时钟为UART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //设置串口0波特率与波特时钟
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*与UARTCharPut，UARTCharPutNonBlocking等搭配使用*/
    //配置串口0波特率与校验位，停止位，字长等
	UARTConfigSetExpClk( UART7_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //失能FIFO
	UARTFIFODisable( UART7_BASE);
//    //接收发送的FIFO都为1/4，也就是16*1/4=4个字节
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //使能串口的接收与接收超时中断
	UARTIntEnable( UART7_BASE,  UART_INT_RX|UART_INT_RT);
    //注册中断函数
	UARTIntRegister( UART7_BASE, USART7_IRQHandler);
    //设置中断优先级
	IntPrioritySet( INT_UART7,  0);
    //开启中断
	IntEnable( INT_UART7);
	IntMasterEnable();
    //使能串口
    UARTEnable( UART7_BASE);
		
}


void USART0_IRQHandler(void)
{
{
    static uint16_t count = 0;
    //static uint8_t rx_buffer[100];
    
    // 读取中断状态并清除中断标志位
    uint32_t status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);
    
    // 判断UART0有没有字符未读取
    while (UARTCharsAvail(UART0_BASE))
    {
        // 如果有字符未读取就取出，使用UARTCharGetNonBlocking防止等待
        Uart0_RX[count] = UARTCharGetNonBlocking(UART0_BASE);
        
        
        // 判断是否接收完整一节字符串
        if (Uart0_RX[count] == '\n')
        {
            // 发送字符串
            Uart0_Transmit(Uart0_RX);
            
            // 重置计数器和缓冲区
           count = 0;
           // memset(Uart0_RX, 0, sizeof(Uart0_RX));
        }
        else
        {
            // 数量递增
            count++;
            
            // 判断缓冲区溢出
            if (count >= 100)
            {
                // 发送错误信息并重置计数器和缓冲区
                Uart0_Transmit((u8 *)"Error: Buffer Overflow\n");
                count = 0;
                memset(Uart0_RX, 0, sizeof(Uart0_RX));
            }
        }
    }
}

}




void USART1_IRQHandler(void)
{
{
    static uint16_t count = 0;
    
    // 读取中断状态并清除中断标志位
    uint32_t status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, status);
    
    // 判断UART0有没有字符未读取
    while (UARTCharsAvail(UART1_BASE))
    {
        // 如果有字符未读取就取出，使用UARTCharGetNonBlocking防止等待
        Uart1_RX[count] = UARTCharGetNonBlocking(UART1_BASE);
        
        
        // 判断是否接收完整一节字符串
        if (Uart1_RX[count] == '\n')
        {
            // 发送字符串
            Uart1_Transmit(Uart1_RX);
            
            // 重置计数器和缓冲区
           count = 0;
           // memset(Uart1_RX, 0, sizeof(Uart1_RX));
					printf("%s\r\n", Uart1_RX);
        }
        else
        {
            // 数量递增
            count++;
            
            // 判断缓冲区溢出
            if (count >= 100)
            {
                // 发送错误信息并重置计数器和缓冲区
                Uart1_Transmit((u8 *)"Error: Buffer Overflow\n");
                count = 0;
                memset(Uart1_RX, 0, sizeof(Uart1_RX));
            }
        }
    }
}

}




void USART6_IRQHandler(void)
{
{
    static uint16_t count = 0;
    // 读取中断状态并清除中断标志位
    uint32_t status = UARTIntStatus(UART6_BASE, true);
    UARTIntClear(UART6_BASE, status);
    
    // 判断UART0有没有字符未读取
    while (UARTCharsAvail(UART6_BASE))
    {
        // 如果有字符未读取就取出，使用UARTCharGetNonBlocking防止等待
        Uart6_RX[count] = UARTCharGetNonBlocking(UART6_BASE);
        
        
        // 判断是否接收完整一节字符串
        if (Uart6_RX[count] == '\n')
        {
            // 发送字符串
            Uart1_Transmit(Uart6_RX);
            
            // 重置计数器和缓冲区
           count = 0;
           // memset(Uart6_RX, 0, sizeof(Uart6_RX));
        }
        else
        {
            // 数量递增
            count++;
            
            // 判断缓冲区溢出
            if (count >= 100)
            {
                // 发送错误信息并重置计数器和缓冲区
                Uart1_Transmit((u8 *)"Error: Buffer Overflow\n");
                count = 0;
                memset(Uart6_RX, 0, sizeof(Uart6_RX));
            }
        }
    }
}

}

void USART7_IRQHandler(void)
{
{
    static uint16_t count = 0;
    
    // 读取中断状态并清除中断标志位
    uint32_t status = UARTIntStatus(UART7_BASE, true);
    UARTIntClear(UART7_BASE, status);
    
    // 判断UART0有没有字符未读取
    while (UARTCharsAvail(UART7_BASE))
    {
        // 如果有字符未读取就取出，使用UARTCharGetNonBlocking防止等待
        Uart7_RX[count] = UARTCharGetNonBlocking(UART7_BASE);
        
        
        // 判断是否接收完整一节字符串
        if (Uart7_RX[count] == '\n')
        {
            // 发送字符串
            Uart1_Transmit(Uart7_RX);
            
            // 重置计数器和缓冲区
            count = 0;
           // memset(Uart7_RX, 0, sizeof(Uart7_RX));
        }
        else
        {
            // 数量递增
            count++;
            
            // 判断缓冲区溢出
            if (count >= 100)
            {
                // 发送错误信息并重置计数器和缓冲区
                Uart1_Transmit((u8 *)"Error: Buffer Overflow\n");
                count = 0;
                memset(Uart7_RX, 0, sizeof(Uart7_RX));
            }
        }
    }
}

}

/**
 * @brief 将字符串通过UART0发送
 * 
 * @param string 要发送的字符串，以'\0'结尾
 */
void Uart0_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // 获取字符串的第一个字符
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART0_BASE, data); // 发送字符
        data = *string++; // 获取下一个字符
    }
}

/**
 * @brief 将字符串通过UART1发送
 * 
 * @param string 要发送的字符串，以'\0'结尾
 */
void Uart1_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // 获取字符串的第一个字符
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART1_BASE, data); // 发送字符
        data = *string++; // 获取下一个字符
    }
}
/**
 * @brief 将字符串通过UART6发送
 * 
 * @param string 要发送的字符串，以'\0'结尾
 */
void Uart6_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // 获取字符串的第一个字符
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART6_BASE, data); // 发送字符
        data = *string++; // 获取下一个字符
    }
}
/**
 * @brief 将字符串通过UART7发送
 * 
 * @param string 要发送的字符串，以'\0'结尾
 */
void Uart7_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // 获取字符串的第一个字符
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART7_BASE, data); // 发送字符
        data = *string++; // 获取下一个字符
    }
}

/************printf重定向相关**************/
int fputc(int ch, FILE *f)
{
	UARTCharPut(UART0_BASE, ch);
  return ch;
}

int fgetc(FILE *f)
{
  uint8_t ch = 0;
  ch = UARTCharGet(UART0_BASE);
  return ch;
}
