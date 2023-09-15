


#include "bsp_spi.h"

/* SSI配置函数 */
void SSI_Init(void)
{
    /* 使能外设 */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /* 设置SSI IO口的模式 */
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5);

    /* IO口配置为SSI功能 */
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);//SCK
    GPIOPinConfigure(GPIO_PA4_SSI0RX); //MISO
    GPIOPinConfigure(GPIO_PA5_SSI0TX); //MOSI

    /* SSI配置 模式3(Polarity = 1 Phase = 1) 主设备模式 速率1MHz 数据长度8位*/
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 1000000, 8);
//	Polarity	Phase	Mode
//	0						0	            SSI_FRF_MOTO_MODE_0
//	0						1	            SSI_FRF_MOTO_MODE_1
//	1						0							SSI_FRF_MOTO_MODE_2
//	1						1							SSI_FRF_MOTO_MODE_3
    /* 使能SSI2 */
    SSIEnable(SSI0_BASE);

}

/* SPI读写函数 */
uint8_t ucSPI_RW(uint8_t uc_SendData)
{
    uint32_t ui_TempData;
    uint8_t uc_ReceiveData;

    /* 向SSI FIFO写入数据 */
    SSIDataPutNonBlocking(SSI0_BASE, uc_SendData);
    /* 等待SSI不忙 */
    while(SSIBusy(SSI0_BASE));
    /* 从FIFO读取数据 */
    SSIDataGetNonBlocking(SSI0_BASE, &ui_TempData);

    /* 截取数据的低八位 */
    uc_ReceiveData = ui_TempData & 0xff;

    return uc_ReceiveData;
}

void vSPI_Transmit(uint8_t *ucp_Data, uint16_t us_Size)
{
    uint16_t i = 0;
    /* 连续写入数据 */
    for(i = 0; i < us_Size; i++)
    {
        ucSPI_RW(ucp_Data[i]);
    }
}

void vSPI_Receive(uint8_t *ucp_Data, uint16_t us_Size)
{
    uint16_t i = 0;
    /* 连续读取数据 */
    for(i = 0; i < us_Size; i++)
    {
        ucp_Data[i] = ucSPI_RW(0xFF);
    }
}
