#include "mpu6050.h"
#include "stm32f4xx_hal_i2c.h"
#include <stdio.h>
#include <string.h>

static uint8_t ReadMemory(const mpu6050_t *const pHandle, uint8_t regAddr,
		uint8_t *const readBuff, uint16_t len) {

	HAL_StatusTypeDef status = HAL_I2C_Mem_Read(pHandle->pI2cHandle,
			(pHandle->deviceAddr << 1), regAddr, 1, readBuff, len, 100);
	if (status == HAL_OK)
		return MPU6050_STATUS_SUCCESS;
	else if (status == HAL_TIMEOUT)
		return MPU6050_STATUS_TIMEOUT;
	else if (status == HAL_BUSY)
		return MPU6050_STATUS_BUSY;
	else
		return MPU6050_STATUS_FAILOUR;

}

static uint8_t WriteMemory(const mpu6050_t *const pHandle, uint8_t regAddr,
		uint8_t *const readBuff, uint16_t len) {
	HAL_StatusTypeDef status = HAL_I2C_Mem_Write(pHandle->pI2cHandle,
			(pHandle->deviceAddr << 1), regAddr, 1, readBuff, len,
			HAL_MAX_DELAY);
	if (status == HAL_OK)
		return MPU6050_STATUS_SUCCESS;
	else if (status == HAL_TIMEOUT)
		return MPU6050_STATUS_TIMEOUT;
	else if (status == HAL_BUSY)
		return MPU6050_STATUS_BUSY;
	else
		return MPU6050_STATUS_FAILOUR;

}

uint8_t mpu6050_Init(mpu6050_t *const pDevice, uint8_t addr,
		I2C_HandleTypeDef *const pI2cHandle) {
	if (pDevice == NULL || pI2cHandle == NULL)
		return MPU6050_STATUS_NULL_PTR;

	// set a default address
	if (addr == 0)
		pDevice->deviceAddr = (uint8_t) MPU6050_I2C_ADDR_DEFAULT;

	// set i2c instance
	pDevice->pI2cHandle = pI2cHandle;

	uint8_t whoAmI = 0x00;

	// read device WHO_AM_I
	if (ReadMemory(pDevice, MPU6050_WHO_AM_I, &whoAmI, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;
	if (whoAmI != 0x68)
		return MPU6050_STATUS_UNDEFINED;
	printf("MPU6050 Device found\r\n");
	return MPU6050_STATUS_SUCCESS;
}

uint8_t mpu6050_Reset(mpu6050_t *const pDevice) {
	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;

	mpu6050_pwr_mgmt_1_t pwrMgm1 = { .clksel = 0, .cycle = 0, .device_reset = 0,
			.not_used_01 = 0, .sleep = 0, .temp_dis = 0, };

	uint8_t data = 0x00;
	(void) memcpy(&data, &pwrMgm1, 1);

	if (WriteMemory(pDevice, MPU6050_PWR_MGMT_1, &data, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;

	return MPU6050_STATUS_SUCCESS;
}

uint8_t mpu6050_GetTemperature(mpu6050_t *const pDevice, float *pTemperature) {
	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;
	uint8_t data[2];
	int16_t regValue = 0;
	float temperature = 0;

	if (ReadMemory(pDevice, MPU6050_TEMP_OUT_H, data, 2)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;

	regValue = (int16_t) ((data[0] << 8) | data[1]);
	temperature = (regValue / 340) + 36.53f;
	printf("temperature: %f degC\r\n", temperature);
	if (pTemperature != NULL)
		*pTemperature = temperature;
	return MPU6050_STATUS_SUCCESS;
}

uint8_t mpu6050_GetAccelerometerScale(mpu6050_t *const pDevice,
		mpu6050_accel_fs_t *pFullscale) {
	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;
	mpu6050_accel_config_t config = { 0 };

	if (ReadMemory(pDevice, MPU6050_ACCEL_CONFIG, &config, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;
	if (pFullscale != NULL)
		*pFullscale = config.afs_sel;
	printf("accel full scale get: %d\r\n", config.afs_sel);
	return MPU6050_STATUS_SUCCESS;
}

uint8_t mpu6050_SetAccelerometerScale(mpu6050_t *const pDevice,
		mpu6050_accel_fs_t fullscale) {

	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;

	mpu6050_accel_config_t config = { 0 };

	if (ReadMemory(pDevice, MPU6050_ACCEL_CONFIG, &config, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;

	config.afs_sel = fullscale;
	if (WriteMemory(pDevice, MPU6050_ACCEL_CONFIG, &config, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;
	printf("accel full scale set: %d\r\n", config.afs_sel);
	switch (config.afs_sel) {
	case MPU6050_ACCEL_FS_2G:
		pDevice->rangePerDigit = .000061f;
		break;
	case MPU6050_ACCEL_FS_4G:
		pDevice->rangePerDigit = .000122f;
		break;
	case MPU6050_ACCEL_FS_8G:
		pDevice->rangePerDigit = .000244f;
		break;
	case MPU6050_ACCEL_FS_16G:
		pDevice->rangePerDigit = .0004882f;
		break;
	}
	return MPU6050_STATUS_SUCCESS;
}

uint8_t mpu6050_GetRawAcceleration(mpu6050_t *const pDevice,
		mpu6050_vector_t *pVector) {
	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;

	uint8_t data[6];
	mpu6050_vector_t vector = { .xAxis = 0.0f, .yAxis = 0.0f, .zAxis = 0.0f };

	if (ReadMemory(pDevice, MPU6050_ACCEL_XOUT_H, data, 6)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;

	vector.xAxis = ((data[0] << 8) | data[1]) * pDevice->rangePerDigit;
	vector.yAxis = ((data[2] << 8) | data[3]) * pDevice->rangePerDigit;
	vector.zAxis = ((data[4] << 8) | data[5]) * pDevice->rangePerDigit;

	printf("raw acceleration :{ x: %f , y: %f, z: %f }\r\n", vector.xAxis,
			vector.yAxis, vector.zAxis);
	if (pVector != NULL)
		*pVector = vector;
	return MPU6050_STATUS_SUCCESS;
}

uint8_t mpu6050_GetGyroscopeScale(mpu6050_t *const pDevice,
		mpu6050_gyro_fs_t *pFullscale) {

	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;

	mpu6050_gyro_config_t config = { 0 };

	if (ReadMemory(pDevice, MPU6050_GYRO_CONFIG, &config, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;
	if (pFullscale != NULL)
		*pFullscale = config.fs_sel;
	printf("gyro full scale get: %d\r\n", config.fs_sel);
	return MPU6050_STATUS_SUCCESS;

}

uint8_t mpu6050_SetGyroscopeScale(mpu6050_t *const pDevice,
		mpu6050_gyro_fs_t fullscale) {
	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;

	mpu6050_gyro_config_t config = { 0 };

	if (ReadMemory(pDevice, MPU6050_GYRO_CONFIG, &config, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;

	config.fs_sel = fullscale;
	if (WriteMemory(pDevice, MPU6050_GYRO_CONFIG, &config, 1)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;
	printf("gyro full scale set: %d\r\n", config.fs_sel);
	switch (config.fs_sel) {
	case MPU6050_GYRO_FS_250_DEG_PER_SEC:
		pDevice->dpsPerDigit = .007633f;
		break;
	case MPU6050_GYRO_FS_500_DEG_PER_SEC:
		pDevice->dpsPerDigit = .015267f;
		break;
	case MPU6050_GYRO_FS_1000_DEG_PER_SEC:
		pDevice->dpsPerDigit = .030487f;
		break;
	case MPU6050_GYRO_FS_2000_DEG_PER_SEC:
		pDevice->dpsPerDigit = .060975f;
		break;
	}
	return MPU6050_STATUS_SUCCESS;

}

uint8_t mpu6050_GetRawGyroscope(mpu6050_t *const pDevice,
		mpu6050_vector_t *pVector) {
	if (pDevice == NULL)
		return MPU6050_STATUS_NULL_PTR;

	uint8_t data[6];
	mpu6050_vector_t vector = { .xAxis = 0.0f, .yAxis = 0.0f, .zAxis = 0.0f };

	if (ReadMemory(pDevice, MPU6050_GYRO_XOUT_H, data, 6)
			!= MPU6050_STATUS_SUCCESS)
		return MPU6050_STATUS_FAILOUR;

	vector.xAxis = ((data[0] << 8) | data[1]) * pDevice->dpsPerDigit;
	vector.yAxis = ((data[2] << 8) | data[3]) * pDevice->dpsPerDigit;
	vector.zAxis = ((data[4] << 8) | data[5]) * pDevice->dpsPerDigit;

	printf("raw gyroscope :{ x: %f , y: %f, z: %f }\r\n", vector.xAxis,
			vector.yAxis, vector.zAxis);
	if (pVector != NULL)
		*pVector = vector;
	return MPU6050_STATUS_SUCCESS;
}

