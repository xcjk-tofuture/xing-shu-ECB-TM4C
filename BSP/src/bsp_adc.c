#include "bsp_adc.h"


//TM4有两个ADC，分别为ADC0和ADC1。每个ADC位数为12位，下设12个通道，所以总共可以采24路数据。


//1. 使用 RCGCADC 寄存器启用 ADC 时钟
//2. 通过 RCGCGPIO寄存器启用相应 GPIO模块的时钟。
//3. 将 ADC 输入管脚的 AFSEL 位置位。
//4. 通过将 GPIO 数字使能 (GPIODEN) 寄存器中相应 DEN 位清零，将 AINx 管脚配置为模拟输出。
//5. 通过为 GPIOAMSEL 寄存器的相应位写 1，禁用待用模拟输入脚的模拟隔离电路。
//6. 假如应用有相关需求，则应通过 ADCSSPRI寄存器重新配置采样序列发生器的优先级（0-最高，3-最低）。

//void ADC_Init()
//{

//	

//    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);   // 使能ADC0

//    // 设置GPIO引脚E3和E2作为ADC输入引脚
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
//    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1);

//    // 配置ADC时钟和采样序列 不写就是1/64 主频
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

	  SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);   // 使能ADC0

    // 设置GPIO引脚PE3作为ADC输入引脚
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3);

    // 配置ADC时钟和采样序列 不写就是1/64 主频
    //ADCClockConfigSet(ADC0_BASE, ADC_CLOCK_SRC_PLL | ADC_CLOCK_RATE_FULL, 1);
    ADCSequenceConfigure(ADC0_BASE, 0, ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 0, 0, ADC_CTL_CH0 | ADC_CTL_IE | ADC_CTL_END );
		ADCSequenceEnable(ADC0_BASE, 0);


}
