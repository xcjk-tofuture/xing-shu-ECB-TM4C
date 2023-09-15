#ifndef __BSP_TIM_H
#define __BSP_TIM_H







#include "include.h"


void TIM0_Init(u16  fre); //��ʱ��0������ʱ����ʼ��
void TIM0_Period_Handler();  //��ʱ��0  32λ������ʱ���жϴ�����


void WTIM1_Init(u16  fre); //��ʱ��1������ʱ����ʼ��
void WTIM1_Period_Handler();  //��ʱ��1  32λ��ֶ�ʱ���жϴ�����

//void PWM1_Init(); //PWM1��ʼ��


void Motor_Init();   //���pwm�źų�ʼ��
void Buzzer_Init();  //��Դ��������ʼ��
void Servo_Init();   //�����ʼ��

void TIM_Capture_Init(); //���벶��

void PWM_IN_IRQHandler();//���벶������

void Motor_Encoder_Init();  //��������ʼ��

void TimerQEIinit();
void QQ_Handler(void);

#endif