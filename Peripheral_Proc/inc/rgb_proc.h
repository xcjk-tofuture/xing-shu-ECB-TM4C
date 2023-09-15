#ifndef __RGB_PROC_H

#define __RGB_PROC_H



#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "include.h"
#include "bsp_uart.h"





void RGB_Task_Proc(void const * argument);		//RGB进程主程序
void RGB_Show_Proc(u8 ucled);                 //RGB处理函数
#endif