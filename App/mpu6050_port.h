#ifndef  __MPU6050_PORT_H__
#define __MPU6050_PORT_H__

#include <stdint.h>
#include <stdbool.h>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_i2c.h"



typedef struct{
	I2C_HandleTypeDef i2cHandle;
}mpu6050_port_t;

typedef struct{
	I2C_TypeDef i2cPort;
	uint32_t clockSpeed;
//	GPIO_TypeDef sclGpio;
//	GPIO_TypeDef sdaGpio;
//	bool sclPullupEnable;
//	bool sdaPullupEnable;
}mpu6050_port_config_t;


void mpu6050_port_Init(mpu6050_port_t *const pHandle,mpu6050_port_config_t *const pConfig);

int32_t mpu6050_port_ReadMemory(mpu6050_port_t *const pHandle,uint8_t registerAddr,uint8_t *const buffer,uint16_t len);

int32_t mpu6050_port_WriteMemory(mpu6050_port_t *const pHandle,uint8_t registerAddr,uint8_t *const buffer,uint16_t len);

void mpu6050_port_I2cReset(mpu6050_port_t *const pHandle);

#endif //__MPU6050_PORT_H__
