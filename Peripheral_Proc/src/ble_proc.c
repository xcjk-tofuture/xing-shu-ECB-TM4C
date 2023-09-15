#include "ble_proc.h"

extern u8 Uart1_RX[200];
extern u8 Uart1_TX[200];



u8 DataSend [100];


//发送用Uart1_Transmit
void Ble_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN Ble_Task_Proc */
  /* Infinite loop */
  for(;;)
  {
     vTaskDelay(1);
  }
  /* USER CODE END Ble_Task_Proc */
}




//匿名上位机demo
//数据拆分

#define BYTE0(dwTemp)     (*(char *)(&dwTemp))
#define BYTE1(dwTemp)     (*((char *)(&dwTemp) +1))
#define BYTE2(dwTemp)     (*((char *)(&dwTemp) +2))
#define BYTE3(dwTemp)     (*((char *)(&dwTemp) +3))

void ANODT_SendF1(s16 a, s16 b, s16 c)      //向匿名上位机发送数据
{
 
  u8 cnt = 0;
	DataSend[cnt++] = 0xAA;
	DataSend[cnt++] = 0xFF;
	DataSend[cnt++] = 0xF1;
	DataSend[cnt++] = 6;
	
  DataSend[cnt++] = BYTE0(a);
	DataSend[cnt++] = BYTE1(a);
  
	DataSend[cnt++] = BYTE0(b);
  DataSend[cnt++] = BYTE1(b);
  
	DataSend[cnt++] = BYTE0(c);
  DataSend[cnt++] = BYTE1(c);
	
	
	u8 sc = 0;
	u8 ac = 0;
	
	for (u8 i = 0; i < DataSend[3] + 4; i++)
	{
	     sc += DataSend[i];
		   ac += sc;
	}
	
	DataSend[cnt++] = sc;
	DataSend[cnt++] = ac;

	Uart1_Transmit((u8 *)DataSend);
	
}