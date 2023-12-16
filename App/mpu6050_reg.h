#ifndef __MPU6050_REG_H__
#define __MPU6050_REG_H__

#include <stdint.h>

/**
 * I2c Address when AD0 pin is attached to VCC.
 */
#define MPU6050_I2C_ADDR_AD0_H (0x69)

/**
 * I2c Address when AD0 pin is attached to GND.
 */
#define MPU6050_I2C_ADDR_AD0_L (0x68)

/**
 * Default I2c address for device.
 */
#define MPU6050_I2C_ADDR_DEFAULT MPU6050_I2C_ADDR_AD0_L

#ifndef DRV_BYTE_ORDER

#ifndef __BYTE_ORDER__

#define DRV_LITTLE_ENDIAN 1234
#define DRV_BIG_ENDIAN    4321

/** if _BYTE_ORDER is not defined, choose the endianness of your architecture
 *  by uncommenting the define which fits your platform endianness
 */
#define DRV_BYTE_ORDER    DRV_BIG_ENDIAN
//#define DRV_BYTE_ORDER    DRV_LITTLE_ENDIAN

#else /* defined __BYTE_ORDER__ */

#define DRV_LITTLE_ENDIAN  __ORDER_LITTLE_ENDIAN__
#define DRV_BIG_ENDIAN     __ORDER_BIG_ENDIAN__
#define DRV_BYTE_ORDER     __BYTE_ORDER__

#endif /* __BYTE_ORDER__*/
#endif /* DRV_BYTE_ORDER */


/**
 * WHO_AM_I register location value should be 0x68 for mpu6050 devices.
 */
#define MPU6050_WHO_AM_I (0x75)

/**
 * Generate sample rate for mpu6050 from gyroscope output rate.
 * Sample rate=  GyroOutpurRate/(1+SMPRT_DIV)
 */
#define MPU6050_SMPRT_DIV (0x19)

/**
 * This register stores the upper byte of X axis
 * acceleration value.
 */
#define MPU6050_ACCEL_XOUT_H (0x3B)

/**
 * This register stores the lower byte of X axis
 * acceleration value.
 */
#define MPU6050_ACCEL_XOUT_L (0x3C)

/**
 * This register stores the upper byte of Y axis
 * acceleration value.
 */
#define MPU6050_ACCEL_YOUT_H (0x3D)

/**
 * This register stores the lower byte of Y axis
 * acceleration value.
 */
#define MPU6050_ACCEL_YOUT_L (0x3E)

/**
 * This register stores the upper byte of Z axis
 * acceleration value.
 */
#define MPU6050_ACCEL_ZOUT_H (0x3F)

/**
 * This register stores the lower byte of Z axis
 * acceleration value.
 */
#define MPU6050_ACEL_ZOUT_L (0x40)

/**
 * This register stores the upper byte of X axis
 * gyroscope value.
 */
#define MPU6050_GYRO_XOUT_H (0x43)

/**
 * This register stores the lower byte of X axis
 * gyroscope value.
 */
#define MPU6050_GYRO_XOUT_L (0x44)

/**
 * This register stores the upper byte of Y axis
 * gyroscope value.
 */
#define MPU6050_GYRO_YOUT_H (0x45)

/**
 * This register stores the lower byte of Y axis
 * gyroscope value.
 */
#define MPU6050_GYRO_YOUT_L (0x46)

/**
 * This register stores the upper byte of Z axis
 * gyroscope value.
 */
#define MPU6050_GYRO_ZOUT_H (0x47)

/**
 * This register stores the lower byte of Z axis
 * gyroscope value.
 */
#define MPU6050_GYRO_ZOUT_L (0x48)

/**
 * This register stores the upper byte of temperature data.
 */
#define MPU6050_TEMP_OUT_H (0x41)

/**
 * This register stores the lower byte of temperature data.
 */
#define MPU6050_TEMP_OUT_L (0x42)

/**
 * Config register location.
 */
#define MPU6050_CONFIG (0x1A)

/**
 *	Enumeration represents all external sync options.
 */
typedef enum {
	MPU6050_EXT_SYNC_INPUT_DISABLE = 0, /*<! FSYNC input disabled */
	MPU6050_EXT_SYNC_TEMP_OUT_L = 1, /*<! FSYNC bit location to TEMP_OUT_L register */
	MPU6050_EXT_SYNC_GYRO_XOUT_L = 2, /*<! FSYNC bit location to GYRO_XOUT_L register */
	MPU6050_EXT_SYNC_GYRO_YOUT_L = 3, /*<! FSYNC bit location to GYRO_YOUT_L register */
	MPU6050_EXT_SYNC_GYRO_ZOUT_L = 4, /*<! FSYNC bit location to GYRO_ZOUT_L register */
	MPU6050_EXT_SYNC_ACCEL_XOUT_L = 5,/*<! FSYNC bit location to ACCEL_XOUT_L register */
	MPU6050_EXT_SYNC_ACCEL_YOUT_L = 6, /*<! FSYNC bit location to ACCEL_YOUT_L register */
	MPU6050_EXT_SYNC_ACCEL_ZOUT_L = 7, /*<! FSYNC bit location to ACCEL_XOUT_L register */
} mpu6050_ext_sync_t;

/**
 *	Enumeration represents all Digital Low Pass Filter options.
 */
typedef enum {
	MPU6050_DLPF_CFG_0 = 0, /*<! Accelerometer bandwidth 260Hz, Gyroscope bandwidth 256Hz ,FrameSync 8Khz*/
	MPU6050_DLPF_CFG_1 = 1, /*<! Accelerometer bandwidth 184Hz, Gyroscope bandwidth 188Hz ,FrameSync 1Khz*/
	MPU6050_DLPF_CFG_2 = 2, /*<! Accelerometer bandwidth 94Hz, Gyroscope bandwidth 98Hz ,FrameSync 1Khz*/
	MPU6050_DLPF_CFG_3 = 3, /*<! Accelerometer bandwidth 44Hz, Gyroscope bandwidth 42Hz ,FrameSync 1Khz*/
	MPU6050_DLPF_CFG_4 = 4, /*<! Accelerometer bandwidth 21Hz, Gyroscope bandwidth 20Hz ,FrameSync 1Khz*/
	MPU6050_DLPF_CFG_5 = 5, /*<! Accelerometer bandwidth 10Hz, Gyroscope bandwidth 10Hz ,FrameSync 1Khz*/
	MPU6050_DLPF_CFG_6 = 6, /*<! Accelerometer bandwidth 5Hz, Gyroscope bandwidth 5Hz ,FrameSync 1Khz*/
} mpu6050_dlpf_cfg_t;

/**
 * Structure contains config register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t not_used_01 :2; /*<!Element contains 2 reserved bits */
	uint8_t ext_sync_set :3; /*<!Element contains external sync setting bits (ex : MPU6050_EXT_SYNC_TEMP_OUT_L) */
	uint8_t dlpf_cfg :3; /*<!Element contains DLPF config bits (ex : MPU6050_DLPF_CFG_0) */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t dlpf_cfg :3;
	uint8_t ext_sync_set :3;
	uint8_t not_used_01 :2;
#endif
} mpu6050_config_t;

/**
 *	Gyroscope config register location.
 */
#define MPU6050_GYRO_CONFIG (0x1B)

/**
 *	Enumeration represents all gyroscope full scale options.
 */
typedef enum {
	MPU6050_GYRO_FS_250_DEG_PER_SEC = 0, /*<! Gyroscope full scale +/-250 degree per second*/
	MPU6050_GYRO_FS_500_DEG_PER_SEC = 1, /*<! Gyroscope full scale +/-500 degree per second*/
	MPU6050_GYRO_FS_1000_DEG_PER_SEC = 2, /*<! Gyroscope full scale +/-1000 degree per second*/
	MPU6050_GYRO_FS_2000_DEG_PER_SEC = 3, /*<! Gyroscope full scale +/-2000 degree per second*/
} mpu6050_gyro_fs_t;

/**
 * Structure contains gyro config register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t xg_st :1;  /*<!Element contains X axis self test perform bit */
	uint8_t yg_st :1; /*<!Element contains Y axis self test perform bit */
	uint8_t zg_st :1; /*<!Element contains Z axis self test perform bit */
	uint8_t fs_sel :2; /*<!Element contains full scale bits ( ex: MPU6050_GYRO_FS_250_DEG_PER_SEC) */
	uint8_t not_used_01 :3; /*<!Element contains 3 reserved bits */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t not_used_01 :3;
	uint8_t fs_sel :2;
	uint8_t zg_st :1;
	uint8_t yg_st :1;
	uint8_t xg_st :1;
#endif
} mpu6050_gyro_config_t;

/**
 * Accelerometer config register location.
 */
#define MPU6050_ACCEL_CONFIG (0x1C)

/**
 *	Enumeration represents all accelerometer full scale options.
 */
typedef enum {
	MPU6050_ACCEL_FS_2G = 0, /*<! Accelerometer full scale +/-2g */
	MPU6050_ACCEL_FS_4G = 1, /*<! Accelerometer full scale +/-4g */
	MPU6050_ACCEL_FS_8G = 2, /*<! Accelerometer full scale +/-8g */
	MPU6050_ACCEL_FS_16G = 3, /*<! Accelerometer full scale +/-16g */
} mpu6050_accel_fs_t;

/**
 * Structure contains accel config register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t xg_st :1; /*<!Element contains X axis self test perform bit */
	uint8_t yg_st :1; /*<!Element contains Y axis self test perform bit */
	uint8_t zg_st :1; /*<!Element contains z axis self test perform bit */
	uint8_t afs_sel :2; /*<!Element contains full scale bits ( ex: MPU6050_ACCEL_FS_2G) */
	uint8_t not_used_01 :3; /*<!Element contains 3 reserved bits */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t not_used_01 :3;
	uint8_t afs_sel :2;
	uint8_t zg_st :1;
	uint8_t yg_st :1;
	uint8_t xg_st :1;
#endif
} mpu6050_accel_config_t;

/**
 * FIFO enable register location.
 */
#define MPU6050_FIFO_EN (0x23)

/**
 * Structure contains accel config register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t temp_fifo_en :1; /*< !Element contains temperature fifo enable bit */
	uint8_t xg_fifo_en :1; /*<! Element contains gyro X axis fifo enable bit */
	uint8_t yg_fifo_en :1; /*<! Element contains gyro Y axis fifo enable bit */
	uint8_t zg_fifo_en :1; /*<! Element contains gyro Z axis fifo enable bit */
	uint8_t accel_fifo_en :1; /*<! Element contains accelerometer fifo enable bit */
	uint8_t slv2_fifo_en :1; /*<! Element contains external sensor slave 2 fifo enable bit */
	uint8_t slv1_fifo_en :1; /*<! Element contains external sensor slave 1 fifo enable bit */
	uint8_t slv0_fifo_en :1; /*<! Element contains external sensor slave 0 fifo enable bit */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t slv0_fifo_en :1;
	uint8_t slv1_fifo_en :1;
	uint8_t slv2_fifo_en :1;
	uint8_t accel_fifo_en :1;
	uint8_t zg_fifo_en :1;
	uint8_t yg_fifo_en :1;
	uint8_t xg_fifo_en :1;
	uint8_t temp_fifo_en :1;
#endif
} mpu6050_fifo_enable_t;

/**
 * Interrupt pin config register location.
 */
#define MPU6050_INT_PIN_CFG (0x37)

/**
 * Structure contains interrupt pin config register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t int_level :1; /*< !Element contains interrupt active level selection bit 0=> active high, 1=> active low */
	uint8_t int_open :1; /*< !Element contains interrupt open drain selection bit 0=> push-pull, 1=> open drain */
	uint8_t latch_en :1; /*< !Element contains interrupt latching enable bit 0=> high for 50uS, 1=> high until clear */
	uint8_t int_rd_clear :1; /*< !Element contains interrupt status clear bit 0=> only cleared by reading status 1=> cleared on any read*/
	uint8_t fsync_int_level :1; /*< !Element contains frame sync logic level selection bit 0=> active high, 1=> active low */
	uint8_t fsync_int_en :1; /*< !Element contains frame sync enable bit*/
	uint8_t i2c_bypass_en :1; /*< !Element contains i2c bypass enable bit 0=> master can directly auxiliary i2c bus*/
	uint8_t not_used_01 :1; /*< !Element contains 1 reserved bit*/
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t not_used_01 :1;
	uint8_t i2c_bypass_en :1;
	uint8_t fsync_int_en :1;
	uint8_t fsync_int_level :1;
	uint8_t int_rd_clear :1;
	uint8_t latch_en :1;
	uint8_t int_open :1;
	uint8_t int_level :1;
#endif
} mpu6050_int_pin_cfg_t;

/**
 * Interrupt enable register location.
 */
#define MPU6050_INT_ENABLE (0x38)

/**
 * Structure contains interrupt enable register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t not_used_01 :3; /*< !Element contains 3 reserved bits */
	uint8_t fifo_oflow_en :1; /*< !Element contains fifo overflow interrupt enable bit */
	uint8_t i2c_mst_int_en :1; /*< !Element contains i2c master interrupt enable bit */
	uint8_t not_used_02 :2; /*< !Element contains 2 reserved bits */
	uint8_t data_rdy_en :1; /*< !Element contains data ready interrupt enable bit */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t data_rdy_en :1;
	uint8_t not_used_02 :2;
	uint8_t i2c_mst_int_en :1;
	uint8_t fifo_oflow_en :1;
	uint8_t not_used_01 :3;
#endif
} mpu6050_int_enable_t;

/**
 * Interrupt status register location.
 */
#define MPU6050_INT_STATUS (0x3A)

/**
 * Structure contains interrupt status register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t not_used_01 :3; /*< !Element contains 3 reserved bits */
	uint8_t fifo_oflow_int :1; /*< !Element contains fifo overflow status bit */
	uint8_t i2c_mst_int_int :1; /*< !Element contains i2c master status bit */
	uint8_t not_used_02 :2; /*< !Element contains 2 reserved bits */
	uint8_t data_rdy_int :1;  /*< !Element contains data ready status bit */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t data_rdy_int :1;
	uint8_t not_used_02 :2;
	uint8_t i2c_mst_int_int :1;
	uint8_t fifo_oflow_int :1;
	uint8_t not_used_01 :3;
#endif
} mpu6050_int_status_t;

/**
 * Signal path reset register location.
 */
#define MPU6050_SIGNAL_PATH_RESET (0x68)

/**
 * Structure contains signal path reset register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t not_used_01 :5; /*< !Element contains 5 reserved bits */
	uint8_t gyro_reset :1; /*< !Element contains gyroscope reset bit */
	uint8_t accel_reset :1; /*< !Element contains accelerometer reset bit */
	uint8_t temp_reset :1; /*< !Element contains temperature sensor reset bit */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t temp_reset :1;
	uint8_t accel_reset :1;
	uint8_t gyro_reset :1;
	uint8_t not_used_01 :5;
#endif
} mpu6050_signal_path_reset_t;

/**
 * User control register location.
 */
#define MPU6050_USER_CTRL (0x6A)

/**
 * Structure contains user control register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t not_used_01 :1; /*< !Element contains 1 reserved bit */
	uint8_t fifo_en :1; /*< !Element contains fifo enable bit */
	uint8_t i2c_mst_en :1; /*< !Element contains i2c master enable bit */
	uint8_t i2c_if_dis :1; /*< !Element contains i2c interface disable bit (1=> enable spi interface and disables i2c) */
	uint8_t not_used_02 :1; /*< !Element contains 1 reserved bit */
	uint8_t fifo_reset :1; /*< !Element contains fifo reset bit i.g fifo_en bit should be 0 to rest fifo buffer */
	uint8_t i2c_mst_reset :1; /*< !Element contains i2c master reset bit */
	uint8_t sig_cond_reset :1; /*< !Element contains signal conditioning reset bit */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t sig_cond_reset :1;
	uint8_t i2c_mst_reset :1;
	uint8_t fifo_reset :1;
	uint8_t not_used_02 :1;
	uint8_t i2c_if_dis :1;
	uint8_t i2c_mst_en :1;
	uint8_t fifo_en :1;
	uint8_t not_used_01 :1;
#endif
} mpu6050_user_ctrl_t;

/**
 * Power management 1 register location.
 */
#define MPU6050_PWR_MGMT_1 (0x6B)

/**
 *	Enumeration represents all clock source options.
 */
typedef enum {
	MPU6050_CLK_SRC_INTENAL_8MHZ = 0, /*<! Internal 8MHz oscillator */
	MPU6050_CLK_SRC_PLL_GYROX = 1, /*<! PLL with X axis gyroscope reference */
	MPU6050_CLK_SRC_PLL_GYROY = 2, /*<! PLL with Y axis gyroscope reference */
	MPU6050_CLK_SRC_PLL_GYROZ = 3, /*<! PLL with Z axis gyroscope reference */
	MPU6050_CLK_SRC_PLL_EXTERNAL_32KHZ = 4, /*<! PLL with external 32.768kHz reference */
	MPU6050_CLK_SRC_PLL_EXTERNAL_19MHZ = 5, /*<! PLL with external 19.2MHz reference */
	MPU6050_CLK_STOP = 7, /*<! Stops the clock and keeps the timing generator in reset */
} mpu6050_clk_src_t;

/**
 * Structure contains power management 1 register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t device_reset :1; /*< !Element contains device reset bit */
	uint8_t sleep :1; /*< !Element contains sleep enable bit  */
	uint8_t cycle :1; /*< !Element contains cycle bit i.g 1=> periodical wake up from sleep to sample data */
	uint8_t not_used_01:1; /*< !Element contains 1 reserved bit */
	uint8_t temp_dis :1; /*< !Element contains temperature sensor disable  bit */
	uint8_t clksel :3;  /*< !Element contains clock source selection  bit (ex: MPU6050_CLK_SRC_INTENAL_8MHZ) */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t clksel :3;
	uint8_t temp_dis :1;
	uint8_t not_used_01 :1;
	uint8_t cycle :1;
	uint8_t sleep :1;
	uint8_t device_reset :1;
#endif
} mpu6050_pwr_mgmt_1_t;

/**
 * Power management 2 register location.
 */
#define MPU6050_PWR_MGMT_2 (0x6C)

/**
 *	Enumeration represents all low power wake up frequency options.
 */
typedef enum {
	MPU6050_LP_WAKEUP_1HZ = 0, /*<! Wake up frequency 1.26Hz */
	MPU6050_LP_WAKEUP_5HZ = 1, /*<! Wake up frequency 5Hz */
	MPU6050_LP_WAKEUP_20HZ = 2, /*<! Wake up frequency 20Hz */
	MPU6050_LP_WAKEUP_40HZ = 3, /*<! Wake up frequency 40Hz */
} mpu6050_lp_wakeup_t;

/**
 * Structure contains power management 2 register bits.
 */
typedef struct {
#if DRV_BYTE_ORDER == DRV_BIG_ENDIAN
	uint8_t lp_wake_ctrl :2; /*< !Element contains low power wake up control bit (ex : MPU6050_LP_WAKEUP_1HZ) */
	uint8_t stby_xa :1; /*< !Element contains accelerometer X axis standby mode bit */
	uint8_t stby_ya :1; /*< !Element contains accelerometer Y axis standby mode bit */
	uint8_t stby_za :1; /*< !Element contains accelerometer Z axis standby mode bit */
	uint8_t stby_xg :1; /*< !Element contains gyroscope X axis standby mode bit */
	uint8_t stby_yg :1; /*< !Element contains gyroscope Y axis standby mode bit */
	uint8_t stby_zg :1; /*< !Element contains gyroscope Z axis standby mode bit */
#elif DRV_BYTE_ORDER == DRV_LITTLE_ENDIAN
	uint8_t stby_zg :1;
	uint8_t stby_yg :1;
	uint8_t stby_xg :1;
	uint8_t stby_za :1;
	uint8_t stby_ya :1;
	uint8_t stby_xa :1;
	uint8_t lp_wake_ctrl :2;
#endif
} mpu6050_pwr_mgmt_2_t;


#endif //__MPU6050_REG_H__
