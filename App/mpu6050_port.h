#ifndef  __MPU6050_PORT_H__
#define __MPU6050_PORT_H__

#include <stdint.h>
#include <stdbool.h>

typedef struct{
	uint8_t i2cPort;
	int32_t sclGpio;
	int32_t sdaGpio;
	bool sclPullupEnable;
	bool sdaPullupEnable;
}mpu6050_port_i2c_config_t;


void mpu6050_port_I2cInit(const mpu6050_port_i2c_config_t *pConfig);

//void mpu6050_port_I2cReadMemory()

void mpu6050_port_I2cReset(void);

#endif //__MPU6050_PORT_H__
