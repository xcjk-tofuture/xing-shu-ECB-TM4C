
#include "lcd.h"
#include "lcd_proc.h"
#include "mpu6050.h"
extern unsigned char startup[40968];
extern u32 uwTick;
extern float BatValue;
extern state_t CarPos;
u8 LcdDisp[40];

u8 LcdPage = 1;

void LCD_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN LCD_Task_Proc */
  /* Infinite loop */
	LCD_Init();//LCD³õÊ¼»¯
//	LCD_Image(0, 0, 128,160, startup);
	vTaskDelay(200);
	LCD_Clear(BLACK);
  for(;;)
  {
	LCD_Chinese16ForFile(10,0,0, LIGHTBLUE, BLACK); //±êÌâ  ÐÇ
	LCD_Chinese16ForFile(10 + 18,0,1, LIGHTBLUE, BLACK); //±êÌâ  Êà
	LCD_ShowString(10 + 36,0,"V2.0 RTOS",YELLOW,BLACK,16,0);
	sprintf((u8 *)LcdDisp,"BAT: %.2fV", BatValue);
	LCD_ShowString(0,160 - 32, LcdDisp,WHITE,BLACK,16,0);	
	sprintf((u8 *)LcdDisp,"TIME:%d", uwTick/1000);
	LCD_ShowString(0,160 - 16, LcdDisp,WHITE,BLACK,16,0);
	sprintf((u8 *)LcdDisp,"PAGE:%d", LcdPage);
	LCD_ShowString(80,160 - 16, LcdDisp,WHITE,BLACK,16,0);
	
	sprintf(LcdDisp,"pitch:%0.2f        ",CarPos.attitude.pitch);  //¸©Ñö½Ç
	LCD_ShowString(0,16 + 16 + 3 * 12, LcdDisp,WHITE,BLACK,12,0);


	sprintf(LcdDisp," roll:%0.2f        ",CarPos.attitude.roll);  //·­¹ö½Ç
	LCD_ShowString(0,16 + 16 + 4 * 12, LcdDisp,WHITE,BLACK,12,0);	  

	sprintf(LcdDisp,"  yaw:%0.2f       ", CarPos.attitude.yaw);    //Æ«º½½Ç
	LCD_ShowString(0,16 + 16 + 5 * 12, LcdDisp,WHITE,BLACK,12,0);		
	
		
	vTaskDelay(100);
  }
  /* USER CODE END LCD_Task_Proc */
}