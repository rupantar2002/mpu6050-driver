#include "mpu6050_port.h"
#include "mpu6050_reg.h"

void mpu6050_port_Init(mpu6050_port_t *const pHandle,
		mpu6050_port_config_t *const pConfig) {
//
//	if (pHandle != NULL && pConfig != NULL) {
//		I2C_HandleTypeDef *const pI2c = &pHandle->i2cHandle;
//		pI2c->Instance = pConfig->i2cPort;
//		pI2c->Init.ClockSpeed = pConfig->clockSpeed;
//		pI2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
//		pI2c->Init.OwnAddress1 = 0;
//		pI2c->Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
//		pI2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
//		pI2c->Init.OwnAddress2 = 0;
//		pI2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
//		pI2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
//		HAL_I2C_Init(&hi2c2);
//	}

}

int32_t mpu6050_port_ReadMemory(mpu6050_port_t *const pHandle,
		uint8_t registerAddr, uint8_t *const buffer, uint16_t len) {

	if (pHandle != NULL) {
		HAL_I2C_Mem_Read(&pHandle->i2cHandle, (MPU6050_I2C_ADDR_AD0_L << 1),
				registerAddr, 1, buffer, len, 100U);
	}
}

int32_t mpu6050_port_WriteMemory(mpu6050_port_t *const pHandle,
		uint8_t registerAddr, uint8_t const*const buffer, uint16_t len) {

	if (pHandle != NULL) {
		HAL_I2C_Mem_Write(&pHandle->i2cHandle, (MPU6050_I2C_ADDR_AD0_L << 1),
				registerAddr, 1, buffer, len, 100U);
	}
}

void mpu6050_port_Reset(mpu6050_port_t *const pHandle) {

	if (pHandle != NULL) {
		HAL_I2C_DeInit(&pHandle->i2cHandle);
	}
}
