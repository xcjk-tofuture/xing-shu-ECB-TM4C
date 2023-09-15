#include "bsp_iic.h"






/***********************************************************
@函数名：Init_I2C
@入口参数：无
@出口参数：无
功能描述：TM4C硬件I2C初始化
@作者：无名小哥
@日期：2019年01月27日
*************************************************************/
void I2C_Init(void) {
			SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C1); // 使能 I2C1 外设
			SysCtlDelay(2); // 在使能外设后插入一些周期，以允许时钟完全启动
			SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA); // 使能 GPIOA 外设
			SysCtlDelay(2); // 在使能外设后插入一些周期，以允许时钟完全启动

			// 使用替代功能
			GPIOPinConfigure(GPIO_PA6_I2C1SCL); // 配置引脚PA6为 I2C1 的 SCL 引脚
			GPIOPinConfigure(GPIO_PA7_I2C1SDA); // 配置引脚PA7为 I2C1 的 SDA 引脚

			GPIOPinTypeI2CSCL(GPIO_PORTA_BASE, GPIO_PIN_6); // 使用具有 I2C SCL 外设的引脚
			GPIOPinTypeI2C(GPIO_PORTA_BASE, GPIO_PIN_7); // 使用具有 I2C 外设的引脚

			I2CMasterInitExpClk(I2C1_BASE, 400*100000,true); // 启用 I2C，并将频率设置为 400 kHz
			//I2CMasterInitExpClk(I2C1_BASE, SysCtlClockGet(),true);
			SysCtlDelay(2); // 在使能 I2C 后插入一些周期，以允许时钟完全启动
}

/***********************************************************
@函数名：i2cWriteData
@入口参数：uint8_t addr, uint8_t regAddr, uint8_t *data, uint8_t length
@出口参数：无
功能描述：I2C写数据
@作者：无名小哥
@日期：2019年01月27日
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
@函数名：i2cRead
@入口参数：uint8_t addr, uint8_t regAddr
@出口参数：无
功能描述：I2C读数据
@作者：无名小哥
@日期：2019年01月27日
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
@函数名：i2cWrite
@入口参数：uint8_t addr, uint8_t regAddr, uint8_t data
@出口参数：无
功能描述：I2C写数据
@作者：无名小哥
@日期：2019年01月27日
*************************************************************/
void i2cWrite(uint8_t addr, uint8_t regAddr, uint8_t data) {
  i2cWriteData(addr, regAddr, &data, 1);
}


/***********************************************************
@函数名：i2cReadData
@入口参数：uint8_t addr, uint8_t regAddr, uint8_t *data,
uint8_t length
@出口参数：无
功能描述：I2C读数据
@作者：无名小哥
@日期：2019年01月27日
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





