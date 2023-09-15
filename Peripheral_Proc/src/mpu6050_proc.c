#include "mpu6050_proc.h"
#include "mpu6050.h"
#include "WP_math.h"

state_t CarPos;		/*��̬*/
vector3f Gyro, Acc;
Vector3f_t CarAcc;
Vector3f_t CarGryo;
float Temp;

void MPU6050_Task_Proc(void const * argument)
{
  /* USER CODE BEGIN MPU6050_Task_Proc */


	static u16 count = 0;
	
	MPU6050_Init();	 //��װ��֮ǰ��Ҫ����ʼ��  �ⶫ��û�����ź�ֱ��������˵ ��������̵����ƾͳ����� ��Ҳ����������̶���
  for(;;)
  {
	MPU6050_Read_Data(&Gyro, &Acc, &Temp);

		CarAcc.x = (float)Acc.x/(0xffff/16.0);
		CarAcc.y = (float)Acc.y/(0xffff/16.0);
		CarAcc.z = (float)Acc.z/(0xffff/16.0);
		
		CarGryo.x = (float)Gyro.x/(0xffff/2000.0);
		CarGryo.y = (float)Gyro.y/(0xffff/2000.0);
		CarGryo.z = (float)Gyro.z/(0xffff/2000.0);
		imuUpdate(CarAcc, CarGryo, &CarPos, 0.01); //��̬����
	
		if (count % 10 == 0 )
		{
		printf("3��������:%d\t%d\t%d\r\n",(int16_t)(Gyro.x),(int16_t)(Gyro.y),(int16_t)(Gyro.z));
		printf("3����ٶ�:%d\t%d\t%d\r\n",(int16_t)(Acc.x),(int16_t)(Acc.y),(int16_t)(Acc.z));
		printf("IMU�¶ȡ�:%f\r\n",Temp);
		printf("Pitch:%.2f, Roll :%.2f Yaw: %.2f\r\n", CarPos.attitude.pitch, CarPos.attitude.roll,CarPos.attitude.yaw);
		}
			vTaskDelay(10);
		count++;
  }
  /* USER CODE END MPU6050_Task_Proc */
}


#define DEG2RAD		0.017453293f	/* ��ת���� ��/180 */
#define RAD2DEG		57.29578f		/* ����ת�� 180/�� */


float Kp = 0.4f;		/*��������*/
float Ki = 0.001f;		/*��������*/
float exInt = 0.0f;
float eyInt = 0.0f;
float ezInt = 0.0f;		/*��������ۼ�*/

static float q0 = 1.0f;	/*��Ԫ��*/
static float q1 = 0.0f;
static float q2 = 0.0f;
static float q3 = 0.0f;	

static float baseZacc = 1.0;		/*��̬Z����ٶ�*/
static bool isCalibrated = false;


static float invSqrt(float x);	/*���ٿ�ƽ����*/

void imuUpdate(Vector3f_t acc, Vector3f_t gyro, state_t *state , float dt)	/*�����ں� �����˲�*/
{
	float normalise;
	float ex, ey, ez;
	float q0s, q1s, q2s, q3s;	/*��Ԫ����ƽ��*/
	static float R11,R21;		/*����(1,1),(2,1)��*/
	static float vecxZ, vecyZ, veczZ;	/*��������ϵ�µ�Z��������*/
	float halfT =0.5f * dt;
	Vector3f_t tempacc =acc;

	gyro.x = gyro.x * DEG2RAD;	/* ��ת���� */
	gyro.y = gyro.y * DEG2RAD;
	gyro.z = gyro.z * DEG2RAD;

	/* ĳһ��������ٶȲ�Ϊ0 */
	if((acc.x != 0.0f) || (acc.y != 0.0f) || (acc.z != 0.0f))
	{
		/*��λ�����ټƲ���ֵ*/
		normalise = invSqrt(acc.x * acc.x + acc.y * acc.y + acc.z * acc.z);
		acc.x *= normalise;
		acc.y *= normalise;
		acc.z *= normalise;

		/*���ټƶ�ȡ�ķ������������ټƷ���Ĳ�ֵ����������˼���*/
		ex = (acc.y * veczZ - acc.z * vecyZ);
		ey = (acc.z * vecxZ - acc.x * veczZ);
		ez = (acc.x * vecyZ - acc.y * vecxZ);
		
		/*����ۼƣ�����ֳ������*/
		exInt += Ki * ex * dt ;  
		eyInt += Ki * ey * dt ;
		ezInt += Ki * ez * dt ;
		
		/*�ò���������PI����������ƫ�����������ݶ����е�ƫ����*/
		gyro.x += Kp * ex + exInt;
		gyro.y += Kp * ey + eyInt;
		gyro.z += Kp * ez + ezInt;
	}
	/* һ�׽����㷨����Ԫ���˶�ѧ���̵���ɢ����ʽ�ͻ��� */
	q0 += (-q1 * gyro.x - q2 * gyro.y - q3 * gyro.z) * halfT;
	q1 += (q0 * gyro.x + q2 * gyro.z - q3 * gyro.y) * halfT;
	q2 += (q0 * gyro.y - q1 * gyro.z + q3 * gyro.x) * halfT;
	q3 += (q0 * gyro.z + q1 * gyro.y - q2 * gyro.x) * halfT;
	
	/*��λ����Ԫ��*/
	normalise = invSqrt(q0 * q0 + q1 * q1 + q2 * q2 + q3 * q3);
	q0 *= normalise;
	q1 *= normalise;
	q2 *= normalise;
	q3 *= normalise;
	/*��Ԫ����ƽ��*/
	q0s = q0 * q0;
	q1s = q1 * q1;
	q2s = q2 * q2;
	q3s = q3 * q3;
	
	R11 = q0s + q1s - q2s - q3s;	/*����(1,1)��*/
	R21 = 2 * (q1 * q2 + q0 * q3);	/*����(2,1)��*/

	/*��������ϵ�µ�Z��������*/
	vecxZ = 2 * (q1 * q3 - q0 * q2);/*����(3,1)��*/
	vecyZ = 2 * (q0 * q1 + q2 * q3);/*����(3,2)��*/
	veczZ = q0s - q1s - q2s + q3s;	/*����(3,3)��*/
	
	if (vecxZ>1) vecxZ=1;
	if (vecxZ<-1) vecxZ=-1;
	
	/*����roll pitch yaw ŷ����*/
	state->attitude.pitch = -asinf(vecxZ) * RAD2DEG; 
	state->attitude.roll = atan2f(vecyZ, veczZ) * RAD2DEG;
	state->attitude.yaw = atan2f(R21, R11) * RAD2DEG;
	
	if (!isCalibrated)	/*У׼*/
	{
		baseZacc = tempacc.x* vecxZ + tempacc.y * vecyZ + tempacc.z * veczZ;
		isCalibrated = true;
	}
	state->acc.z= tempacc.x* vecxZ + tempacc.y * vecyZ + tempacc.z * veczZ - baseZacc;	/*Z����ٶ�(ȥ���������ٶ�)*/
}

// Fast inverse square-root
// See: http://en.wikipedia.org/wiki/Fast_inverse_square_root
float invSqrt(float x)	/*���ٿ�ƽ����*/
{
	float halfx = 0.5f * x;
	float y = x;
	long i = *(long*)&y;
	i = 0x5f3759df - (i>>1);
	y = *(float*)&i;
	y = y * (1.5f - (halfx * y * y));
	return y;
}
