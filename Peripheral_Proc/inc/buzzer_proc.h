#ifndef __BUZZER_PROC_H
#define __BUZZER_PROC_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "include.h"


void Buzzer_Task_Proc(void const * argument);
void driveBuzzer(uint16_t frequency, uint32_t duration);
void playMusic(void);
void Music_Play_Lowbattery();  //���������������
void Music_Play_StartUp();  //��������





#endif