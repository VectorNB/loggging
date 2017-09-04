#ifndef __MYIIC_H
#define __MYIIC_H
#include "stm32f4xx_hal.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//IIC ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2010/6/10 
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
////////////////////////////////////////////////////////////////////////////////// 	  

//VOID ABC(void)
//{
//	GPIOB->MODER  &=~ 0X0000C000;
//  GPIOB->PUPDR  &=~ 0X00000000;	
//	GPIOB->PUPDR  |=  0X00004000;
//	
//	GPIOB->MODER  &=~ 0X0000C000;
//	GPIOB->MODER  |=  0X00004000;
//	GPIOB->PUPDR  &=~ 0X00000000;	
//	GPIOB->PUPDR  |=  0X00004000;
//	GPIOB->OTYPER &=~ 0X00000080;
//	GPIOB->OSPEEDR&=~ 0X0000C000;
//	GPIOB->OSPEEDR|=  0X00008000;
//	
//	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET);
//	HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7)
//}

   	   		   
//IO��������  B7
#define SDA_IN()  {	GPIOB->MODER  &=~ 0X0000C000;\
										GPIOB->PUPDR  &=~ 0X00000000;}
										//GPIOB->PUPDR  |=  0X00004000;}

#define SDA_OUT() {	GPIOB->MODER  &=~ 0X0000C000;\
										GPIOB->MODER  |=  0X00004000;}
										//GPIOB->PUPDR  &=~ 0X00000000;\
										//GPIOB->PUPDR  |=  0X00004000;\
										//GPIOB->OTYPER &=~ 0X00000080;\
										//GPIOB->OSPEEDR&=~ 0X0000C000;\
										//GPIOB->OSPEEDR|=  0X00008000;}


//IO��������	 
#define IIC_SCL_H  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_SET)
#define IIC_SCL_L  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_6,GPIO_PIN_RESET)
										
#define IIC_SDA_H  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_SET)  
#define IIC_SDA_L  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_7,GPIO_PIN_RESET)
										
#define READ_SDA   HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_7) 

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�
void IIC_Write_One_Byte(uint8_t daddr,uint8_t addr,uint8_t data);
uint8_t IIC_Read_One_Byte(uint8_t daddr,uint8_t addr);	  
#endif
















