#include "bsp_adc.h"


//TM4������ADC���ֱ�ΪADC0��ADC1��ÿ��ADCλ��Ϊ12λ������12��ͨ���������ܹ����Բ�24·���ݡ�


//1. ʹ�� RCGCADC �Ĵ������� ADC ʱ��
//2. ͨ�� RCGCGPIO�Ĵ���������Ӧ GPIOģ���ʱ�ӡ�
//3. �� ADC ����ܽŵ� AFSEL λ��λ��
//4. ͨ���� GPIO ����ʹ�� (GPIODEN) �Ĵ�������Ӧ DEN λ���㣬�� AINx �ܽ�����Ϊģ�������
//5. ͨ��Ϊ GPIOAMSEL �Ĵ�������Ӧλд 1�����ô���ģ������ŵ�ģ������·��
//6. ����Ӧ�������������Ӧͨ�� ADCSSPRI�Ĵ����������ò������з����������ȼ���0-��ߣ�3-��ͣ���

//void ADC_Init()
//{

//	

//    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);   // ʹ��ADC0

//    // ����GPIO����E3��E2��ΪADC��������
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
//    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1);

//    // ����ADCʱ�ӺͲ������� ��д����1/64 ��Ƶ
//    //ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 1);
//    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

//    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 );
//    ADCSequenceStepConfigure(ADC0_BASE, 0, 1, ADC_CTL_CH1  );
//		ADCSequenceStepConfigure(ADC0_BASE, 0, 2, ADC_CTL_CH2 | ADC_CTL_IE | ADC_CTL_END);

//	

//		  ADCSequenceEnable(ADC0_BASE, 0);

//}


void BAT_ADC_Init()
{

	  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);   // ʹ��ADC0

    // ����GPIO����PE3��ΪADC��������
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    // ����ADCʱ�ӺͲ������� ��д����1/64 ��Ƶ
    //ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 1);
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END );
		ADCSequenceEnable(ADC0_BASE, 0);


}
