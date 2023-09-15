#ifndef __BSP_TIM_H
#define __BSP_TIM_H







#include "include.h"


void TIM0_Init(u16  fre); //定时器0级联定时器初始化
void TIM0_Period_Handler();  //定时器0  32位级联定时器中断处理函数


void WTIM1_Init(u16  fre); //定时器1级联定时器初始化
void WTIM1_Period_Handler();  //定时器1  32位拆分定时器中断处理函数

//void PWM1_Init(); //PWM1初始化


void Motor_Init();   //电机pwm信号初始化
void Buzzer_Init();  //无源蜂鸣器初始化
void Servo_Init();   //舵机初始化

void TIM_Capture_Init(); //输入捕获

void PWM_IN_IRQHandler();//输入捕获处理函数

void Motor_Encoder_Init();  //编码器初始化

void TimerQEIinit();
void QQ_Handler(void);

#endif