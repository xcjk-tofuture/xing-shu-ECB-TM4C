/*
	1�������������̣�
		SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);							//Enable UART0 module
		SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);							//for UART
		GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0 | GPIO_PIN_1);	//PA0&PA1 forUART0
		UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);					//configure the baud clock source theprecision internal oscillator(UART_CLOCK_PIOSC)																											
		UARTStdioConfig(0,9600, 16000000);												//�������Ҳ����uartstdio.c�ﶨ��ģ����Դ��ļ��鿴Դ����
		
	2��HWREG��ʾ����Ӳ���Ĵ���
		
	3��s = GPIOIntStatus(GPIO_PORTF_BASE, true);
		 ��ȡ�ж�״̬��TM4C��������ĳЩ�жϱ����Σ����ε��ж��źŲ��ᱻ�͵��жϿ�����������λ����GPIOIM�Ĵ���
		 �ڶ�������д1���򷵻ز����������жϵ������ж�״̬ return(HWREG(ui32Port + GPIO_O_MIS)); ����ui32Port + GPIO_O_MISָ����Reg GPIOMIS�ĵ�ַ��HWREG(ui32Port + GPIO_O_MIS)��Ϊȡֵ
							 д0���򷵻ذ����������жϵ������ж�״̬ return(HWREG(ui32Port + GPIO_O_RIS));
		
		 ������������������������ж��źŵ��ۺ���Ϣ������������PF������pin��û�з����жϣ���ͨ��s & GPIO_PIN_4�����ķ���ȡ����ĳλ���е����ж�
			
	4��GPIOIntClear(GPIO_PORTF_BASE, s);
		 ������з�����λ���жϱ�־
				
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
	/**********************ʹ��uart0 ********************************/
    //ʹ������
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOA);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART0);
    //ʹ�ܸ���
	GPIOPinConfigure( GPIO_PA0_U0RX);
	GPIOPinConfigure( GPIO_PA1_U0TX);
    //�����ź�
	GPIOPinTypeUART( GPIO_PORTA_BASE,  GPIO_PIN_0);
	GPIOPinTypeUART( GPIO_PORTA_BASE,  GPIO_PIN_1);
    /*����UARTprintfʹ��*/
    //���ô���0��ʱ��ΪUART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //���ô���0�������벨��ʱ��
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*��UARTCharPut��UARTCharPutNonBlocking�ȴ���ʹ��*/
    //���ô���0��������У��λ��ֹͣλ���ֳ���
	UARTConfigSetExpClk( UART0_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //ʧ��FIFO
	UARTFIFODisable( UART0_BASE);
//    //���շ��͵�FIFO��Ϊ1/4��Ҳ����16*1/4=4���ֽ�
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //ʹ�ܴ��ڵĽ�������ճ�ʱ�ж�
	UARTIntEnable( UART0_BASE,  UART_INT_RX|UART_INT_RT);
    //ע���жϺ���
	UARTIntRegister( UART0_BASE, USART0_IRQHandler);
    //�����ж����ȼ�
	IntPrioritySet( INT_UART0,  0);
    //�����ж�
	IntEnable( INT_UART0);
	IntMasterEnable();
    //ʹ�ܴ���
    UARTEnable( UART0_BASE);
		
		
		
		
		
		/**********************ʹ��uart1 ********************************/
		   //ʹ������
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOB);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART1);
    //ʹ�ܸ���
	GPIOPinConfigure( GPIO_PB0_U1RX);
	GPIOPinConfigure( GPIO_PB1_U1TX);
    //�����ź�
	GPIOPinTypeUART( GPIO_PORTB_BASE,  GPIO_PIN_0);
	GPIOPinTypeUART( GPIO_PORTB_BASE,  GPIO_PIN_1);
    /*����UARTprintfʹ��*/
    //���ô���0��ʱ��ΪUART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //���ô���0�������벨��ʱ��
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*��UARTCharPut��UARTCharPutNonBlocking�ȴ���ʹ��*/
    //���ô���0��������У��λ��ֹͣλ���ֳ���
	UARTConfigSetExpClk( UART1_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //ʧ��FIFO
	UARTFIFODisable( UART1_BASE);
//    //���շ��͵�FIFO��Ϊ1/4��Ҳ����16*1/4=4���ֽ�
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //ʹ�ܴ��ڵĽ�������ճ�ʱ�ж�
	UARTIntEnable( UART1_BASE,  UART_INT_RX|UART_INT_RT);
    //ע���жϺ���
	UARTIntRegister(UART1_BASE, USART1_IRQHandler);
    //�����ж����ȼ�
	IntPrioritySet( INT_UART1,  0);
    //�����ж�
	IntEnable( INT_UART1);
	IntMasterEnable();
    //ʹ�ܴ���
    UARTEnable( UART1_BASE);



		
		/**********************ʹ��uart6 ********************************/
	   //ʹ������
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART6);
    //ʹ�ܸ���
	GPIOPinConfigure( GPIO_PD4_U6RX);
	GPIOPinConfigure( GPIO_PD5_U6TX);
    //�����ź�
	GPIOPinTypeUART( GPIO_PORTD_BASE,  GPIO_PIN_4);
	GPIOPinTypeUART( GPIO_PORTD_BASE,  GPIO_PIN_5);
    /*����UARTprintfʹ��*/
    //���ô���0��ʱ��ΪUART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //���ô���0�������벨��ʱ��
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*��UARTCharPut��UARTCharPutNonBlocking�ȴ���ʹ��*/
    //���ô���0��������У��λ��ֹͣλ���ֳ���
	UARTConfigSetExpClk( UART6_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //ʧ��FIFO
	UARTFIFODisable( UART6_BASE);
//    //���շ��͵�FIFO��Ϊ1/4��Ҳ����16*1/4=4���ֽ�
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //ʹ�ܴ��ڵĽ�������ճ�ʱ�ж�
	UARTIntEnable( UART6_BASE,  UART_INT_RX|UART_INT_RT);
    //ע���жϺ���
	UARTIntRegister( UART6_BASE, USART6_IRQHandler);
    //�����ж����ȼ�
	IntPrioritySet( INT_UART6,  0);
    //�����ж�
	IntEnable( INT_UART6);
	IntMasterEnable();
    //ʹ�ܴ���
    UARTEnable( UART6_BASE);	
		
		
		/**********************ʹ��uart7 ********************************/
	   //ʹ������
  SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOE);
	SysCtlPeripheralEnable( SYSCTL_PERIPH_UART7);
    //ʹ�ܸ���
	GPIOPinConfigure( GPIO_PE0_U7RX);
	GPIOPinConfigure( GPIO_PE1_U7TX);
    //�����ź�
	GPIOPinTypeUART( GPIO_PORTE_BASE,  GPIO_PIN_0);
	GPIOPinTypeUART( GPIO_PORTE_BASE,  GPIO_PIN_1);
    /*����UARTprintfʹ��*/
    //���ô���0��ʱ��ΪUART_CLOCK_PIOSC
//	UARTClockSourceSet( UART0_BASE,  UART_CLOCK_PIOSC);
    //���ô���0�������벨��ʱ��
//	UARTStdioConfig( 0,  115200,
//                             16000000);
    /*��UARTCharPut��UARTCharPutNonBlocking�ȴ���ʹ��*/
    //���ô���0��������У��λ��ֹͣλ���ֳ���
	UARTConfigSetExpClk( UART7_BASE,  SysCtlClockGet(),
                                 115200,  UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE);
    //ʧ��FIFO
	UARTFIFODisable( UART7_BASE);
//    //���շ��͵�FIFO��Ϊ1/4��Ҳ����16*1/4=4���ֽ�
//	UARTFIFOLevelSet( UART0_BASE,  UART_FIFO_TX2_8,
//                              UART_FIFO_RX2_8);
    //ʹ�ܴ��ڵĽ�������ճ�ʱ�ж�
	UARTIntEnable( UART7_BASE,  UART_INT_RX|UART_INT_RT);
    //ע���жϺ���
	UARTIntRegister( UART7_BASE, USART7_IRQHandler);
    //�����ж����ȼ�
	IntPrioritySet( INT_UART7,  0);
    //�����ж�
	IntEnable( INT_UART7);
	IntMasterEnable();
    //ʹ�ܴ���
    UARTEnable( UART7_BASE);
		
}


void USART0_IRQHandler(void)
{
{
    static uint16_t count = 0;
    //static uint8_t rx_buffer[100];
    
    // ��ȡ�ж�״̬������жϱ�־λ
    uint32_t status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);
    
    // �ж�UART0��û���ַ�δ��ȡ
    while (UARTCharsAvail(UART0_BASE))
    {
        // ������ַ�δ��ȡ��ȡ����ʹ��UARTCharGetNonBlocking��ֹ�ȴ�
        Uart0_RX[count] = UARTCharGetNonBlocking(UART0_BASE);
        
        
        // �ж��Ƿ��������һ���ַ���
        if (Uart0_RX[count] == '\n')
        {
            // �����ַ���
            Uart0_Transmit(Uart0_RX);
            
            // ���ü������ͻ�����
           count = 0;
           // memset(Uart0_RX, 0, sizeof(Uart0_RX));
        }
        else
        {
            // ��������
            count++;
            
            // �жϻ��������
            if (count >= 100)
            {
                // ���ʹ�����Ϣ�����ü������ͻ�����
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
    
    // ��ȡ�ж�״̬������жϱ�־λ
    uint32_t status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, status);
    
    // �ж�UART0��û���ַ�δ��ȡ
    while (UARTCharsAvail(UART1_BASE))
    {
        // ������ַ�δ��ȡ��ȡ����ʹ��UARTCharGetNonBlocking��ֹ�ȴ�
        Uart1_RX[count] = UARTCharGetNonBlocking(UART1_BASE);
        
        
        // �ж��Ƿ��������һ���ַ���
        if (Uart1_RX[count] == '\n')
        {
            // �����ַ���
            Uart1_Transmit(Uart1_RX);
            
            // ���ü������ͻ�����
           count = 0;
           // memset(Uart1_RX, 0, sizeof(Uart1_RX));
					printf("%s\r\n", Uart1_RX);
        }
        else
        {
            // ��������
            count++;
            
            // �жϻ��������
            if (count >= 100)
            {
                // ���ʹ�����Ϣ�����ü������ͻ�����
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
    // ��ȡ�ж�״̬������жϱ�־λ
    uint32_t status = UARTIntStatus(UART6_BASE, true);
    UARTIntClear(UART6_BASE, status);
    
    // �ж�UART0��û���ַ�δ��ȡ
    while (UARTCharsAvail(UART6_BASE))
    {
        // ������ַ�δ��ȡ��ȡ����ʹ��UARTCharGetNonBlocking��ֹ�ȴ�
        Uart6_RX[count] = UARTCharGetNonBlocking(UART6_BASE);
        
        
        // �ж��Ƿ��������һ���ַ���
        if (Uart6_RX[count] == '\n')
        {
            // �����ַ���
            Uart1_Transmit(Uart6_RX);
            
            // ���ü������ͻ�����
           count = 0;
           // memset(Uart6_RX, 0, sizeof(Uart6_RX));
        }
        else
        {
            // ��������
            count++;
            
            // �жϻ��������
            if (count >= 100)
            {
                // ���ʹ�����Ϣ�����ü������ͻ�����
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
    
    // ��ȡ�ж�״̬������жϱ�־λ
    uint32_t status = UARTIntStatus(UART7_BASE, true);
    UARTIntClear(UART7_BASE, status);
    
    // �ж�UART0��û���ַ�δ��ȡ
    while (UARTCharsAvail(UART7_BASE))
    {
        // ������ַ�δ��ȡ��ȡ����ʹ��UARTCharGetNonBlocking��ֹ�ȴ�
        Uart7_RX[count] = UARTCharGetNonBlocking(UART7_BASE);
        
        
        // �ж��Ƿ��������һ���ַ���
        if (Uart7_RX[count] == '\n')
        {
            // �����ַ���
            Uart1_Transmit(Uart7_RX);
            
            // ���ü������ͻ�����
            count = 0;
           // memset(Uart7_RX, 0, sizeof(Uart7_RX));
        }
        else
        {
            // ��������
            count++;
            
            // �жϻ��������
            if (count >= 100)
            {
                // ���ʹ�����Ϣ�����ü������ͻ�����
                Uart1_Transmit((u8 *)"Error: Buffer Overflow\n");
                count = 0;
                memset(Uart7_RX, 0, sizeof(Uart7_RX));
            }
        }
    }
}

}

/**
 * @brief ���ַ���ͨ��UART0����
 * 
 * @param string Ҫ���͵��ַ�������'\0'��β
 */
void Uart0_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // ��ȡ�ַ����ĵ�һ���ַ�
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART0_BASE, data); // �����ַ�
        data = *string++; // ��ȡ��һ���ַ�
    }
}

/**
 * @brief ���ַ���ͨ��UART1����
 * 
 * @param string Ҫ���͵��ַ�������'\0'��β
 */
void Uart1_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // ��ȡ�ַ����ĵ�һ���ַ�
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART1_BASE, data); // �����ַ�
        data = *string++; // ��ȡ��һ���ַ�
    }
}
/**
 * @brief ���ַ���ͨ��UART6����
 * 
 * @param string Ҫ���͵��ַ�������'\0'��β
 */
void Uart6_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // ��ȡ�ַ����ĵ�һ���ַ�
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART6_BASE, data); // �����ַ�
        data = *string++; // ��ȡ��һ���ַ�
    }
}
/**
 * @brief ���ַ���ͨ��UART7����
 * 
 * @param string Ҫ���͵��ַ�������'\0'��β
 */
void Uart7_Transmit(u8 *string)
{
    u8 data;
    data = *string++; // ��ȡ�ַ����ĵ�һ���ַ�
    while(data != '\0')
    {
        UARTCharPutNonBlocking(UART7_BASE, data); // �����ַ�
        data = *string++; // ��ȡ��һ���ַ�
    }
}

/************printf�ض������**************/
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
