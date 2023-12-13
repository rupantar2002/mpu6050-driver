#include "app.h"
#include "stm32f407xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_i2c.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//mpu6050
#include "mpu6050_reg.h"

int32_t IntfRead(void *handle, uint8_t addr, uint8_t reg_addr,
		uint8_t *const data, uint16_t len) {
	return HAL_I2C_Mem_Read(handle, addr, reg_addr, 1, data, len,
	HAL_MAX_DELAY);

}

int32_t IntfWrite(void *handle, uint8_t addr, uint8_t reg_addr,
		uint8_t *const data, uint16_t len) {
	return HAL_I2C_Mem_Write(handle, addr, reg_addr, 1, data, len,
	HAL_MAX_DELAY);
}

typedef struct {
	void *handle;
	int32_t (*read_register)(void *handle, uint8_t addr, uint8_t reg_addr,
			uint8_t *constdata, uint16_t len);
	int32_t (*write_register)(void *handle, uint8_t addr, uint8_t reg_addr,
			uint8_t *constdata, uint16_t len);
} mpu6050_intf_t;

static I2C_HandleTypeDef gI2cIns;
static const mpu6050_intf_t gMpu6050 = { .handle = &gI2cIns, .read_register =
		IntfRead, .read_register = IntfWrite, };

static uint8_t gAddress = 0x00;

//static void PrintRegisterState(uint8_t reg, uint8_t *val) {
//	if (val == NULL)
//		return;
//	uint8_t val;
//	switch (reg) {
//	case MPU6050_WHO_AM_I: {
//		printf("WHO_AM_I[0x%02x]==0x%02x\r\n", reg, *val);
//	}
//		break;
//	}
//	case MPU6050_PWR_MGMT_1:
//	{
//		mpu6050_pwr_mgmt_1_t pwrMgm1={0};
//		memcpy(&pwrMgm1,)
//		break;
//	}
//	default:
//	{
//		break;
//	}
//}

static void InitI2c(void) {
	gI2cIns.Instance = I2C1;
	gI2cIns.Init.ClockSpeed = 100000;
	gI2cIns.Init.DutyCycle = I2C_DUTYCYCLE_2;
	gI2cIns.Init.OwnAddress1 = 0;
	gI2cIns.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	gI2cIns.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	gI2cIns.Init.OwnAddress2 = 0;
	gI2cIns.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	gI2cIns.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
	(void) HAL_I2C_Init(&gI2cIns);
}

static uint8_t I2cDetectAddresses(void) {

	uint8_t i, data = 0, found = false;
	HAL_StatusTypeDef ret = HAL_ERROR;
	for (i = 0; i <= 127; i++) {
		data = 0;
		ret = HAL_I2C_Master_Transmit(&gI2cIns, (i << 1) | 1, data, 1,
		HAL_MAX_DELAY);
		if (ret == HAL_OK) {
			printf("device found in addr:0x%2x\r\n", i);
			found = true;
			break;

		} else if (ret == HAL_TIMEOUT) {
			printf("HAL_TIMEOUT addr:0x%2x\r\n", i);
		} else if (ret == HAL_BUSY) {
			printf("HAL_BUSY addr:0x%2x\r\n", i);
		} else {
			// do nothing
		}
	}
	return (found == true ? i : 0xff);
}

static uint8_t ReadAccelerometer(uint8_t addr, int *arr) {
	uint8_t data[6] = { 0 };
	int16_t accelX = 0, accelY = 0, accelZ = 0;
	IntfRead(&gI2cIns, addr, MPU6050_ACEL_XOUT_H,data, 6);
	accelX = ((data[0] << 8) | data[1]);
	accelY = ((data[2] << 8) | data[3]);
	accelZ = ((data[4] << 8) | data[5]);
	printf("{accelX: %d, accelY: %d,accelZ: %d}\r\n", accelX, accelY, accelZ);
}

void app_Init(void) {
	printf("--------MPU6050-------------\r\n");
	InitI2c();
	// MPU6050
	uint8_t addr = 0xff;
	addr = I2cDetectAddresses();
	if (addr > 0 && addr < 0xff)
		printf("I2c addr-> 0x%02x\r\n", addr);
	else
		return;

	// read WHO_AM_I
	uint8_t whoAmI = 0x00;
	if (IntfRead(&gI2cIns, (addr << 1), MPU6050_WHO_AM_I, &whoAmI, 1) == 0
			&& whoAmI == 0x68) {
		gAddress = addr;
		printf("MPU6050 device\r\n");
	} else {
		printf("no device\r\n");
		return;
	}

	// reset device
	mpu6050_pwr_mgmt_1_t data = { 0 };
	IntfWrite(&gI2cIns, (addr << 1), MPU6050_PWR_MGMT_1, &data, 1);

}

void app_ProcessLoop(void) {
	ReadAccelerometer((gAddress << 1), NULL);
	HAL_Delay(100);
}

