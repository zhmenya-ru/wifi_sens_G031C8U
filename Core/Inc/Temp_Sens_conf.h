/*
 * Temp_Sens_conf.h
 *
 *  Created on: 8 февр. 2022 г.
 *      Author: STM
 */

#ifndef INC_TEMP_SENS_CONF_H_
#define INC_TEMP_SENS_CONF_H_
#include "gpio.h"
#include "tim.h"

#define DHT11_use 			0
#define DHT22_use			0
#define DS18B20_use			1
#define DS18S20_use			0
#define Sens_Port			GPIOA
#define Sens_Pin			GPIO_PIN_2
#define DelayTIM				htim1
//PA2

//HCLK 50MHz
//static void MX_TIM6_Init(void)
//{
//
//  /* USER CODE BEGIN TIM6_Init 0 */
//
//  /* USER CODE END TIM6_Init 0 */
//
//  TIM_MasterConfigTypeDef sMasterConfig = {0};
//
//  /* USER CODE BEGIN TIM6_Init 1 */
//
//  /* USER CODE END TIM6_Init 1 */
//  htim6.Instance = TIM6;
//  htim6.Init.Prescaler = 50-1;
//  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
//  htim6.Init.Period = 0xffff-1;
//  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
//  {
//    Error_Handler();
//  }
//  /* USER CODE BEGIN TIM6_Init 2 */
//
//  /* USER CODE END TIM6_Init 2 */
//
//}



#endif /* INC_TEMP_SENS_CONF_H_ */
