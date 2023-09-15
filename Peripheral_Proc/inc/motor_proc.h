#ifndef __MOTOR_PROC_H
#define __MOTOR_PROC_H

#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "include.h"


typedef struct motor
{
	u8 Num;       //���
	s8 direction; //����
	s32 Trig;     //������
	float Speed;  //��ǰ�ٶ�
	s16 SetSpeedRange; //�趨���ٶȵ�λ   ���Ŵ�������
	s8 SetDirection; //   ���Ŵ�������
	
}MOTOR;

void Motor_Encoder_Init();
void Motor_Get_Value(MOTOR  *motor);
void Motor_Init();
void Motor_Speed_Set(MOTOR *motor, s16 speed);
void Motor_Speed_Set_Extra(MOTOR *motor, s16 speed);
float FABS(float a);




#endif