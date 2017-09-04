#include "user.h"
#include "exit.h"
#include "server.h"
#include "lcd.h"
#include  "flash.h"
#include "picture.h"
#include "24cxx.h"
#include <stdlib.h>


USERPRV m_userprv;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim4;
extern USBD_HandleTypeDef hUsbDeviceFS;
extern I2C_HandleTypeDef hi2c1;
extern IWDG_HandleTypeDef hiwdg;

extern const unsigned char asc16[];
extern const unsigned char sz32[];
extern const struct typFNT_GB162 hz16[];
extern const struct typFNT_GB242 hz24[];
/**
  * @brief us ÑÓÊ±
  * @param  
  *           
  * @retval 
  */

void Delay_us(uint32_t time)
{
	htim2.Instance->CNT = 0;
	__HAL_TIM_ENABLE(&htim2);
	while(htim2.Instance->CNT<(84*time));
	__HAL_TIM_ENABLE(&htim2);
}

/**
  * @brief  ms ÑÓÊ± 
  * @param  time <15887
  *              
  * @retval                                                                                                                    
  */
void Delay_ms(uint32_t time)
{
	htim2.Instance->CNT = 0;
	__HAL_TIM_ENABLE(&htim2);
	while(htim2.Instance->CNT<(84000*time));
	__HAL_TIM_ENABLE(&htim2);
}
/**
  * @brief  È«¾Ö±äÁ¿³õÊ¼»¯
  * @param  
  *              
  * @retval                                                                                                                    
  */
void Data_Init(USERPRV * _userprv)
{
	_userprv->m_ucUSBRXFlag = 0;
	_userprv->m_ucETHRXFLAG = 0;
	_userprv->m_ucTIM3Count = 0;
	_userprv->m_ucCommendFlag = 0;
	_userprv->m_usSampleWay = 0;
	_userprv->m_usOneMeterPaus = 0;
	_userprv->m_ucRExitflag = 0;
	
	_userprv->m_ucReadMoRenFlag = 0;
	_userprv->m_ucWriteMoRenFlag = 0;
	
	_userprv->m_usOneFramNUM = 0;
	_userprv->m_usSampleSpan = 0;
	_userprv->m_usMoNiQiSpeed = 0;
	_userprv->m_ucTransDataON = 0;
	_userprv->m_ucSlefTestON = 0;
	_userprv->m_ucMoNiQiDirec = 0;
	_userprv->m_usSendCmdVal = 0;
	
	_userprv->m_iTimer4UpdateCnt = 0;
	_userprv->m_uiBMQVal = 0x7fffffff;
	
	 _userprv->m_uiBMQSTAVal = 0x7fffffff;
	
	_userprv->m_tIPinformation.WriteFlag = 0x97fddb90;
	
  _userprv->m_tInstrument.hand = 0xffffbbaa;
	_userprv->m_tInstrument.end =  0xffffaabb;
	
	_userprv->m_tCommendStack.DATA1 = 0xffff;
	_userprv->m_tCommendStack.DATA2 = 0x97fd;
	
	_userprv->m_tModelDes.hand = 0xffffaadd;
	_userprv->m_tModelDes.type = 0x2;
	_userprv->m_tModelDes.state = 0x4;
	_userprv->m_tModelDes.ID = 0x3001;
	_userprv->m_tModelDes.end = 0xffffddaa;
	
	_userprv->m_tSystemState.hand = 0xffffbbee;
	_userprv->m_tSystemState.depth = 0x7fffffff;
	_userprv->m_tSystemState.time = 0;
	_userprv->m_tSystemState.strain = 0xffffffff;
	_userprv->m_tSystemState.end = 0xffffeebb;
	
	_userprv->m_tLoggingStaHand.hand = 0xffffabcd;
	_userprv->m_tLoggingStaEnd.end = 0xffffdcba;
	
	_userprv->m_tYA_ZhongZi.hand = 0xffff97fd;
	_userprv->m_tYA_ZhongZi.num = 0x0c;
	_userprv->m_tYA_ZhongZi.type = 0x3006;
	
	_userprv->m_tIPinformation.DNS.data[3] = 144;
	_userprv->m_tIPinformation.DNS.data[2] = 144;
	_userprv->m_tIPinformation.DNS.data[1] = 144;
	_userprv->m_tIPinformation.DNS.data[0] = 144;
	
	_userprv->m_tIPinformation.Severs.data[3] = 192;
	_userprv->m_tIPinformation.Severs.data[2] = 168;
	_userprv->m_tIPinformation.Severs.data[1] = 0;
	_userprv->m_tIPinformation.Severs.data[0] = 100;
	
	_userprv->m_tIPinformation.port = 5050;
	_userprv->m_tIPinformation.WriteFlag = 0X97FDDB90;
	_userprv->m_uiMoniqicnt = 0x7fffffff;
	
	_userprv->m_ucFLUSH_YJP = 0x0;
	
}

/**
  * @brief  ´æ´¢Ä¬ÈÏ²ÎÊıµ«ÊÇÖ»´æ²»±äµÄ¼¸¸ö²ÎÊı 
  * @param  µÚÒ»¸ö ³õÊ¼Öµ µÚ¶ş¸ö Ã¿Ã×Ã¿Ã×Âö³åÊı µÈµÈµÈ
  *              
  * @retval                                                                                                                    
  */
 unsigned char databuff1[30] = {0x00};
void Read_MoRen_Val(USERPRV * _userprv)//Write_MoRen_Val
{
	AT24CXX_Read(0x04,databuff1,24);
	_userprv->m_uiBMQSTAVal = (databuff1[0]<<24)+(databuff1[1]<<16)+(databuff1[2]<<8)+(databuff1[3]);
	_userprv->m_usSampleSpan = (databuff1[4]<<24)+(databuff1[5]<<16)+(databuff1[6]<<8)+(databuff1[7]);	
	_userprv->m_tModelDes.ID = (databuff1[8]<<24)+(databuff1[9]<<16)+(databuff1[10]<<8)+(databuff1[11]);
	_userprv->m_usOneFramNUM = (databuff1[12]<<8)+(databuff1[13]);	
	_userprv->m_usOneMeterPaus = (databuff1[14]<<8)+(databuff1[15]);
	_userprv->m_ucBaud = databuff1[16];
	_userprv->m_usSampleWay = databuff1[17];
	_userprv->m_ucMoNiQiDirec = databuff1[18];
	_userprv->m_ucCommendFlag = databuff1[19];//_userprv->m_ucCommendFlag
	_userprv->m_usMoNiQiSpeed = (databuff1[20]<<8)+(databuff1[21]);	
	_userprv->m_ucWaitTime = databuff1[22];
  _userprv->m_ucWaitTime1 = databuff1[23];
	
	Set_Baud(	_userprv->m_ucBaud );
  _userprv->m_usSendCmdVal = _userprv->m_usOneFramNUM;
}
/**
  * @brief  ¶ÁÈ¡Ä¬ÈÏ²ÎÊı
  * @param  
  *              
  * @retval                                                                                                                    
  */
 unsigned char databuff[30] = {0x00};//{0x36,0x37,0x38,0x39,0x13,0x40,0x10,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x50,0x51,0x53,0x54};
void Write_MoRen_Val(USERPRV * _userprv)//
{
	databuff[0] = (_userprv->m_uiBMQSTAVal>>24)&0xff;
	databuff[1] = (_userprv->m_uiBMQSTAVal>>16)&0xff;
	databuff[2] = (_userprv->m_uiBMQSTAVal>>8)&0xff;
	databuff[3] = (_userprv->m_uiBMQSTAVal)&0xff;
	//AT24CXX_Write(0x04,databuff,4);
	//µÚ¶şÒ³
	databuff[4] = (_userprv->m_usSampleSpan>>24)&0xff;
	databuff[5] = (_userprv->m_usSampleSpan>>16)&0xff;
	databuff[6] = (_userprv->m_usSampleSpan>>8)&0xff;
	databuff[7] = (_userprv->m_usSampleSpan)&0xff;
	//AT24CXX_Write(8,databuff,4);
	databuff[8] = (_userprv->m_tModelDes.ID>>24)&0xff;
	databuff[9] = (_userprv->m_tModelDes.ID>>16)&0xff;
	databuff[10] = (_userprv->m_tModelDes.ID>>8)&0xff;
	databuff[11] = (_userprv->m_tModelDes.ID)&0xff;
	//AT24CXX_Write(12,databuff,4);
	//µÚÈıÒ³
	databuff[12] = (_userprv->m_usOneFramNUM>>8)&0xff;
	databuff[13] = (_userprv->m_usOneFramNUM)&0xff;
	//AT24CXX_Write(16,databuff,2);
	databuff[14] = (_userprv->m_usOneMeterPaus>>8)&0xff;
	databuff[15] = (_userprv->m_usOneMeterPaus)&0xff;
	//AT24CXX_Write(18,databuff,2);
	databuff[16] = (_userprv->m_ucBaud)&0xff;
	//AT24CXX_Write(20,databuff,1);
	databuff[17] = (_userprv->m_usSampleWay)&0xff;
	//AT24CXX_Write(21,databuff,1);
	databuff[18] = (_userprv->m_ucMoNiQiDirec)&0xff;
	databuff[19] = _userprv->m_ucCommendFlag;
	
	databuff[20] = (_userprv->m_usMoNiQiSpeed>>8)&0xff;
	databuff[21] = _userprv->m_usMoNiQiSpeed&0xff;
	databuff[22] = _userprv->m_ucWaitTime;
	databuff[23] = _userprv->m_ucWaitTime1;
	AT24CXX_Write(0x04,databuff,24); 
}

/**
  * @brief  »ñÈ¡±àÂëÆ÷µÄÖµ
  * @param  
  *              
  * @retval 
  */
void Get_BMQValue(USERPRV * _userprv)
{
	_userprv->m_uiBMQVal = _userprv->m_iTimer4UpdateCnt*65535+htim4.Instance->CNT+0x7fffffff;
}
/**
  * @brief  ÅĞ¶ÏÊÇ·ñÊÇAĞÍÄ£¿é
  * @param  
  *              
  * @retval 
  */
void Judge_A_Moudle(USERPRV * _userprv)
{
	if((!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_2))&&(!HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_3)))
	{
		_userprv->m_tModelDes.type = 0x2;
	}
	else
		_userprv->m_tModelDes.type = 0x3;
}



/**
  * @brief  ·ÖÎöÍ¨ÓÃÃüÁî
  * @param  
  * 
  * @retval 
  */
void _analyse_(uint8_t * pdata,USERPRV * _userprv)
{
	uint16_t cmd1 = 0,cmd2 = 0,cmd3 = 0,cmd4 = 0,cmd5 = 0,cmd6 = 0,cmd7 = 0,cmd8 = 0,cmd9 = 0,cmd10 = 0;
	uint16_t data1 = 0,data2 = 0;
	cmd1 = (pdata[5]<<8)+pdata[6];
	cmd2 = (pdata[9]<<8)+pdata[10];
	cmd3 = (pdata[13]<<8)+pdata[14];
	cmd4 = (pdata[17]<<8)+pdata[18];
	cmd5 = (pdata[21]<<8)+pdata[22];
	cmd6 = (pdata[27]<<8)+pdata[28];
	cmd7 = (pdata[33]<<8)+pdata[34];
	cmd8 = (pdata[37]<<8)+pdata[38];
	cmd9 = (pdata[41]<<8)+pdata[42];
	cmd10 = (pdata[45]<<8)+pdata[46];
	if(cmd1 == 0x0012)
	{
	  data1 = (pdata[7]<<2)+(pdata[8])+1;
		_userprv->m_ucBaud = (uint8_t)data1;
		Set_Baud(data1);
	}
  if(cmd2 == 0x0002)
	{
		_userprv->m_usOneMeterPaus = (pdata[11]<<8)+(pdata[12]);
	}
	if(cmd3 == 0x0003)
	{
		 _userprv->m_usOneFramNUM = (pdata[15]<<8)+(pdata[16])+1;
		 _userprv->m_usSendCmdVal = _userprv->m_usOneFramNUM;
	}
  if(cmd4 == 0x0004)
	{
		_userprv->m_usSampleWay = (pdata[19]<<8)+(pdata[20])+1;		
	}
	if(cmd5 == 0x0005)
	{
		_userprv->m_usSampleSpan = (pdata[23]<<24)+(pdata[24]<<16)+(pdata[25]<<8)+(pdata[26]);		
	}
	if(cmd6 == 0x0006)
	{
    _userprv->m_uiBMQVal = (pdata[29]<<24)+(pdata[30]<<16)+(pdata[31]<<8)+(pdata[32]);	
	}
	if(_userprv->m_usSampleWay == 3)
	{
	  if(cmd7 == 0x0007)
			{
					data2 = (pdata[35]<<8)+(pdata[36])+1;
					switch (data2)
					{
						case 0x0001:
							_userprv->m_usSampleWay = 0x2;
							break;
						case 0x0002:
							_userprv->m_usSampleWay = 0x3;
							break;
					}		
			}
	}
	if(cmd8 == 0x0008)
	{
		_userprv->m_usMoNiQiSpeed = (pdata[39]<<8)+(pdata[40]);		
	}
	if(cmd9 == 0x0009)
	{
		_userprv->m_ucMoNiQiDirec = (pdata[43]<<8)+(pdata[44])+1;		
	}
 if(cmd10 == 0x0016)
	{
		//_userprv->m_ucMoNiQiDirec = (pdata[43]<<8)+(pdata[44])+1;		
		_userprv->m_ucWaitTime = pdata[47];
	  _userprv->m_ucWaitTime1 = pdata[48];
	}
}
void Analyse_Common_cmd(uint8_t * pdata,uint16_t cmdtype,USERPRV * _userprv)
{
	switch (cmdtype)
	{
		case 0x0010:
			_userprv->m_ucChangeAB =~_userprv->m_ucChangeAB;
		  break;
		case 0x0011:
	//Òº¾§ÆÁÌáÊ¾½øÈëÍ¨ÓÃÅäÖÃÃüÁî Ä£Ê½
	  Lcd_Clear(YELLOW);
	  Gui_DrawFont_GBK24(5,5,BLACK,YELLOW,"Í¨ÓÃÃüÁîÅäÖÃ");
			break;
		case 0x0012:
			_analyse_(pdata,_userprv);
			_userprv->m_ucCommendFlag |=0x20;
      _userprv->m_ucWriteMoRenFlag = 1;
//		  //Write_At24c02(_userprv);
			Write_MoRen_Val(_userprv);
	    Lcd_Clear(BLUE);
	    Gui_DrawFont_GBK24(50,5,RED,BLUE,"²â¾®×´Ì¬");
		  Gui_DrawFont_GBK16(5,40,RED,BLUE,"²ÉÑù·½Ê½");
	    Gui_DrawFont_GBK16(5,60,RED,BLUE,"²ÉÑù¼ä¸ô");
		  Gui_DrawFont_GBK16(5,80,RED,BLUE,"Depth  :");
		  Gui_DrawFont_GBK16(5,100,RED,BLUE,"Time   :");
		  if(_userprv->m_usSampleWay == 0x01)
			{
				Gui_DrawFont_GBK16(90,40,RED,BLUE,"TIME");
			}
			else if(_userprv->m_usSampleWay == 0x02)
			{
				Gui_DrawFont_GBK16(90,40,RED,BLUE,"PULSE");
			}
			else
				Gui_DrawFont_GBK16(90,40,RED,BLUE,"SIMULATOR");
			Show_Num(90,60,RED,BLUE,_userprv->m_usSampleSpan);
			break;
		case 0x0014:
			Read_MoRen_Val(_userprv);
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
	    _userprv->m_ucReadMoRenFlag = 1;
		  Lcd_Clear(BLUE);
	    Gui_DrawFont_GBK24(50,5,RED,BLUE,"²â¾®×´Ì¬");
		  Gui_DrawFont_GBK16(5,40,RED,BLUE,"²ÉÑù·½Ê½");
	    Gui_DrawFont_GBK16(5,60,RED,BLUE,"²ÉÑù¼ä¸ô");
      Gui_DrawFont_GBK16(5,80,RED,BLUE,"Depth  :");
		  Gui_DrawFont_GBK16(5,100,RED,BLUE,"Time   :");
		  if(_userprv->m_usSampleWay == 0x1)
			{
				Gui_DrawFont_GBK16(90,40,RED,BLUE,"TIME");
			}
			else if(_userprv->m_usSampleWay == 0x2)
			{
				Gui_DrawFont_GBK16(90,40,RED,BLUE,"PULSE");
			}
			else
				Gui_DrawFont_GBK16(90,40,RED,BLUE,"SIMULATOR");
			  Show_Num(90,60,RED,BLUE,_userprv->m_usSampleSpan);
			break;
		default :
			break;
	}
	cmdtype = 0xffff;
}

/**
  * @brief  Analyse_3005_CMD
  * @param  
  *              
  * @retval 
  */
static void Analyse_3005_CMD(uint16_t NUM,uint16_t startdata,USERPRV * _userprv)
{

}

/**
  * @brief  ·ÖÎö¿ØÖÆÃüÁî
  * @param  
  *              
  * @retval 
  */
void Analyse_control_cmd(uint8_t * pdata,uint16_t cmdtype,USERPRV * _userprv)
{
	static uint16_t data = 0,data1 = 0,temp = 0,i = 0,j = 0;
	uint16_t tempcout  = 0,freecmdCount = 0;
	unsigned char  buff[50];
	unsigned short cmd = 0,val = 0;
	switch (cmdtype)
	{
		case 0x3002: //µÚÒ»±ØĞëµÈ´ı 512 »òÕß 4096 ¸öÊı¾İ·µ»ØÍê²Å¿ÉÒÔ¡£
			data = (pdata[7]<<8) + pdata[8];
		  data1 = (pdata[9]<<8)+pdata[10];
			//if(((_userprv->m_ucTransDataON)&&(_userprv->m_ucWaitReturnEnd == 0) )||(_userprv->m_ucTransDataON == 0))
		if((data == 0x3000)||(data == 0x2000))
		{
			Send_Data_To_FPGA_DoubleCmd(data,data1);
			_userprv->m_ucRExitflag = 0;
			while(!_userprv->m_ucRExitflag){}
		  if(_userprv->m_ucRExitflag == 1)
			{
				Read_Data_From_FPGA(&temp,1);
				if(_userprv->m_ucETHCommuFlag)
					TCP_server_out((uint8_t *)&temp,2);
				else if(_userprv->m_ucUSBCommuFlag)
					USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&temp,2);
			}
		}
		else
		  Send_Data_To_FPGA_DoubleCmd(data,data1);
			//else {} //ÕâÀïÎªÊ²Ã´²»¼ÓÉÏ´úÂëÚ« Ó¦Îª Âß¼­ÉÏÕâ¸÷else Óï¾äÊÇ²»»áÖ´ĞĞµÄ¡£³ÌĞòÊÇ°´Ë³ĞòÖ´ĞĞµÄ¡£ ËùÒÔÉÏÃæµÄ if ÅĞ¶ÏÒ²²»ĞèÒª¡£	
			break;
		case 0x3003:
		  data = (pdata[7]<<8)+(pdata[8]);
		   switch (data)
			 {
				 case 0x0001:
					 _userprv->m_ucTransDataON = 1;				 
					 break;
				 case 0x0002:
					 _userprv->m_ucTransDataON = 0;
					 break;
			 }
			break;
		case 0x3004:  //
      data = (pdata[7]<<8)+(pdata[8]);  
		 _userprv->m_ucSlefTestON = 1;
			Send_Data_To_FPGA_DoubleCmd(0X3000,data);
			_userprv->m_ucRExitflag = 0;
			while(!_userprv->m_ucRExitflag)
			{
				tempcout++;
				Delay_ms(1);
				if(tempcout>20)
				{
					tempcout =0;
					break;
				}			
			}
			if(_userprv->m_ucRExitflag)
			{
				tempcout = 0;
				Read_Data_From_FPGA(_userprv->m_usFPGARXbuff,0);
			  _userprv->m_tInstrument.data  = ((_userprv->m_usFPGARXbuff[0]>>8)&0xff)+((_userprv->m_usFPGARXbuff[0]&0xff)<<8); 
			  TCP_server_out((uint8_t *)&_userprv->m_tInstrument,12);
			}
		 data = 0;
			break;
			case 0x3005://ÕâÌõÃüÁîÊÕµ½ºó 407 ×Ô¶¯ÀÛ¼Ó·¢ËÍµÄ²ÎÊı ¡£ÏÈ°Ñ ¸öÊıÌáÈ¡³öÀ´ È»ºó ·¢ËÍÒ»¸öÊı¾İFPGA ¾Íµ¯»ØÒ»¸öÊı¾İ£¬Ö±µ½ËùÓĞµÄÊı¾İ¶¼ µ¯»ØÀ´ ÕâÌõÃüÁî²ÅËãÍê³É¡£ÕâÀï¸øFPGA  ¾Í ÓÃ3000 À´×.ö
			  _userprv->m_ucSlefTestON = 1;
			  data = (pdata[7]<<8)+(pdata[8]);
			  data1 = (pdata[9]<<8)+(pdata[10]);
			  temp = data1;
			  //Analyse_3005_CMD(data,data1,_userprv);
			 for(i = 0;i<data;i++)
				{
					_userprv->m_ucRExitflag = 0;
		      Send_Data_To_FPGA_DoubleCmd(0X3000,temp);
					while(!_userprv->m_ucRExitflag)
					{
						tempcout++;
						Delay_ms(1);
						if(tempcout>100)
						{
							tempcout =0;
							break;
						}			
					}
					if(_userprv->m_ucRExitflag)
					{
						tempcout = 0;
						Read_Data_From_FPGA(_userprv->m_usFPGARXbuff,0);
						_userprv->m_tInstrument.data =0x00000000;
						_userprv->m_tInstrument.data  = ((_userprv->m_usFPGARXbuff[0]>>8)&0xff)+((_userprv->m_usFPGARXbuff[0]&0xff)<<8); 
						TCP_server_out((uint8_t *)&_userprv->m_tInstrument,12);
					}
					else{
						tempcout = 0;
						_userprv->m_tInstrument.data =0x00000000;
						TCP_server_out((uint8_t *)&_userprv->m_tInstrument,12);
					}
				 temp+=1;
				 Delay_ms(m_userprv.m_ucWaitTime1);	 
				} 
			  break;
		  case 0x3006:
			////Ë«×ÖÃüÁî ·µ»ØÉ¶ÔõÃ´·µ»ØĞèÒªÓÃÊ¾²¨Æ÷¿´
			  buff[0] = 0xfd; buff[1] = 0x97; buff[2] = 0xff; buff[3] = 0xff;
			  buff[4] = 0x00; buff[5] = 0x00; buff[6] = 0x05; buff[7] = 0x30;
		    cmd = (pdata[7]<<8)+(pdata[8]);
		    val = (pdata[9]<<8)+(pdata[10]);
			  _userprv->m_ucRExitflag = 0;
			  Send_Data_To_FPGA_DoubleCmd(cmd,val);
			 	_userprv->m_ucALLDataReturnFlag = 0;
				while(1)
					{
						if(_userprv->m_ucRExitflag) 
						{
							_userprv->m_ucRExitflag = 0;
							Read_Data_From_FPGA(_userprv->m_usFPGARXbuff,freecmdCount);
							freecmdCount++;
						}
						if(_userprv->m_ucALLDataReturnFlag>10)//100ms Ã»ÓĞ·µ»ØÊı¾ÍÈÏÎª³ö´íÁË¡£
						{
							_userprv->m_ucALLDataReturnFlag = 0;
							break;
						}
					}
				for(i = 0;i<freecmdCount;i++)
					{
						buff[8+j] = (_userprv->m_usFPGARXbuff[i]>>8)&0xff;
						buff[9+j] = (_userprv->m_usFPGARXbuff[i])&0xff;
						j+=2;
					}
			  buff[4] = (freecmdCount>>8)&0xff;
			  buff[5] = (freecmdCount)&0xff;
				TCP_server_out(buff,50);
			  i = 0;
				j = 0;
				freecmdCount = 0;
			  _userprv->m_ucALLDataReturnFlag = 0;
			  break;
	}
}

/**
  * @brief  ·ÖÎöÉèÖÃIP²ÎÊıÃüÁî
  * @param  
  *   
  * @retval 
  */

void Set_IP(USERPRV * _userprv,uint8_t * databuff)
{
  uint16_t cmd = (databuff[5]<<8)+databuff[6];
	switch (cmd)
	{
		case 0x1000:
			Gui_DrawFont_GBK16(5,35,RED,GRAY1,"Ä£¿é  IP: ");
		  _userprv->m_tIPinformation.IP.data[3] = databuff[7];
      _userprv->m_tIPinformation.IP.data[2] = databuff[8];
      _userprv->m_tIPinformation.IP.data[1] = databuff[9];
      _userprv->m_tIPinformation.IP.data[0] = databuff[10];	
			Show_One_Line_Parameter(80,35,_userprv->m_tIPinformation.IP.data[3],
																	 _userprv->m_tIPinformation.IP.data[2],
																	 _userprv->m_tIPinformation.IP.data[1],
																	 _userprv->m_tIPinformation.IP.data[0],RED,GRAY1);		
			break;
		case 0x1001:
      Gui_DrawFont_GBK16(5,55,RED,GRAY1,"×ÓÍøÑÚÂë: ");
			_userprv->m_tIPinformation.SUBNET.data[3] = databuff[7];
      _userprv->m_tIPinformation.SUBNET.data[2] = databuff[8];
      _userprv->m_tIPinformation.SUBNET.data[1] = databuff[9];
      _userprv->m_tIPinformation.SUBNET.data[0] = databuff[10];
			Show_One_Line_Parameter(80,55,_userprv->m_tIPinformation.SUBNET.data[3],
																	 _userprv->m_tIPinformation.SUBNET.data[2],
																	 _userprv->m_tIPinformation.SUBNET.data[1],
																	 _userprv->m_tIPinformation.SUBNET.data[0],RED,GRAY1);		
		
			break;
		case 0x1002:
			Gui_DrawFont_GBK16(5,75,RED,GRAY1,"Ä¬ÈÏÍø¹Ø: ");
			_userprv->m_tIPinformation.NETWORK.data[3] = databuff[7];
      _userprv->m_tIPinformation.NETWORK.data[2] = databuff[8];
      _userprv->m_tIPinformation.NETWORK.data[1] = databuff[9];
      _userprv->m_tIPinformation.NETWORK.data[0] = databuff[10];
			Show_One_Line_Parameter(80,75,_userprv->m_tIPinformation.NETWORK.data[3],
																	 _userprv->m_tIPinformation.NETWORK.data[2],
																	 _userprv->m_tIPinformation.NETWORK.data[1],
																	 _userprv->m_tIPinformation.NETWORK.data[0],RED,GRAY1);		
			break;
		case 0x1003:
			Gui_DrawFont_GBK16(5,95,RED,GRAY1,"·şÎñÆ÷IP: ");
			Gui_DrawFont_GBK16(5,115,RED,GRAY1,"¶Ë¿Ú");
			_userprv->m_tIPinformation.Severs.data[3] = databuff[7];
      _userprv->m_tIPinformation.Severs.data[2] = databuff[8];
      _userprv->m_tIPinformation.Severs.data[1] = databuff[9];
      _userprv->m_tIPinformation.Severs.data[0] = databuff[10];	
			Show_One_Line_Parameter(80,95,_userprv->m_tIPinformation.Severs.data[3],
																	 _userprv->m_tIPinformation.Severs.data[2],
																	 _userprv->m_tIPinformation.Severs.data[1],
																	 _userprv->m_tIPinformation.Severs.data[0],RED,GRAY1);		
			Show_Num(80,115,RED,GRAY1,_userprv->m_tIPinformation.port);	
			break;
		case 0x1004:
			Gui_DrawFont_GBK16(5,135,RED,GRAY1,"DNS µØÖ·: ");
			_userprv->m_tIPinformation.DNS.data[3] = databuff[7];
      _userprv->m_tIPinformation.DNS.data[2] = databuff[8];
      _userprv->m_tIPinformation.DNS.data[1] = databuff[9];
      _userprv->m_tIPinformation.DNS.data[0] = databuff[10];
			Show_One_Line_Parameter(80,135,_userprv->m_tIPinformation.DNS.data[3],
																	 _userprv->m_tIPinformation.DNS.data[2],
																	 _userprv->m_tIPinformation.DNS.data[1],
																	 _userprv->m_tIPinformation.DNS.data[0],RED,GRAY1);	
			break;
		case 0x1006:
		  Lcd_Clear(GRAY2);
	    Gui_DrawFont_GBK24(50,50,RED,GRAY2,"ÅäÖÃÍê³É");
      Gui_DrawFont_GBK24(10,100,RED,GRAY2,"Çë¶ÏµçÖØÆôÉè±¸£¡");
			Write_FLASH(_userprv);
      Show_One_Minate(_userprv,5);
      _userprv->m_usConfigIPFlag = 0x1006;
			break;
	}
}

/**
  * @brief  ·ÖÎöÉèÖÃIP²ÎÊıÃüÁî
  * @param  
  *              
  * @retval 
  */
void Analyse_SetIP_cmd(USERPRV * _userprv,uint8_t * databuff)
{
	//Òº¾§ÆÁÌáÊ¾½øÈëÉèÖÃIP Ä£Ê½
	Lcd_Clear(GRAY1);
	Gui_DrawFont_GBK24(5,5,RED,GRAY1,"½øÈëÅäÖÃIPÄ£Ê½");
	_userprv->m_usConfigIPFlag = (databuff[5]<<8) + (databuff[6]);	
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
	while(1)
	{
		Set_IP(_userprv,_userprv->m_ucETHRXbuff);
		Delay_ms(500);
	}
}
/**
  * @brief  ·ÖÎöETH »òÕßÊÇUSBÃüÁî
  * @param  
  *              
  * @retval 
  */
void Analyse_EHT_USB_CMD(USERPRV * _userprv)
{
	uint16_t cmdtype = 0;
	if(_userprv->m_ucETHRXFLAG||_userprv->m_ucUSBRXFlag)
	{
		//HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	  //HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
		if(_userprv->m_ucETHRXFLAG)
		cmdtype = (_userprv->m_ucETHRXbuff[5]<<8)+(_userprv->m_ucETHRXbuff[6]);
		else if(_userprv->m_ucUSBRXFlag)
		cmdtype = (_userprv->m_ucUSBRXBuff[5]<<8)+(_userprv->m_ucUSBRXBuff[6]);
		if((cmdtype>0)&&(cmdtype<0x0fff))
		{
			if(_userprv->m_ucETHRXFLAG)
			  Analyse_Common_cmd(_userprv->m_ucETHRXbuff,cmdtype,_userprv);
			else if(_userprv->m_ucUSBRXFlag)
			  Analyse_Common_cmd(_userprv->m_ucUSBRXBuff,cmdtype,_userprv); 
		}
		else if((cmdtype >= 0x1000)&&(cmdtype<0x01fff))
		{
			if(_userprv->m_ucETHRXFLAG)
			  Analyse_SetIP_cmd(_userprv,_userprv->m_ucETHRXbuff);
			else if(_userprv->m_ucUSBRXFlag)
			  Analyse_SetIP_cmd(_userprv,_userprv->m_ucUSBRXBuff); 
		}
		else if((cmdtype >= 0x2000)&&(cmdtype<0x02fff))
		{
			
		}
		else if((cmdtype >= 0x3000)&&(cmdtype<0x03fff))
		{
			if(_userprv->m_ucETHRXFLAG)
			  Analyse_control_cmd(_userprv->m_ucETHRXbuff,cmdtype,_userprv);
			else if(_userprv->m_ucUSBRXFlag)
			  Analyse_control_cmd(_userprv->m_ucUSBRXBuff,cmdtype,_userprv);
		}
		else if((cmdtype >= 0x4000)&&(cmdtype<0x0ffff))//´ı¶¨
		{
			
		}
	}
	_userprv->m_ucETHRXFLAG = 0;
	_userprv->m_ucUSBRXFlag = 0;
}

/**
  * @brief  ·¢ËÍÊı¾İ°üÀ¨²â¾®×´Ì¬Êı¾İ ÒÇÆ÷¼ì²â×´Ì¬Êı¾İ
  * @param  
  *              
  * @retval 
  */
extern void Send_Fixed_Fpga_Data(uint16_t num,uint8_t * buff);
void Trans_Data(USERPRV * _userprv)
{
	uint16_t FPGAData = 0;
	static uint16_t num = 0;
	char buff[20];
  if(_userprv->m_ucTransDataON )     //Õâ¸öµØ·½»¹Òª¼ÓÉÏ Í£Ö¹FALG 
	{
		//HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);
		switch (_userprv->m_usSampleWay)
		{
			case 1://Ê±¼ä·½Ê½ 				
					_userprv->m_uiBMQVal = _userprv->m_iTimer4UpdateCnt*65535+htim4.Instance->CNT;
          _userprv->m_tLoggingStaHand.timespan = htim5.Instance->CNT;
					_userprv->m_tLoggingStaHand.depth = htim4.Instance->CNT;//Éî¶ÈÊÇ¸ù¾İ¹âµç±àÂë Æ÷»ñµÃ  »òÕß Ä£ÄâÆ÷»ñµÃ 
			    sprintf(buff,"%d",_userprv->m_tLoggingStaHand.depth);
			    Gui_DrawFont_GBK16(90,80,RED,BLUE,buff);
				  sprintf(buff,"%d",_userprv->m_tLoggingStaHand.timespan);
		      Gui_DrawFont_GBK16(90,100,RED,BLUE,buff);
					//_userprv->m_tSystemState.depth = _userprv->m_tLoggingStaHand.depth;
					_userprv->m_tSystemState.time = _userprv->m_tLoggingStaHand.timespan;
					if((_userprv->m_tLoggingStaHand.timespan-_userprv->m_uiTime)>_userprv->m_usSampleSpan)//¶¨Ê±¼ä ¼ä¸ô²É¼¯
					{
						if(_userprv->m_ucETHCommuFlag)//eth Í¨ĞÅ
						TCP_server_out((uint8_t *)&_userprv->m_tLoggingStaHand,sizeof(_userprv->m_tLoggingStaHand));
						else if(_userprv->m_ucUSBCommuFlag)//usb Í¨ĞÅ
						USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&_userprv->m_tLoggingStaHand,sizeof(_userprv->m_tLoggingStaHand));
						//ÕıÔÚ·¢ËÍÊı¾İ µÈ´ıflag ÖÃÎ»
						_userprv->m_ucWaitReturnEnd = 1;
						//·¢ËÍ·µ»ØÊı¾İÃüÁî
					  Send_Data_To_FPGA_OneCmd(_userprv->m_usSendCmdVal);//0x1000 0x1200
						_userprv->m_ucALLDataReturnFlag = 0;
						while(1)
						{
							if(_userprv->m_ucRExitflag)
							{
								//¶¼»ØÊı¾İ
								Read_Data_From_FPGA(_userprv->m_usFPGARXbuff,num);
								//·¢ËÍ»ØÈ¥
								if(num == 255)
								{
									_userprv->m_tLoggingStaEnd.num +=256;
								   Send_Fixed_Fpga_Data(num,(uint8_t *)&_userprv->m_usFPGARXbuff);
									 num = 0;
								}
							  num++;
								_userprv->m_ucRExitflag = 0;
								_userprv->m_ucALLDataReturnFlag = 0;
							}
							if(_userprv->m_ucALLDataReturnFlag>_userprv->m_ucWaitTime)
							{
								_userprv->m_ucALLDataReturnFlag = 0;
								if(num >= 2)
								{
									num+=1;
									_userprv->m_tLoggingStaEnd.num +=num;
									Send_Fixed_Fpga_Data(num,(uint8_t *)&_userprv->m_usFPGARXbuff);
									num = 0;
								}
 								break;
							}
						}
						//½«Î²°Í ·¢ËÍ»ØÈ¥
						if(_userprv->m_ucETHCommuFlag)
							TCP_server_out((uint8_t *)&_userprv->m_tLoggingStaEnd,sizeof(_userprv->m_tLoggingStaEnd));
						else if(_userprv->m_ucUSBCommuFlag)
							USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&_userprv->m_tLoggingStaEnd,sizeof(_userprv->m_tLoggingStaEnd));
						//¸üĞÂÊ±¼ä
						_userprv->m_uiTime = _userprv->m_tLoggingStaHand.timespan;
						//·¢ËÍÊı¾İµÈ´ıflag ÇåÁã
						_userprv->m_ucWaitReturnEnd = 0;
						_userprv->m_tLoggingStaEnd.num = 0;
					}
				break;
				
			case 2://Âö³å·½Ê½
				  _userprv->m_uiBMQVal = _userprv->m_iTimer4UpdateCnt*65535+htim4.Instance->CNT;
          _userprv->m_tLoggingStaHand.timespan = htim5.Instance->CNT;//»ñÈ¡µ±Ç°Ê±¼ä
					_userprv->m_tLoggingStaHand.depth = htim4.Instance->CNT;//Éî¶ÈÊÇ¸ù¾İ¹âµç±àÂë Æ÷»ñµÃ  »òÕß Ä£ÄâÆ÷»ñµÃ
					_userprv->m_tSystemState.depth = _userprv->m_tLoggingStaHand.depth;
					_userprv->m_tSystemState.time = _userprv->m_tLoggingStaHand.timespan;	
			    sprintf(buff,"%d",_userprv->m_tLoggingStaHand.depth);
			    Gui_DrawFont_GBK16(90,80,RED,BLUE,buff);
				  sprintf(buff,"%d",_userprv->m_tLoggingStaHand.timespan);
		      Gui_DrawFont_GBK16(90,100,RED,BLUE,buff);			
					if((_userprv->m_uiBMQVal-_userprv->m_uiBMQValLast)>_userprv->m_usSampleSpan)//¶¨Ê±¼ä ¼ä¸ô²É¼¯
					{
						if(_userprv->m_ucETHCommuFlag)//eth Í¨ĞÅ
						  TCP_server_out((uint8_t *)&_userprv->m_tLoggingStaHand,sizeof(_userprv->m_tLoggingStaHand));
						else if(_userprv->m_ucUSBCommuFlag)//usb Í¨ĞÅ
						  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&_userprv->m_tLoggingStaHand,sizeof(_userprv->m_tLoggingStaHand));
						//ÕıÔÚ·¢ËÍÊı¾İ µÈ´ıflag ÖÃÎ»
						_userprv->m_ucWaitReturnEnd = 1;
						//·¢ËÍ·µ»ØÊı¾İÃüÁî
					  Send_Data_To_FPGA_OneCmd(_userprv->m_usSendCmdVal);//0x1000 0x1200
						_userprv->m_ucALLDataReturnFlag = 0;
					  while(1)
						{
							if(_userprv->m_ucRExitflag)
							{
								//¶¼»ØÊı¾İ
								Read_Data_From_FPGA(_userprv->m_usFPGARXbuff,num);
								//·¢ËÍ»ØÈ¥
								if(num == 255)
								{
									 _userprv->m_tLoggingStaEnd.num+=256; 
								   Send_Fixed_Fpga_Data(num,(uint8_t *)&_userprv->m_usFPGARXbuff);
									 num = 0;
								}
							  num++;
//								if(_userprv->m_ucETHCommuFlag)
//									TCP_server_out((uint8_t *)&FPGAData,2);
//								else if(_userprv->m_ucUSBCommuFlag)
//									USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&FPGAData,2);
								_userprv->m_ucRExitflag = 0;
								_userprv->m_ucALLDataReturnFlag = 0;
							}
							if(_userprv->m_ucALLDataReturnFlag>_userprv->m_ucWaitTime)
							{
								_userprv->m_ucALLDataReturnFlag = 0;
								if(num >= 2)
									{
										num+=1;
										_userprv->m_tLoggingStaEnd.num +=num;
										Send_Fixed_Fpga_Data(num,(uint8_t *)&_userprv->m_usFPGARXbuff);
										num = 0;
									}
								break;
							}
						}
						//½«Î²°Í ·¢ËÍ»ØÈ¥
						if(_userprv->m_ucETHCommuFlag)
							TCP_server_out((uint8_t *)&_userprv->m_tLoggingStaEnd,sizeof(_userprv->m_tLoggingStaEnd));
						else if(_userprv->m_ucUSBCommuFlag)
							USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&_userprv->m_tLoggingStaEnd,sizeof(_userprv->m_tLoggingStaEnd));
						_userprv->m_tLoggingStaEnd.num = 0;
						//¸üĞÂÂö³å¼ÆÊı
						_userprv->m_uiBMQValLast = _userprv->m_uiBMQVal;
						//·¢ËÍÊı¾İµÈ´ıflag ÇåÁã
						_userprv->m_ucWaitReturnEnd = 0;
						_userprv->m_tLoggingStaEnd.num  = 0;
					}					 
				break;
				
			case 3://Ä£ÄâÆ÷·½Ê½
				  _userprv->m_uiBMQVal = _userprv->m_uiMoniqicnt;
          _userprv->m_tLoggingStaHand.timespan = htim5.Instance->CNT;//»ñÈ¡µ±Ç°Ê±¼ä
					_userprv->m_tLoggingStaHand.depth = _userprv->m_uiMoniqicnt/10*_userprv->m_usMoNiQiSpeed;//Éî¶ÈÊÇ¸ù¾İ¹âµç±àÂë Æ÷»ñµÃ  »òÕß Ä£ÄâÆ÷»ñµÃ
					_userprv->m_tSystemState.depth = _userprv->m_tLoggingStaHand.depth;
					_userprv->m_tSystemState.time = _userprv->m_tLoggingStaHand.timespan;	
				  sprintf(buff,"%d",_userprv->m_tLoggingStaHand.depth);
			    Gui_DrawFont_GBK16(90,80,RED,BLUE,buff);
				  sprintf(buff,"%d",_userprv->m_tLoggingStaHand.timespan);
		      Gui_DrawFont_GBK16(90,100,RED,BLUE,buff);
					if((_userprv->m_uiMoniqicnt-_userprv->m_uiMoniqicntlast)>_userprv->m_usSampleSpan)//¶¨Ê±¼ä ¼ä¸ô²É¼¯
					{
						if(_userprv->m_ucETHCommuFlag)//eth Í¨ĞÅ
						  TCP_server_out((uint8_t *)&_userprv->m_tLoggingStaHand,sizeof(_userprv->m_tLoggingStaHand));
						else if(_userprv->m_ucUSBCommuFlag)//usb Í¨ĞÅ
						  USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&_userprv->m_tLoggingStaHand,sizeof(_userprv->m_tLoggingStaHand));
						//ÕıÔÚ·¢ËÍÊı¾İ µÈ´ıflag ÖÃÎ»
						_userprv->m_ucWaitReturnEnd = 1;
						//·¢ËÍ·µ»ØÊı¾İÃüÁî
					  Send_Data_To_FPGA_OneCmd(_userprv->m_usSendCmdVal);//0x1000 0x1200
						_userprv->m_ucALLDataReturnFlag = 0;
						while(1)
						{
							if(_userprv->m_ucRExitflag)
							{
								//¶¼»ØÊı¾İ
								Read_Data_From_FPGA(_userprv->m_usFPGARXbuff,num);
								//·¢ËÍ»ØÈ¥
								if(num == 255)
								{
									 _userprv->m_tLoggingStaEnd.num +=256;
								   Send_Fixed_Fpga_Data(num,(uint8_t *)&_userprv->m_usFPGARXbuff);
									 num = 0;
								}
							  num++;
//								if(_userprv->m_ucETHCommuFlag)
//									TCP_server_out((uint8_t *)&FPGAData,2);
//								else if(_userprv->m_ucUSBCommuFlag)
//									USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&FPGAData,2);
								_userprv->m_ucRExitflag = 0;
								_userprv->m_ucALLDataReturnFlag = 0;
							}
							if(_userprv->m_ucALLDataReturnFlag>_userprv->m_ucWaitTime)
							{
								if(num >= 2)
									{
										num+=1;
										_userprv->m_tLoggingStaEnd.num +=num;
										Send_Fixed_Fpga_Data(num,(uint8_t *)&_userprv->m_usFPGARXbuff);
										num = 0;
									}
								_userprv->m_ucALLDataReturnFlag = 0;
								break;
							}
						}
						//½«Î²°Í ·¢ËÍ»ØÈ¥
						if(_userprv->m_ucETHCommuFlag)
							TCP_server_out((uint8_t *)&_userprv->m_tLoggingStaEnd,sizeof(_userprv->m_tLoggingStaEnd));
						else if(_userprv->m_ucUSBCommuFlag)
							USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&_userprv->m_tLoggingStaEnd,sizeof(_userprv->m_tLoggingStaEnd));
						//¸üĞÂÂö³å¼ÆÊı
            _userprv->m_uiMoniqicntlast = _userprv->m_uiMoniqicnt ;
						//·¢ËÍÊı¾İµÈ´ıflag ÇåÁã
						_userprv->m_ucWaitReturnEnd = 0;
						_userprv->m_tLoggingStaEnd.num  = 0;
					}									
				break;
			default :
				Delay_ms(1);
				break;
		}
	}
	else
	{
		
	}
}

/**
  * @brief Ù¤ÂíÍ¨ĞÅ¼ì²â ÖĞ×ÓÍ¨ĞÅ¼ì²â Êı¾İ³õÊ¼»¯
  * @param  
  *              
  * @retval 
  */
void Zhongzi_Yama_Data_Init(TEST_Y * test_y,TEST_Z *  test_z)
{
	uint32_t i = 0;
	uint8_t j = 0;
	uint8_t flag = 0;
	uint16_t temp = 0x094a;
	
	for(i = 0;i<DATACHECKLength;i++)
	{
		test_y[i].head = 0x3000;
		if(!flag)
		{
		  test_y[i].value = (temp<<j)&0x0fff;
		}
		else
		  test_y[i].value = (temp>>j)&0x0fff;	
		if(j==12)
		{
			j = 0;
			flag = !flag;
		}
		j++;
	}
	j = 0;
	flag = 0;
	for(i = 0;i<256;i++)
	{
		test_z[i].head = 0x2000;
		if(!flag)
		{
		  test_z[i].value = (temp<<j)&0x0fff;
		}
		else
		  test_z[i].value = (temp>>j)&0x0fff;	
		if(j==12)
		{
			j = 0;
			flag = !flag;
		}
		j++;
	}
}

/**
  * @brief Ù¤ÂíÍ¨ĞÅ²âÊÔ ÖĞ×ÓÍ¨ĞÅ²âÊÔ 
  * @param  
  *              
  * @retval 
  */
uint8_t Z_Y_TestFunc(USERPRV * _userprv)
{
	uint8_t data,data1;
	uint8_t trans = 0;
  uint16_t i = 0;
	uint16_t  tempcout = 0;
	uint16_t tempval = 0;
	float errorcount = 0.0f;

	if(_userprv->m_ucYamaFlag)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
    Lcd_Clear(GREEN);
		Gui_DrawFont_GBK24(30,5,RED,GREEN,"Ù¤ÂíÖĞ×ÓÎóÂëÂÊ");
		Gui_DrawFont_GBK24(5,40,RED,GREEN,"Ù¤Âí");
    trans = _userprv->m_ucTransDataON;
		_userprv->m_ucTransDataON = 2;
		for(i = 0;i<DATACHECKLength;i++)
		{
			Send_Data_To_FPGA_DoubleCmd(_userprv->m_tTest_Y[i].head,_userprv->m_tTest_Y[i].value);
			_userprv->m_ucRExitflag = 0;
			while(!_userprv->m_ucRExitflag)
			{
				tempcout++;
				Delay_ms(1);
				if(tempcout>20)
				{
					tempcout =0;
					errorcount+=1;
					break;
				}			
			}
			if(_userprv->m_ucRExitflag)
			{
				tempcout = 0;
				Read_Data_From_FPGA(&_userprv->m_usTestRxbuff[i],0);
			}
			data = (uint8_t)(_userprv->m_usTestRxbuff[i]&0xff);
			data1 = (uint8_t)(_userprv->m_usTestRxbuff[i]>>8);
			tempval = (data<<8)+data1;
			if(tempval != _userprv->m_tTest_Y[i].value)
			{
				errorcount+=1;
			}
			Delay_ms(50);
    }
	  _userprv->m_fYamaError = errorcount/DATACHECKLength;
		Show_Num_float(5,70,RED,GREEN,_userprv->m_fYamaError);
		_userprv->m_ucTransDataON = 2;
	  _userprv->m_tYA_ZhongZi.allnum = DATACHECKLength;
		_userprv->m_tYA_ZhongZi.errornum = errorcount;
		_userprv->m_tYA_ZhongZi.Y_Z = 0x02;
		TCP_server_out((uint8_t *)&_userprv->m_tYA_ZhongZi,14);
		Show_One_Minate(_userprv,5);
		_userprv->m_ucTransDataON = trans;	  
		Lcd_Clear(BLUE);
		Gui_DrawFont_GBK24(50,5,RED,BLUE,"²â¾®×´Ì¬");
		Gui_DrawFont_GBK16(5,40,RED,BLUE,"²ÉÑù·½Ê½");
		Gui_DrawFont_GBK16(5,60,RED,BLUE,"²ÉÑù¼ä¸ô");
    Gui_DrawFont_GBK16(5,80,RED,BLUE,"Depth  :");
		Gui_DrawFont_GBK16(5,100,RED,BLUE,"Time   :");
		if(_userprv->m_usSampleWay == 0x1)
		{
			Gui_DrawFont_GBK16(90,40,RED,BLUE,"TIME");
		}
		else if(_userprv->m_usSampleWay == 0x2)
		{
			Gui_DrawFont_GBK16(90,40,RED,BLUE,"PULSE");
		}
		else
			Gui_DrawFont_GBK16(90,40,RED,BLUE,"SIMULATOR");
		Show_Num(90,60,RED,BLUE,_userprv->m_usSampleSpan);
		_userprv->m_ucYamaFlag = 0;
	}
	//ÖĞ×Ó
	if(_userprv->m_ucZhongziFlag)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);
		Lcd_Clear(GREEN);
		Gui_DrawFont_GBK24(30,5,RED,GREEN,"Ù¤ÂíÖĞ×ÓÎóÂëÂÊ");
	  Gui_DrawFont_GBK24(5,40,RED,GREEN,"ÖĞ×Ó");
	  _userprv->m_ucTransDataON = 2;
		for(i = 0;i<DATACHECKLength;i++)
		{
			Send_Data_To_FPGA_DoubleCmd(_userprv->m_tTest_Y[i].head,_userprv->m_tTest_Y[i].value);
			_userprv->m_ucRExitflag = 0;
			while(!_userprv->m_ucRExitflag)
			{
					tempcout++;
					Delay_ms(1);
					if(tempcout>20)
					{
						tempcout =0;
						errorcount+=1;
						break;
					}			
			}
			if(_userprv->m_ucRExitflag)
			{
				tempcout = 0;
				Read_Data_From_FPGA(&_userprv->m_usTestRxbuff[i],0);
			}
			data = (uint8_t)(_userprv->m_usTestRxbuff[i]&0xff);
			data1 = (uint8_t)(_userprv->m_usTestRxbuff[i]>>8);
			tempval = (data<<8)+data1;			
			if(tempval != _userprv->m_tTest_Y[i].value)
			{
				errorcount+=1;
			}
			Delay_ms(50);
    }
	  _userprv->m_fYamaError = errorcount/DATACHECKLength;
		Show_Num_float(5,70,RED,GREEN,_userprv->m_fYamaError);
		_userprv->m_ucTransDataON = 2;
		_userprv->m_tYA_ZhongZi.allnum = DATACHECKLength;
		_userprv->m_tYA_ZhongZi.errornum = errorcount;
		_userprv->m_tYA_ZhongZi.Y_Z = 0x01;
		TCP_server_out((uint8_t *)&_userprv->m_tYA_ZhongZi,14);
		Show_One_Minate(_userprv,5);
		_userprv->m_ucTransDataON = trans;	
		Lcd_Clear(BLUE);
		Gui_DrawFont_GBK24(50,5,RED,BLUE,"²â¾®×´Ì¬");
		Gui_DrawFont_GBK16(5,40,RED,BLUE,"²ÉÑù·½Ê½");
		Gui_DrawFont_GBK16(5,60,RED,BLUE,"²ÉÑù¼ä¸ô");
    Gui_DrawFont_GBK16(5,80,RED,BLUE,"Depth  :");
		Gui_DrawFont_GBK16(5,100,RED,BLUE,"Time   :");
		if(_userprv->m_usSampleWay == 0x1)
		{
			Gui_DrawFont_GBK16(90,40,RED,BLUE,"TIME");
		}
		else if(_userprv->m_usSampleWay == 0x2)
		{
			Gui_DrawFont_GBK16(90,40,RED,BLUE,"PULSE");
		}
		else
			Gui_DrawFont_GBK16(90,40,RED,BLUE,"SIMULATOR");
		Show_Num(90,60,RED,BLUE,_userprv->m_usSampleSpan);
		_userprv->m_ucZhongziFlag = 0;		
	}
	return 1;
}	

/**
  * @brief  ÔÚ´«ÊäÊı¾İ¿ª¹ØÎªµ×µÄÊ±ºò ¸üĞÂÊ±¼äĞÅÏ¢ºÍÉî¶ÈĞÅÏ¢
  * @param  
  *              
  * @retval 
  */
void 	Updata_Time_Depth(USERPRV * _userprv)
{
	  if(_userprv->m_ucTransDataON == 0)
		{
			_userprv->m_uiBMQVal = _userprv->m_iTimer4UpdateCnt*65535+htim4.Instance->CNT;
			_userprv->m_tSystemState.depth = _userprv->m_uiBMQVal;
			_userprv->m_tSystemState.time = htim5.Instance->CNT;
		}
}
/**
  * @brief  ´¦Àí 3004 ×Ô¼ì
  * @param  
  *              
  * @retval 
  */
void DealWith_0x3004(USERPRV * _userprv)
{
	
}
/**
  * @brief  A Ä£¿éº¯Êı
  * @param  
  *              
  * @retval 
  */
void A_Moudel_Function(USERPRV * _userprv)
{
  Analyse_EHT_USB_CMD(_userprv);
	Trans_Data(_userprv);
	Z_Y_TestFunc(_userprv);
	Updata_Time_Depth(_userprv);
	if(_userprv->m_ucFLUSH_YJP)//Ë¢ĞÂÒº¾§ÆÁ
	{
		_userprv->m_ucFLUSH_YJP = 0;
		Welcome_Page(_userprv);
	}
	if(_userprv->m_ucOneScnt>20)
	{
		_userprv->m_ucOneScnt = 0;
	  AT24CXX_Write(0x00,(uint8_t *)&_userprv->m_uiBMQVal,4);
	}
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET);
}

/**
  * @brief  A_B Ä£¿éº¯Êı
  * @param  
  *              
  * @retval 
  */
void A_B_Moudel_Function(USERPRV * _userprv)
{
	switch (_userprv->m_tModelDes.type)
	{
		case 0x2://A ĞÍ»ú
			A_Moudel_Function(_userprv);
			break;
		case 0x3://BĞÍ»ú
			
		  break;
		default:
			Delay_ms(1);
		  break;
	}
}
/**
  * @brief  ÅĞ¶ÏAB Ä£¿é
  * @param  
  *              
  * @retval 
  */
void Judge_A_B_Moudel(USERPRV * _userprv)
{
	if((HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_2) == RESET)&&(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_3) == RESET))
	{
		_userprv->m_tModelDes.type = 0x02;
	}
	else
		_userprv->m_tModelDes.type = 0x3;
}
/**
  * @brief  ¿ªÊ¼»¶Ó­½çÃæ
  * @param  
  *              
  * @retval 
  */
void Welcome_Page(USERPRV * _userprv)
{
	showimage(gImage_start,0,0);
	Gui_DrawFont_GBK24(50,80,RED,BLUE,"»¶Ó­Ê¹ÓÃ£¡");
	Gui_DrawFont_GBK16(5,120,RED,BLUE, "TYPE:");
	if(_userprv->m_tModelDes.type == 0x2)
    Gui_DrawFont_GBK16(48,120,RED,BLUE, "A");
	else
	  Gui_DrawFont_GBK16(48,120,RED,BLUE, "B");
	Gui_DrawFont_GBK16(5,150,RED,BLUE, "ID  :");
  Show_Num(48,150,RED,BLUE,_userprv->m_tModelDes.ID);
}

/**
  * @brief  Ğ´EEPROM
  * @param  
  *              
  * @retval 
  */
extern I2C_HandleTypeDef hi2c1;
void Write_At24c02(USERPRV * _userprv)
{
	if(HAL_I2C_Mem_Write(&hi2c1,AT24C0XXDEVICEADRR,0x04,8,(uint8_t *)&_userprv->m_uiBMQVal,4,1) == HAL_OK)
	{
		Show_Num(48,150,RED,BLUE,1);
	}
	else
		Show_Num(48,150,RED,BLUE,2);
}
/**
  * @brief  ¶ÁAT24C02
  * @param  
  *              
  * @retval 
  */
void Read_At24c02(USERPRV * _userprv)
{
	if(HAL_I2C_Mem_Read(&hi2c1, AT24C0XXDEVICEADRR, 0x04, 8, (uint8_t *)&_userprv->m_uiBMQVal, 4, 1)==HAL_OK)
	{
		Show_Num(48,150,RED,BLUE,3);
	}
	else
		Show_Num(48,150,RED,BLUE,4);
}

/**
  * @brief  ·¢ËÍ Ä£¿éËµÃ÷
  * @param  
  *              
  * @retval 
  */
void Send_Moudel(USERPRV * _userprv)
{
	TCP_server_out((unsigned char *)&_userprv->m_tModelDes,sizeof(_userprv->m_tModelDes));
}

