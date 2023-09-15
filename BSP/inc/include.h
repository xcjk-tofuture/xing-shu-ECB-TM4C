#ifndef INCLUDE_H_
#define INCLUDE_H_
//基础部分
#include "main.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "driverlib/pin_map.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "inc/hw_sysctl.h"


//有关80Mhz的部分
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"

//io操作
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"

//有关中断
#include "inc/hw_ints.h"
#include "driverlib/interrupt.h"

//有关串口
#include "driverlib/uart.h"
#include "utils/uartstdio.h"//需要导入这个的c和h文件

//有关定时器和pwm波
#include "driverlib/pwm.h"
#include "driverlib/timer.h"
#include "inc/hw_timer.h"

//有关浮点运算
#include "driverlib/fpu.h"

//有关i2c和ssi
#include "driverlib/i2c.h"
#include "inc/hw_i2c.h"
#include "inc/hw_ssi.h"
#include "driverlib/ssi.h"

//有关qei和adc
#include "driverlib/qei.h"
#include "driverlib/adc.h"

//BSP
#include "main.h"
#include "bsp_gpio.h"
#include "bsp_uart.h"
#include "bsp_tim.h"
#include "bsp_adc.h"
#include "bsp_iic.h"
#include "bsp_spi.h"


//MATH
#include "math.h"

//RTOS
#include "FreeRTOS.h"
#include "task.h"

//Peripheral

//PROC
#include "rgb_proc.h"
#include "key_proc.h"
#include "pc_proc.h"
#include "ble_proc.h"
#include "buzzer_proc.h"
#include "k210_proc.h"
#include "lcd_proc.h"
#include "motor_proc.h"
#include "mpu6050_proc.h"
#include "openmv_proc.h"
#include "servo_proc.h"

void FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

#endif /* INCLUDE_H_ */
