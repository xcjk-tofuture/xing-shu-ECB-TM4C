#ifndef __MAIN_H
#define __MAIN_H









 /* exact-width unsigned integer types */



typedef signed int  s32;
typedef signed short int s16;
typedef signed char  s8;
typedef volatile unsigned int  vu32;
typedef volatile unsigned short int  vu16;
typedef volatile unsigned char  vu8;
typedef unsigned int   u32;
typedef unsigned short int u16;
typedef unsigned char  u8;
typedef const u32 uc32;  /*!< Read Only */
typedef const u16 uc16;  /*!< Read Only */
typedef const u8 uc8;   /*!< Read Only */


void Sys_Tick_Init();
void My_Delay_us(u32 n);
void My_Delay_ms(u32 n);
void All_Init();



//PIN-MAP
#define RGB_R_Pin GPIO_PIN_1
#define RGB_R_GPIO_Port GPIO_PORTF_BASE
#define RGB_G_Pin GPIO_PIN_2
#define RGB_G_GPIO_Port GPIO_PORTF_BASE
#define RGB_B_Pin GPIO_PIN_3
#define RGB_B_GPIO_Port GPIO_PORTF_BASE


#define LCD_DC_GPIO_Port GPIO_PORTB_BASE
#define LCD_DC_Pin GPIO_PIN_3
#define LCD_RES_GPIO_Port GPIO_PORTB_BASE
#define LCD_RES_Pin GPIO_PIN_2
#define LCD_CS_GPIO_Port GPIO_PORTA_BASE
#define LCD_CS_Pin GPIO_PIN_3




typedef struct
{
  float x;
  float y;
  float z;
}Vector3f;

#define vector3f Vector3f
#endif
