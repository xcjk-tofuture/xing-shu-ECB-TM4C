

#include "bsp_gpio.h"
#include "lcd.h"


void GPIO_Init()
{
  /************����PF1 PF2 PF3 ���RGB ��io�����ʾ����***************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);																				//ʹ��PFʱ��
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);						//��������ΪGPIO������ײ���GPIOPadConfigSet��GPIODirModeSet  //para1: ���ߵ�ַ para2: io�ڵ�ַ      
	//SysCtlPeripheralReady(); ���ü��ʱ������ while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
  //GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4,GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU); //io�����ģʽ����  //para1: ���ߵ�ַ para2: io�ڵ�ַ para3: ���������С  para4:���ģʽ
	/*GPIO_PIN_TYPE_STD_WPU������
		GPIO_PIN_TYPE_STD_WPD������
		GPIO_PIN_TYPE_STDΪ��������
		GPIO_PIN_TYPE_ODΪ��©
		GPIO_PIN_TYPE_ANALOGģ������
		GPIO_PIN_TYPE_WAKE_HIGH�ߵ�ƽ����
		GPIO_PIN_TYPE_WAKE_LOW�͵�ƽ����	*/
	/**********************************************/
	
	
	

	/************����PF4 PF0 SW1 SW2��������(�ⲿ�ж�ʾ��)  ע��PF0������***************/
	HWREG(GPIO_PORTF_BASE+GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTF_BASE+GPIO_O_CR) |= GPIO_PIN_0;  //����PF0
	
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);										//ʹ��PFʱ��
	GPIOPinTypeGPIOInput(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4);  //��������ģʽ
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);//��������(����˵�����Ǹ��Ѿ��ڲ��Դ����������� ���ǲ�֪��Ϊʲô���ټ��������һ�ΰ����ͻ��쳣)
	GPIOIntTypeSet(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4, GPIO_FALLING_EDGE); //�����ж�ģʽ �½��ش���
	
	GPIOIntRegister(GPIO_PORTF_BASE, KEY_EXIT_Handler);  //ע���ж� ���жϴ�����
	
	IntPrioritySet(INT_GPIOF|GPIO_PIN_4, 0); // �����ж����ȼ���TM4C123G���ж����ȼ���8����0���
	//�����ǿ�ʼ�����ж�������
	GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_0|GPIO_PIN_4); //IO�жϿ�ʹ��
	IntEnable(INT_GPIOF);  //Port�ж�ʹ�� ������һ������ ������ܺ� #include "inc/hw_ints.h" ͷ�ļ����� ���þͱ���
	IntMasterEnable();			//�������ж�
	/**********************************************/
	
}



void LCD_IO_Init()
{
/******************LCD IO�ڳ�ʼ�� ***************************/
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);																				//ʹ��PBʱ��
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);																				//ʹ��PBʱ��
	GPIOPinTypeGPIOOutput(LCD_DC_GPIO_Port, LCD_DC_Pin);	
	GPIOPinTypeGPIOOutput(LCD_RES_GPIO_Port, LCD_RES_Pin);
	GPIOPinTypeGPIOOutput(LCD_CS_GPIO_Port, LCD_CS_Pin);

	GPIOPinWrite(LCD_CS_GPIO_Port, LCD_CS_Pin, LCD_CS_Pin);  //����lcd csƬѡ��
}










