#include "bsp_iic.h"






/***********************************************************
@��������Init_I2C
@��ڲ�������
@���ڲ�������
����������TM4CӲ��I2C��ʼ��
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void I2C_Init(void) {
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1); // ʹ�� I2C1 ����
			SysCtlDelay(2); // ��ʹ����������һЩ���ڣ�������ʱ����ȫ����
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // ʹ�� GPIOA ����
			SysCtlDelay(2); // ��ʹ����������һЩ���ڣ�������ʱ����ȫ����

			// ʹ���������
			GPIOPinConfigure(GPIO_PA6_I2C1SCL); // ��������PA6Ϊ I2C1 �� SCL ����
			GPIOPinConfigure(GPIO_PA7_I2C1SDA); // ��������PA7Ϊ I2C1 �� SDA ����

			GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6); // ʹ�þ��� I2C SCL ���������
			GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7); // ʹ�þ��� I2C ���������

			I2CMasterInitExpClk(I2C1_BASE, 400*100000,true); // ���� I2C������Ƶ������Ϊ 400 kHz
			//I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(),true);
			SysCtlDelay(2); // ��ʹ�� I2C �����һЩ���ڣ�������ʱ����ȫ����
}

/***********************************************************
@��������i2cWriteData
@��ڲ�����uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length
@���ڲ�������
����������I2Cд����
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void i2cWriteData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length) {
  u16 i;
	I2CMasterSlaveAddrSet(I2C1_BASE, addr, false); // Set to write mode
  
  I2CMasterDataPut(I2C1_BASE, regAddr); // Place address into data register
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_START); // Send start condition
  while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
  
  for (i = 0; i < length - 1; i++) 
	{
    I2CMasterDataPut(I2C1_BASE, data[i]); // Place data into data register
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_CONT); // Send continues condition
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
  }
  
  I2CMasterDataPut(I2C1_BASE, data[length - 1]); // Place data into data register
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_SEND_FINISH); // Send finish condition
  while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
}

/***********************************************************
@��������i2cRead
@��ڲ�����uint8_t addr, uint8_t regAddr
@���ڲ�������
����������I2C������
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
uint8_t i2cRead(uint8_t addr, uint8_t regAddr) {
  I2CMasterSlaveAddrSet(I2C1_BASE, addr, false); // Set to write mode
  
  I2CMasterDataPut(I2C1_BASE, regAddr); // Place address into data register
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
  while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
  
  I2CMasterSlaveAddrSet(I2C1_BASE, addr, true); // Set to read mode
  
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE); // Tell master to read data
  while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
  return I2CMasterDataGet(I2C1_BASE); // Read data
}

/***********************************************************
@��������i2cWrite
@��ڲ�����uint8_t addr, uint8_t regAddr, uint8_t data
@���ڲ�������
����������I2Cд����
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void i2cWrite(uint8_t addr, uint8_t regAddr, uint8_t data) {
  i2cWriteData(addr, regAddr, &data, 1);
}


/***********************************************************
@��������i2cReadData
@��ڲ�����uint8_t addr, uint8_t regAddr, uint8_t *data,
uint8_t length
@���ڲ�������
����������I2C������
@���ߣ�����С��
@���ڣ�2019��01��27��
*************************************************************/
void i2cReadData(uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length) {
  u16 i;
	I2CMasterSlaveAddrSet(I2C1_BASE, addr, false); // Set to write mode
  I2CMasterDataPut(I2C1_BASE, regAddr); // Place address into data register
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_SINGLE_SEND); // Send data
  while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done 
  I2CMasterSlaveAddrSet(I2C1_BASE, addr, true); // Set to read mode
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_START); // Send start condition
  while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
  data[0] = I2CMasterDataGet(I2C1_BASE); // Place data into data register 
	for ( i = 1; i < length - 1; i++) 
	{
    I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_CONT); // Send continues condition
    while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
    data[i] = I2CMasterDataGet(I2C1_BASE); // Place data into data register
  }
  I2CMasterControl(I2C1_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH); // Send finish condition
  while (I2CMasterBusy(I2C1_BASE)); // Wait until transfer is done
  data[length - 1] = I2CMasterDataGet(I2C1_BASE); // Place data into data register
}


void Single_WriteI2C(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)
{
  i2cWrite(SlaveAddress,REG_Address,REG_data);
}	

unsigned char Single_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)
{
  return i2cRead(SlaveAddress,REG_Address);
}

short int Double_ReadI2C(unsigned char SlaveAddress,unsigned char REG_Address)
{
  unsigned char msb , lsb ;
  msb = i2cRead(SlaveAddress,REG_Address);
  lsb = i2cRead(SlaveAddress,REG_Address+1);
  return ( ((short int)msb) << 8 | lsb) ;
}





