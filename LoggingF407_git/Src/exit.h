#ifndef __EXIT_H
#define __EXIT_H 

#include "stm32f4xx_hal.h"


#define DATAIN     GPIOF->IDR  //((GPIO_TypeDef2*)GPIOF)->IDR   		//��������	
#define DATAOUT    GPIOF->ODR //((GPIO_TypeDef2*)GPIOF)->ODR   		//�������

void Read_Data_From_FPGA(uint16_t *data_buff,uint16_t num);
void Set_Baud(uint16_t zcz);
void Send_Data_To_FPGA_DoubleCmd(uint16_t hand,uint16_t cmd);
void Send_Data_To_FPGA_OneCmd(uint16_t cmd);
#endif
