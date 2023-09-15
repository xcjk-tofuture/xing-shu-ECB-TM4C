
#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include "include.h"

void SSI_Init(void);
/* SPI¶ÁÐ´º¯Êý */
uint8_t ucSPI_RW(uint8_t uc_SendData);
void vSPI_Transmit(uint8_t *ucp_Data, uint16_t us_Size);
void vSPI_Receive(uint8_t *ucp_Data, uint16_t us_Size);

#endif