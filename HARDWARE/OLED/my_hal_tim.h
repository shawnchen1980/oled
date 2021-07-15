/**
  ******************************************************************************
  * @file    TIM/TIM_TimeBase/Inc/main.h
  * @author  MCD Application Team
  * @brief   Header for main.c module
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2016 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MY_HAL_TIM_H
#define __MY_HAL_TIM_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
//#include "stm32l0xx_nucleo_32.h"

/* TIM handle declaration */
extern TIM_HandleTypeDef    TimHandle;

/* Prescaler declaration */
extern uint32_t uwPrescalerValue;

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* User can use this section to tailor TIMx instance used and associated
   resources */
/* Definition for TIMx clock resources */
#define TIMx                           TIM2
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()


/* Definition for TIMx's NVIC */
#define TIMx_IRQn                      TIM2_IRQn
#define TIMx_IRQHandler                TIM2_IRQHandler

/* Exported functions ------------------------------------------------------- */
void Timer_Init();
#endif /* __MY_HAL_TIM_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
