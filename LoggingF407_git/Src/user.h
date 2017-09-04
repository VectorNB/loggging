#ifndef __USER_H
#define __USER_H
#include "stm32f4xx_hal.h"
#include "usbd_customhid.h"
#define M_ETHLENGTH 200
#define M_FPGALENGTH 2500
#define M_USBTXBUFF 200
#define  M_USBRXUFF 200

#define TIMEWAYFLAG 0X37
#define PAULSEWAYFLAY 0X37
#define MONIQIWAYFLAY 0XF7

#define DATACHECKLength 256

#define USARTRXBUFFNUM 20

#define MONIQICUNT 10

#define AT24C0XXDEVICEADRR 0XA0

typedef struct {
uint16_t head;
uint16_t value;
}TEST_Y;

typedef struct {
uint16_t head;
uint16_t value;
}TEST_Z;

typedef struct{
uint32_t hand;
uint32_t type;
uint32_t state;
uint32_t ID;
uint32_t end;
}MODELDES;

typedef struct {
uint32_t hand;
uint32_t depth;
uint32_t time;
uint32_t strain;//����
uint32_t end;
}SYSTEMSTATE;

typedef struct {
uint32_t hand;
uint32_t depth;
uint32_t timespan;
uint32_t reserve1;
uint32_t reserve2;
uint32_t reserve3;
uint32_t reserve4;
uint32_t reserve5;
uint32_t reserve6;
uint32_t reserve7;
uint32_t reserve8;
uint32_t reserve9;
uint32_t reserve10;
uint32_t reserve11;	
}LOGGINGSTATEHand;

typedef struct {
uint32_t hand;
uint16_t num;
uint16_t type;
uint16_t errornum;
uint16_t allnum;
uint16_t Y_Z;
}SENDYAMA_ZHONGZI_RUT;

typedef struct {
uint32_t num;
uint32_t end;
}LOGGINGSTATEEND;

typedef struct {
uint32_t hand;
uint32_t data;
uint32_t end;
}INSTRUMENTSTATE;



typedef struct {
uint16_t DATA1;
uint16_t DATA2;	
}COMMENDSTACK;
  
typedef union{
uint32_t val;
uint8_t data[4];
}PARAMETER;

typedef struct {
__IO uint32_t WriteFlag;
__IO PARAMETER IP;
__IO PARAMETER SUBNET;
__IO PARAMETER NETWORK;
__IO PARAMETER DNS;
__IO PARAMETER Severs;
__IO uint32_t port; 
}IPINFOR;

typedef struct{
uint8_t m_ucUSBRXFlag;
uint8_t m_ucETHRXFLAG;
uint16_t m_usETHRXLength;
	
uint8_t m_ucTIM3Count;         //EHT ��������
volatile uint8_t m_ucCommendFlag;       //�ڲ��ø�����ʽ���в�����ʱ����Щ��־λ������λ
volatile uint16_t m_usSampleWay;
	
uint16_t m_usOneMeterPaus;
uint8_t m_ucRExitflag;
uint8_t m_ucChangeAB;
	
uint16_t m_usOneFramNUM;
uint8_t  m_ucWaitTime;
uint8_t  m_ucWaitTime1;
	
uint32_t m_usSampleSpan;
	
volatile uint32_t m_uiBMQVal;//��������ֵ
volatile uint32_t m_uiBMQValLast;//��������ֵ
	
uint16_t m_usMoNiQiSpeed;
uint8_t m_ucTransDataON;       //Ĭ���� 1  ��������յ� 0x3003 0x0002 ���������Ҫ�ص�Ϊ 0 ͬʱ ����ڴ��յ� 0x3004 0002 �ٴ��л��� 1
uint8_t m_ucSlefTestON;        //�յ� 3004 0001 �� ��λ
	
uint8_t m_ucMoNiQiDirec;       //ģ�����ķ���
uint16_t m_usSendCmdVal;       //���׷��� 1000 ����1200
volatile uint8_t m_ucETHCommuFlag;      //ʹ��ETH ����ͨ��

volatile uint8_t m_ucUSBCommuFlag;      //ʹ��USB ����ͨ��
volatile uint8_t m_ucALLDataReturnFlag; //�ȴ�FPGA TO 407 ���е����ݷ��ػ���
uint8_t m_ucWaitReturnEnd;     //���Ϊ1 ��ʾ���ڷ��� �� �������
uint8_t m_ucYamaFlag;

uint8_t m_ucZhongziFlag;
uint16_t m_usConfigIPFlag;
uint8_t  m_ucUSARTRXFlag;

uint8_t m_ucFLUSH_YJP;
uint8_t m_ucBaud;
volatile uint8_t m_ucOneScnt;
uint8_t  m_ucReadMoRenFlag;

uint8_t m_ucWriteMoRenFlag;
uint16_t m_usOneFrameNum;

uint32_t m_uiBMQSTAVal;

int m_iTimer4UpdateCnt;

uint32_t m_uiTime; // ʱ��

int m_uiMoniqicnt;
int m_uiMoniqicntlast;

uint16_t m_usTestRxbuff[DATACHECKLength];

float m_fYamaError;
float m_fZhongziError;

TEST_Y m_tTest_Y[DATACHECKLength];
TEST_Z m_tTest_Z[DATACHECKLength];
IPINFOR m_tIPinformation;


COMMENDSTACK m_tCommendStack;
MODELDES m_tModelDes;
SYSTEMSTATE m_tSystemState;
LOGGINGSTATEHand m_tLoggingStaHand;
LOGGINGSTATEEND m_tLoggingStaEnd;
SENDYAMA_ZHONGZI_RUT m_tYA_ZhongZi;
INSTRUMENTSTATE  m_tInstrument;

uint8_t m_ucETHRXbuff[M_ETHLENGTH];
uint8_t m_ucUSBTXBuff[M_USBTXBUFF];
uint8_t m_ucUSARTRXBuff[USARTRXBUFFNUM];
uint8_t m_ucUSBRXBuff[M_USBTXBUFF];
uint16_t m_usFPGARXbuff[M_FPGALENGTH];
}USERPRV;

void Delay_us(uint32_t time);
void Delay_ms(uint32_t time);
uint8_t Z_Y_TestFunc(USERPRV * _userprv);
void Zhongzi_Yama_Data_Init(TEST_Y * test_y,TEST_Z *  test_z);
void A_Moudel_Function(USERPRV * _userprv);
void Analyse_SetIP_cmd(USERPRV * _userprv,uint8_t * databuff);
void Set_IP(USERPRV * _userprv,uint8_t * databuff);
void Data_Init(USERPRV * _userprv);
void A_B_Moudel_Function(USERPRV * _userprv);
void Judge_A_B_Moudel(USERPRV * _userprv);
void Welcome_Page(USERPRV * _userprv);
void Write_At24c02(USERPRV * _userprv);
void Read_At24c02(USERPRV * _userprv);
void Send_Moudel(USERPRV * _userprv);
void Write_MoRen_Val(USERPRV * _userprv);//д Ĭ�� ���� ��flash ��ȥ
#endif


