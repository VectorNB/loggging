/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

/* USER CODE BEGIN 0 */
#include "lwip.h"
#include "user.h"
#include "server.h"
extern USERPRV m_userprv;
extern USBD_HandleTypeDef hUsbDeviceFS;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern TIM_HandleTypeDef htim4;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
* @brief This function handles Hard fault interrupt.
*/
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */
   //wait();
	if (CoreDebug->DHCSR & 1) {  //check C_DEBUGEN == 1 -> Debugger Connected  
      __breakpoint(0);  // halt program execution here         
  }  
  while (1)  
  {  
  }  
  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles Memory management fault.
*/
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN MemoryManagement_IRQn 1 */

  /* USER CODE END MemoryManagement_IRQn 1 */
}

/**
* @brief This function handles Pre-fetch fault, memory access fault.
*/
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN BusFault_IRQn 1 */

  /* USER CODE END BusFault_IRQn 1 */
}

/**
* @brief This function handles Undefined instruction or illegal state.
*/
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
  }
  /* USER CODE BEGIN UsageFault_IRQn 1 */

  /* USER CODE END UsageFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Debug monitor.
*/
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles USB On The Go FS global interrupt.
*/
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */
  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/* USER CODE BEGIN 1 */

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim1;//100 ms �жϡ�
extern TIM_HandleTypeDef htim4;
extern UART_HandleTypeDef huart1;
extern IWDG_HandleTypeDef hiwdg;
/**
* @brief 
*/
void TIM3_IRQHandler (void)
{
	m_userprv.m_ucTIM3Count++;
	m_userprv.m_ucALLDataReturnFlag++;
  if(m_userprv.m_ucTIM3Count>=24)  //��ETH���� �õ�
	{
		sys_check_timeouts();
	  m_userprv.m_ucTIM3Count = 0;
	}		
 __HAL_TIM_CLEAR_IT(&htim3,TIM_IT_UPDATE);
}

static uint8_t MoniqiCnt = 0;
void TIM1_UP_TIM10_IRQHandler(void) //�� ģ����ʹ�õ� 
{
	MoniqiCnt+=1;
	m_userprv.m_ucOneScnt++;
	if(MoniqiCnt == MONIQICUNT)
	{
		if(m_userprv.m_ucMoNiQiDirec == 0x0001)
			m_userprv.m_uiMoniqicnt +=1; 
		else if(m_userprv.m_ucMoNiQiDirec == 0x0002)
			m_userprv.m_uiMoniqicnt -=1;
		MoniqiCnt = 0;
	}
	// ι������
	HAL_IWDG_Refresh(&hiwdg);
  if(m_userprv.m_ucTransDataON == 0)
	{
		if(m_userprv.m_ucETHCommuFlag)  //�������� ���״̬����β ÿ100ms  ����һ��ϵͳ״̬����
			TCP_server_out((uint8_t *)&m_userprv.m_tSystemState,sizeof(m_userprv.m_tSystemState));
		else if(m_userprv.m_ucUSBCommuFlag)
			USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS,(uint8_t *)&m_userprv.m_tSystemState,sizeof(m_userprv.m_tSystemState));		
	}		
  __HAL_TIM_CLEAR_IT(&htim1,TIM_IT_UPDATE);
}

void TIM4_IRQHandler (void)//  ���� ������ ����
{	
	switch (htim4.Instance->CR1&0x0010)	
	{
		case 0x0010:
			m_userprv.m_iTimer4UpdateCnt-=1;
			__nop();
			break;
		case 0x0000:
			m_userprv.m_iTimer4UpdateCnt+=1;
			__nop();
			break;
	}
	 __HAL_TIM_CLEAR_IT(&htim4,TIM_IT_UPDATE);
}


/**
* @brief 
*/
static int uart1_rx_count = 0;
 void USART1_IRQHandler(void)
{
  uint32_t tmp_flag = 0, tmp_it_source = 0;
  tmp_flag = __HAL_UART_GET_FLAG(&huart1, UART_FLAG_RXNE);
  tmp_it_source = __HAL_UART_GET_IT_SOURCE(&huart1, UART_IT_RXNE);
  /* UART in mode Receiver ---------------------------------------------------*/
  if((tmp_flag != RESET) && (tmp_it_source != RESET))
  { 
	  m_userprv.m_ucUSARTRXBuff[uart1_rx_count++] =  (uint16_t)(huart1.Instance->DR & (uint16_t)0x01FF);
   if(m_userprv.m_ucUSARTRXBuff[0]!=0x97)
   {
     uart1_rx_count = 0;
   }
   if((m_userprv.m_ucUSARTRXBuff[uart1_rx_count-2]==0xdb)&&(m_userprv.m_ucUSARTRXBuff[uart1_rx_count-1]==0x90)&&(uart1_rx_count>2))
   {
     uart1_rx_count = 0;
     m_userprv.m_ucUSARTRXBuff[0] = 0xff;
		 m_userprv.m_ucUSARTRXFlag = 1;
		 m_userprv.m_ucFLUSH_YJP  = 1;
		 if(m_userprv.m_ucUSARTRXBuff[2] == 0x0a)
		 {
			 m_userprv.m_tModelDes.type = 0x2;
		 }
		 else if(m_userprv.m_ucUSARTRXBuff[2] == 0x0b)
		 {
			 m_userprv.m_tModelDes.type = 0x3;
		 }
   }
  }
	
}
/**
* @brief 
*/
void EXTI2_IRQHandler(void)
{
	if(m_userprv.m_ucRExitflag == 0)
	  m_userprv.m_ucRExitflag = 1;
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_2);
}

void EXTI3_IRQHandler(void)
{
  m_userprv.m_ucZhongziFlag = 1;
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_3);
}

void EXTI4_IRQHandler(void)
{
  m_userprv.m_ucYamaFlag = 1;
	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_4);
}

void EXTI9_5_IRQHandler(void)
{

	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_PIN_5);
}

/**
* @brief 
*/

#include "stm32f4xx_hal_eth.h"
extern struct netif gnetif;
/**
* @brief 
*/
uint32_t ETH_GetRxPktSize(ETH_HandleTypeDef *heth)
{
  uint32_t frameLength = 0;
  if(((heth->RxDesc->Status & ETH_DMARXDESC_OWN) == (uint32_t)RESET) &&
     ((heth->RxDesc->Status & ETH_DMARXDESC_ES) == (uint32_t)RESET) &&
     ((heth->RxDesc->Status & ETH_DMARXDESC_LS) != (uint32_t)RESET) &&
     ((heth->RxDesc->Status & ETH_DMARXDESC_FS) != (uint32_t)RESET))
  {
    /* Get the size of the packet: including 4 bytes of the CRC */
    frameLength = ((heth->RxDesc->Status&ETH_DMARXDESC_FL)>>ETH_DMARXDESC_FRAME_LENGTHSHIFT);
  }
	return  frameLength;
}
	
void ETH_IRQHandler(void)
{
  /* USER CODE BEGIN ETH_IRQn 0 */
  /* USER CODE END ETH_IRQn 0 */
  HAL_ETH_IRQHandler(&heth);
  /* USER CODE BEGIN ETH_IRQn 1 */
	
	while(ETH_GetRxPktSize(&heth)!=0)
	ethernetif_input(&gnetif);
	     /* Clear the Eth DMA Rx IT pending bits */
    __HAL_ETH_DMA_CLEAR_IT(&heth, ETH_DMA_IT_R);
    __HAL_ETH_DMA_CLEAR_IT(&heth,ETH_DMA_IT_NIS);
    /* Set HAL State to Ready */
    heth.State = HAL_ETH_STATE_READY;
  /* USER CODE END ETH_IRQn 1 */
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
