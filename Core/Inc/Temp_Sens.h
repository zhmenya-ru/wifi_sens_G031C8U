/*
 * Temp_Sens.h
 *
 *  Created on: 8 февр. 2022 г.
 *      Author: STM
 */

#ifndef INC_TEMP_SENS_H_
#define INC_TEMP_SENS_H_

#include "Temp_Sens_conf.h"
#if BME280_use==1

#endif

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

#if BME280_use==1
/* Configuration for the BME280

 * @osrs is the oversampling to improve the accuracy
 *       if osrs is set to OSRS_OFF, the respective measurement will be skipped
 *       It can be set to OSRS_1, OSRS_2, OSRS_4, etc. Check the header file
 *
 * @mode can be used to set the mode for the device
 *       MODE_SLEEP will put the device in sleep
 *       MODE_FORCED device goes back to sleep after one measurement. You need to use the BME280_WakeUP() function before every measurement
 *       MODE_NORMAL device performs measurement in the normal mode. Check datasheet page no 16
 *
 * @t_sb is the standby time. The time sensor waits before performing another measurement
 *       It is used along with the normal mode. Check datasheet page no 16 and page no 30
 *
 * @filter is the IIR filter coefficients
 *         IIR is used to avoid the short term fluctuations
 *         Check datasheet page no 18 and page no 30
 */

int BME280_Config (uint8_t osrs_t, uint8_t osrs_p, uint8_t osrs_h, uint8_t mode, uint8_t t_sb, uint8_t filter);


// Read the Trimming parameters saved in the NVM ROM of the device
void TrimRead(void);

/* To be used when doing the force measurement
 * the Device need to be put in forced mode every time the measurement is needed
 */
void BME280_WakeUP(void);

/* measure the temp, pressure and humidity
 * the values will be stored in the parameters passed to the function
 */
void BME280_Measure (void);


// Oversampling definitions
#define OSRS_OFF    	0x00
#define OSRS_1      	0x01
#define OSRS_2      	0x02
#define OSRS_4      	0x03
#define OSRS_8      	0x04
#define OSRS_16     	0x05

// MODE Definitions
#define MODE_SLEEP      0x00
#define MODE_FORCED     0x01
#define MODE_NORMAL     0x03

// Standby Time
#define T_SB_0p5    	0x00
#define T_SB_62p5   	0x01
#define T_SB_125    	0x02
#define T_SB_250    	0x03
#define T_SB_500    	0x04
#define T_SB_1000   	0x05
#define T_SB_10     	0x06
#define T_SB_20     	0x07

// IIR Filter Coefficients
#define IIR_OFF     	0x00
#define IIR_2       	0x01
#define IIR_4       	0x02
#define IIR_8       	0x03
#define IIR_16      	0x04


// REGISTERS DEFINITIONS
#define ID_REG      	0xD0
#define RESET_REG  		0xE0
#define CTRL_HUM_REG    0xF2
#define STATUS_REG      0xF3
#define CTRL_MEAS_REG   0xF4
#define CONFIG_REG      0xF5
#define PRESS_MSB_REG   0xF7

#endif

#endif /* INC_TEMP_SENS_H_ */
