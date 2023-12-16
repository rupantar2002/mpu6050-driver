#ifndef __MPU6050_H__
#define __MPU6050_H__
#include "mpu6050_reg.h"
#include "mpu6050_port.h"

typedef enum {
	MPU6050_STATUS_SUCCESS = 0,
	MPU6050_STATUS_FAILOUR,
	MPU6050_STATUS_NULL_PTR,
	MPU6050_STATUS_UNINITIALIZED,
	MPU6050_STATUS_UNDEFINED,
	MPU6050_STATUS_TIMEOUT,
	MPU6050_STATUS_BUSY,
} mpu6050_status_t;

#define MPU6050_USE_VECTOR

#ifdef MPU6050_USE_VECTOR

typedef struct{
	float xAxis;
	float yAxis;
	float zAxis;
}mpu6050_vector_t;


#endif


typedef struct {
	I2C_HandleTypeDef *pI2cHandle;
	uint8_t deviceAddr;
	float rangePerDigit;
	float dpsPerDigit;
} mpu6050_t;

uint8_t mpu6050_Init(mpu6050_t *const pDevice, uint8_t addr,
		I2C_HandleTypeDef *const pI2cHandle);

uint8_t mpu6050_Reset(mpu6050_t *const pDevice);

uint8_t mpu6050_GetTemperature(mpu6050_t *const pDevice, float *pTemperature);

uint8_t mpu6050_GetAccelerometerScale(mpu6050_t *const pDevice,mpu6050_accel_fs_t *pFullscale);

uint8_t mpu6050_SetAccelerometerScale(mpu6050_t *const pDevice,mpu6050_accel_fs_t fullscale);

uint8_t mpu6050_GetRawAcceleration(mpu6050_t *const pDevice,mpu6050_vector_t *pVector);

uint8_t mpu6050_GetGyroscopeScale(mpu6050_t *const pDevice,mpu6050_gyro_fs_t *pFullscale);

uint8_t mpu6050_SetGyroscopeScale(mpu6050_t *const pDevice,mpu6050_gyro_fs_t fullscale);

uint8_t mpu6050_GetRawGyroscope(mpu6050_t *const pDevice,mpu6050_vector_t *pVector);

#endif //__MPU6050_H__
