
#include "myiic.h"
//#include "delay.h"
#include "user.h"
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

//��ʼ��IIC
void IIC_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;	
  __HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	IIC_SDA_H;
	IIC_SCL_H;
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	Delay_us(4);
 	IIC_SDA_L;//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL_L;//ǯסI2C���ߣ�׼�����ͻ�������� 
	Delay_us(4);
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	//SDA_OUT();//sda�����
	IIC_SCL_L;
	IIC_SDA_L;//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	IIC_SCL_H; 
	Delay_us(4);
	IIC_SDA_H;//����I2C���߽����ź�
	Delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
uint8_t IIC_Wait_Ack(void)
{
	//uint8_t ucErrTime=0;  
	IIC_SCL_H;
	Delay_us(2);	 
	IIC_SCL_L; 
	Delay_us(2);
	return 0;  
} 
//����ACKӦ��
void IIC_Ack(void)
{
	Delay_us(2);
	IIC_SCL_H;
	Delay_us(2);
	IIC_SCL_L;
	
	Delay_us(2);
	
	IIC_SDA_H;
	Delay_us(2);
	IIC_SDA_L;
	Delay_us(2);
}
//������ACKӦ��		    
void IIC_NAck(void)
{
	IIC_SDA_H;
	Delay_us(2);
	IIC_SCL_H;
	Delay_us(2);
	IIC_SCL_L;
	Delay_us(2);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(uint8_t txd)
{                        
  uint8_t t;   
	for(t=0;t<8;t++)
	{
			if((txd&0x80)>>7)
				IIC_SDA_H;
			else
				IIC_SDA_L;
			txd<<=1; 	  
			Delay_us(2);   //��TEA5767��������ʱ���Ǳ����
			IIC_SCL_H;
			Delay_us(2); 
			IIC_SCL_L;	
			Delay_us(2);
	}	 
	IIC_SDA_L;
} 	    
//��1���ֽڣ�ack_Hʱ������ACK��ack_L������nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
  for(i=0;i<8;i++ )
	 {

		IIC_SCL_H;
		Delay_us(2);
		receive<<=1;
		if(READ_SDA)receive++;   
		Delay_us(2); 
		IIC_SCL_L; 
		Delay_us(2);
    }		
	 return receive;
}



























