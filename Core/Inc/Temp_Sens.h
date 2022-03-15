/*
 * Temp_Sens.h
 *
 *  Created on: 8 февр. 2022 г.
 *      Author: STM
 */

#ifndef INC_TEMP_SENS_H_
#define INC_TEMP_SENS_H_

#include "Temp_Sens_conf.h"

#if (DHT11_use==1)
#define DHT11_PORT 		Sens_Port
#define DHT11_PIN 		Sens_Pin
#endif

#if (DHT22_use==1)
#define DHT22_PORT 		Sens_Port
#define DHT22_PIN 		Sens_Pin
#endif

#if (DS18B20_use==1)
#define DS18B20_PORT 	Sens_Port
#define DS18B20_PIN 	Sens_Pin
#endif

void delay (uint16_t time);
void Set_Pin_Output (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void Set_Pin_Input (GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);

//DHT11
#if (DHT11_use==1)
void DHT11_Start (void);
uint8_t DHT11_Check_Response (void);
uint8_t DHT11_Read (void);
#endif

//DHT22
#if (DHT22_use==1)
void DHT22_Start (void);
uint8_t DHT22_Check_Response (void);
uint8_t DHT22_Read (void);
#endif

//DS18B20
#if (DS18B20_use==1)
uint8_t DS18B20_Start (void);
void DS18B20_Write (uint8_t data);
uint8_t DS18B20_Read (void);
#endif

#endif /* INC_TEMP_SENS_H_ */
