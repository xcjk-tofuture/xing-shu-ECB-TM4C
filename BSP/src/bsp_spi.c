


#include "bsp_spi.h"

/* SSI���ú��� */
void SSI_Init(void)
{
    /* ʹ������ */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    /* ����SSI IO�ڵ�ģʽ */
    GPIOPinTypeSSI(GPIO_PORTA_BASE, GPIO_PIN_2 | GPIO_PIN_4 | GPIO_PIN_5);

    /* IO������ΪSSI���� */
    GPIOPinConfigure(GPIO_PA2_SSI0CLK);//SCK
    GPIOPinConfigure(GPIO_PA4_SSI0RX); //MISO
    GPIOPinConfigure(GPIO_PA5_SSI0TX); //MOSI

    /* SSI���� ģʽ3(Polarity = 1 Phase = 1) ���豸ģʽ ����1MHz ���ݳ���8λ*/
    SSIConfigSetExpClk(SSI0_BASE, SysCtlClockGet(), SSI_FRF_MOTO_MODE_3, SSI_MODE_MASTER, 1000000, 8);
//	Polarity	Phase	Mode
//	0						0	            SSI_FRF_MOTO_MODE_0
//	0						1	            SSI_FRF_MOTO_MODE_1
//	1						0							SSI_FRF_MOTO_MODE_2
//	1						1							SSI_FRF_MOTO_MODE_3
    /* ʹ��SSI2 */
    SSIEnable(SSI0_BASE);

}

/* SPI��д���� */
uint8_t ucSPI_RW(uint8_t uc_SendData)
{
    uint32_t ui_TempData;
    uint8_t uc_ReceiveData;

    /* ��SSI FIFOд������ */
    SSIDataPutNonBlocking(SSI0_BASE, uc_SendData);
    /* �ȴ�SSI��æ */
    while(SSIBusy(SSI0_BASE));
    /* ��FIFO��ȡ���� */
    SSIDataGetNonBlocking(SSI0_BASE, &ui_TempData);

    /* ��ȡ���ݵĵͰ�λ */
    uc_ReceiveData = ui_TempData & 0xff;

    return uc_ReceiveData;
}

void vSPI_Transmit(uint8_t *ucp_Data, uint16_t us_Size)
{
    uint16_t i = 0;
    /* ����д������ */
    for(i = 0; i < us_Size; i++)
    {
        ucSPI_RW(ucp_Data[i]);
    }
}

void vSPI_Receive(uint8_t *ucp_Data, uint16_t us_Size)
{
    uint16_t i = 0;
    /* ������ȡ���� */
    for(i = 0; i < us_Size; i++)
    {
        ucp_Data[i] = ucSPI_RW(0xFF);
    }
}
