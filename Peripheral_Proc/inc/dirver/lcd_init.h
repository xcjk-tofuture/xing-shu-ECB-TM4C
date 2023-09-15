#ifndef __LCD_INIT_H
#define __LCD_INIT_H

//#include "sys.h"

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "include.h"
#define USE_HORIZONTAL 1  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏


#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif


#define TFT_RES_Pin GPIO_PIN_0
#define TFT_DC_Pin GPIO_PIN_1
#define TFT_BL_Pin GPIO_PIN_2
#define SPI1_TFT_Pin GPIO_PIN_5
//-----------------LCD端口定义---------------- 

//#define LCD_SCLK_Clr() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_RESET)//SCL=SCLK
//#define LCD_SCLK_Set() HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5, GPIO_PIN_SET)

//#define LCD_MOSI_Clr() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_RESET)//SDA=MOSI
//#define LCD_MOSI_Set() HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5, GPIO_PIN_SET)

#define LCD_RES_Clr()  GPIOPinWrite(LCD_RES_GPIO_Port, LCD_RES_Pin, 0)//GPIO_ResetBits(GPIOE,GPIO_Pin_0)//RES
#define LCD_RES_Set()  GPIOPinWrite(LCD_RES_GPIO_Port, LCD_RES_Pin, LCD_RES_Pin)

#define LCD_DC_Clr()   GPIOPinWrite(LCD_DC_GPIO_Port, LCD_DC_Pin, 0)//GPIO_ResetBits(GPIOE,GPIO_Pin_1)//DC
#define LCD_DC_Set()   GPIOPinWrite(LCD_DC_GPIO_Port, LCD_DC_Pin, LCD_DC_Pin)//GPIO_SetBits(GPIOE,GPIO_Pin_1)
 		     
#define LCD_CS_Clr()   GPIOPinWrite(LCD_CS_GPIO_Port, LCD_CS_Pin, 0)//GPIO_ResetBits(GPIOE,GPIO_Pin_2)//CS
#define LCD_CS_Set()   GPIOPinWrite(LCD_CS_GPIO_Port, LCD_CS_Pin, LCD_CS_Pin)//GPIO_SetBits(GPIOE,GPIO_Pin_2)

//#define LCD_BLK_Clr()  GPIOPinWrite(GPIO_PORTB_BASE, TFT_BL_Pin, 0)//PIO_ResetBits(GPIOE,GPIO_Pin_3)//BLK
//#define LCD_BLK_Set()  GPIOPinWrite(GPIO_PORTB_BASE, TFT_BL_Pin, TFT_BL_Pin)//GPIO_SetBits(GPIOE,GPIO_Pin_3)



void LCD_WriteData(uint8_t *buff, size_t buff_size); //写入一串数据
void LCD_GPIO_Init(void);//初始化GPIO
void LCD_Writ_Bus(u8 dat);//模拟SPI时序
void LCD_WR_DATA8(u8 dat);//写入一个字节
void LCD_WR_DATA(u16 dat);//写入两个字节
void LCD_WR_REG(u8 dat);//写入一个指令
void LCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);//设置坐标函数
void LCD_Init(void);//LCD初始化
#endif




