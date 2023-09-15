

#include "FreeRTOS.h"
#include "task.h"
#include "include.h"










TaskHandle_t RGBTaskHandle;
TaskHandle_t KeyTaskHandle;
TaskHandle_t K210TaskHandle;
TaskHandle_t OpenMVTaskHandle;
TaskHandle_t ServoTaskHandle;
TaskHandle_t MPU6050TaskHandle;
TaskHandle_t PCTaskHandle;
TaskHandle_t LCDTaskHandle;
TaskHandle_t BuzzerTaskHandle;
TaskHandle_t MotorTaskHandle;
TaskHandle_t EncoderTaskHandle;
TaskHandle_t BleTaskHandle;

void RGB_Task_Proc();
void Key_Task_Proc();
void K210_Task_Proc();
void OpenMV_Task_Proc();
void Servo_Task_Proc();
void MPU6050_Task_Proc();
void PC_Task_Proc();
void LCD_Task_Proc();
void Buzzer_Task_Proc();
void Motor_Task_Proc();
void Encoder_Task_Proc();
void Ble_Task_Proc();




void FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
	
  printf("rtos loading...........\r\n");
	printf("\\   |   /\r\n");
	printf("-  xcjk  -\r\n");
	printf("/    |   \\\r\n");
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of RGBTask */
	
	/* Create RGBTask */
	
	
	
	
xTaskCreate(RGB_Task_Proc, "RGBTask", 128, NULL, 0, &RGBTaskHandle);

/* Create KeyTask */
xTaskCreate(Key_Task_Proc, "KeyTask", 128, NULL, 0, &KeyTaskHandle);

/* Create K210Task */
xTaskCreate(K210_Task_Proc, "K210Task", 128, NULL, 0, &K210TaskHandle);

/* Create OpenMVTask */
xTaskCreate(OpenMV_Task_Proc, "OpenMVTask", 128, NULL, 0, &OpenMVTaskHandle);

/* Create ServoTask */
xTaskCreate(Servo_Task_Proc, "ServoTask", 128, NULL, 0, &ServoTaskHandle);

/* Create MPU6050Task */
xTaskCreate(MPU6050_Task_Proc, "MPU6050Task", 256, NULL, 0, &MPU6050TaskHandle);

/* Create PCTask */
xTaskCreate(PC_Task_Proc, "PCTask", 128, NULL, 0, &PCTaskHandle);

/* Create LCDTask */
xTaskCreate(LCD_Task_Proc, "LCDTask", 256, NULL, 0, &LCDTaskHandle);

/* Create BuzzerTask */
xTaskCreate(Buzzer_Task_Proc, "BuzzerTask", 128, NULL, 0, &BuzzerTaskHandle);

/* Create MotorTask */
xTaskCreate(Motor_Task_Proc, "MotorTask", 128, NULL, 0, &MotorTaskHandle);

/* Create EncoderTask */
xTaskCreate(Encoder_Task_Proc, "EncoderTask", 128, NULL, 0, &EncoderTaskHandle);

/* Create BleTask */
xTaskCreate(Ble_Task_Proc, "BleTask", 128, NULL, 0, &BleTaskHandle);
 


  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
	
		if(RGBTaskHandle != NULL)
	{ printf("rgb_task_creat_sucess!\r\n"); }

	if(BuzzerTaskHandle != NULL)
	{ printf("buzzer_task_creat_sucess!\r\n"); }


	if(LCDTaskHandle != NULL)
	{ printf("lcd_task_creat_sucess!\r\n"); }

	if(KeyTaskHandle != NULL)
	{ printf("key_task_creat_sucess!\r\n"); }

	if(K210TaskHandle != NULL)
	{ printf("k210_task_creat_sucess!\r\n"); }

	if(OpenMVTaskHandle != NULL)
	{ printf("openmv_task_creat_sucess!\r\n"); }

	if(PCTaskHandle != NULL)
	{ printf("pc_task_creat_sucess!\r\n"); }


	if(ServoTaskHandle != NULL)
	{ printf("servo_task_creat_sucess!\r\n"); }

	if(MotorTaskHandle != NULL)
	{ printf("motor_task_creat_sucess!\r\n"); }    //指示打印是否正常
	
	if(EncoderTaskHandle != NULL)
	{ printf("Encoder_task_creat_sucess!\r\n"); }    //指示打印是否正常
	
	if(MPU6050TaskHandle != NULL)
	{ printf("MPU6050_task_creat_sucess!\r\n"); }    //指示打印是否正常
	
	printf("         .....              *\r\n");
	printf("      ...........        . .\r\n");
	printf("    ...............   . *\r\n");
	printf("    ...............\r\n");
	printf("     ............. *********\r\n");
	printf("      ..........***************\r\n");
	printf("         ....*********************\r\n");
	printf("       .  ***************************\r\n");
	printf("     .   ************星枢*************\r\n");
	printf("    *    **************v2.0***********\r\n");
	printf("   .     *****************************\r\n");
	printf(" *   .   *****************************\r\n");
	printf("          ***************************\r\n");
	printf("             *********************\r\n");
	printf("                ***************\r\n");
	printf("                   *********\r\n\r\n");
    printf("  /\\_/\\  \r\n");
    printf(" ( o.o ) \r\n");
    printf("  > ^ <  \r\n");
		printf(" 星橙祝您使用一路顺风！(ノ￣▽￣)   \r\n");
  /* USER CODE END RTOS_THREADS */

}




