/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
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
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_it.h"
#include "keypad.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0+ Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles Non maskable interrupt.
*/
#include "stdio.h"

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

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
  /* USER CODE BEGIN HardFault_IRQn 1 */

  /* USER CODE END HardFault_IRQn 1 */
}

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void)
{
  /* USER CODE BEGIN SVC_IRQn 0 */

  /* USER CODE END SVC_IRQn 0 */
  /* USER CODE BEGIN SVC_IRQn 1 */

  /* USER CODE END SVC_IRQn 1 */
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
int syst=0;
extern uint8_t value;
/**
* @brief This function handles System tick timer.
*/
//系统时钟每读100个数去读取一下矩阵键盘，如果键盘有输入，对value赋值lrudoc->对应左右上下确认取消
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */
	syst++;
	if(syst==100){
			char	t=GetKey();
			if(t){
				switch(t){
					case KEY_LEFT:
						value='l';
						break;
					case KEY_RIGHT:
						value='r';
						break;
					case KEY_UP:
						value='u';
						break;
					case KEY_DOWN:
						value='d';
						break;
					case KEY_OK:
						value='o';
						break;
					case KEY_CANCEL:
						value='c';
						break;

				}
			}
		printf("systick handler");
		syst=0;
	}

  /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/
/**
  * @brief This function handles USART2 global interrupt / USART2 wake-up interrupt through EXTI line 26.
  */
extern UART_HandleTypeDef UartHandle;
extern __IO ITStatus UartReady;


int count=0;
//下列串口中断处理程序会将收到的报文放入getBuffer缓存区
void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */
//printf("entering usart2_irqhandler\n");
	
		uint8_t res = 0;
	
	//接收中断
	if(__HAL_UART_GET_FLAG(&UartHandle,UART_FLAG_RXNE) != RESET)
	{
		HAL_UART_Receive(&UartHandle,&res,1,1000);
		//将数据放入缓冲区
		if(res >0 )
		{
			getBuffer[count++] = res; 
			getBuffer[count]=0;
		}
		
		__HAL_UART_CLEAR_FLAG(&UartHandle,UART_FLAG_RXNE);
	}
	if(__HAL_UART_GET_FLAG(&UartHandle,UART_FLAG_IDLE)!=RESET)
    	{
			
    	  __HAL_UART_CLEAR_IDLEFLAG(&UartHandle);
				
				if(count>0){
//				printf("%s",(char*)getBuffer);
					
				value=getBuffer[0];
    	 	count=0;
				return;}
				//__HAL_UART_CLEAR_IDLEFLAG(&UartHandle);
           // rt_memset(lpuart_recv_buff,0,sizeof(lpuart_recv_buff));
            
    	} 
  /* USER CODE END USART2_IRQn 0 */
  //HAL_UART_IRQHandler(&UartHandle);
	
	
  /* USER CODE BEGIN USART2_IRQn 1 */

//     if(getBuffer[count-1] == 0x04)
//    {
//     
//     count = 0;
//    }
         //HAL_UART_Receive_IT(&UartHandle, (uint8_t *)&value,1); //Because the receive interrupt is entered every time a character is received, this line of code must be added, otherwise only one character can be received, and the entire string cannot be received.

  /* USER CODE END USART2_IRQn 1 */
}
/* USER CODE BEGIN 1 */

//回调函数
void USART2_IdleCallback(uint8_t *pData,uint16_t len)
{
	while(__HAL_UART_GET_FLAG(&UartHandle,UART_FLAG_TC) != SET);
	
	HAL_UART_Transmit(&UartHandle,pData,len,1000);
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */

extern TIM_HandleTypeDef    TimHandle;
void TIM2_IRQHandler(void)
{
	//printf("timer hander");
  HAL_TIM_IRQHandler(&TimHandle);
}
/**
  * @brief  Period elapsed callback in non blocking mode
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
 // printf("timer interrupt!\n");
	value='t';
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
