#ifndef __MPU6050_H
#define __MPU6050_H
   												  	  
#include "include.h"
#include "iic_divier.h" 


#define IMU_MPU6050_ID   0x68
#define IMU_ICM20689_ID  0x98
//****************************************
// MPU6050
//****************************************
// acceleration due to gravity in m/s/s
#define GRAVITY_MSS 9.80665f
// Gyroscope scale (uncertain where the 0.01745 value comes from)
#define GYRO_SCALE_2000  (0.0174532f / 16.4f)
#define GYRO_SCALE_1000  (0.0174532f / 32.8f)
#define GYRO_SCALE_500  (0.0174532f / 65.5f)
#define SCALE_250  (0.0174532f / 131f)
// Accelerometer scale adjustment
#define ACCEL_SCALE_16G   (GRAVITY_MSS / 2048.0f)
#define ACCEL_SCALE_8G    (GRAVITY_MSS / 4096.0f)
#define ACCEL_SCALE_4G    (GRAVITY_MSS / 8192.0f)
#define ACCEL_SCALE_2G    (GRAVITY_MSS / 16384.0f)


#define	SMPLRT_DIV		0x19
#define	MPU_CONFIG		0x1A
#define	GYRO_CONFIG		0x1B
#define	ACCEL_CONFIG  0x1C
#define ACCEL_CONFIG2 0x1D
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B
#define	WHO_AM_I		  0x75
#define USER_CTRL		  0x6A
#define INT_PIN_CFG		0x37
#define MPU_ADRESS		0x68


typedef struct {
    float x;
    float y;
    float z;
} Vector3f_t;

typedef struct  
{
	u32 timestamp;	/*ʱ���*/

	float roll;
	float pitch;
	float yaw;
} attitude_t;

struct  vec3_s 
{
	u32 timestamp;	/*ʱ���*/

	float x;
	float y;
	float z;
};

typedef struct vec3_s point_t;
typedef struct vec3_s velocity_t;
typedef struct vec3_s acc_t;


typedef struct
{
	float pressure;
	float temperature;
	float asl;
} baro_t;

typedef struct
{
	Vector3f_t acc;
	Vector3f_t gyro;
	Vector3f_t mag;
	baro_t baro;
	point_t position;
} sensorData_t;

typedef struct
{
	attitude_t attitude;
	point_t position;
	velocity_t velocity;
	acc_t acc;
} state_t;

void IMU_Calibration(void);
void MPU6050_Init(void);
void MPU6050_Read_Data(vector3f *gyro,vector3f *accel,float *temperature);
extern Vector3f gyro_offset;
float invSqrt(float x);
void imuUpdate(Vector3f_t acc, Vector3f_t gyro, state_t *state , float dt);
#endif