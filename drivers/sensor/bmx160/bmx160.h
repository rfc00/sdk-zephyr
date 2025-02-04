/* Bosch BMX160 inertial measurement unit header
 *
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_BMX160_BMX160_H_
#define ZEPHYR_DRIVERS_SENSOR_BMX160_BMX160_H_

#include <drivers/i2c.h>
#include <drivers/gpio.h>
#include <drivers/sensor.h>
#include <drivers/spi.h>
#include <sys/util.h>

/* registers */
#define BMX160_REG_CHIPID		0x00
#define BMX160_REG_ERR			0x02
#define BMX160_REG_PMU_STATUS		0x03
#define BMX160_REG_DATA_MAG_X		0x04
#define BMX160_REG_DATA_MAG_Y		0x06
#define BMX160_REG_DATA_MAG_Z		0x08
#define BMX160_REG_DATA_RHALL		0x0A
#define BMX160_REG_DATA_GYR_X		0x0C
#define BMX160_REG_DATA_GYR_Y		0x0E
#define BMX160_REG_DATA_GYR_Z		0x10
#define BMX160_REG_DATA_ACC_X		0x12
#define BMX160_REG_DATA_ACC_Y		0x14
#define BMX160_REG_DATA_ACC_Z		0x16
#define BMX160_REG_SENSORTIME0		0x18
#define BMX160_REG_SENSORTIME1		0x19
#define BMX160_REG_SENSORTIME2		0x1A
#define BMX160_REG_STATUS		0x1B
#define BMX160_REG_INT_STATUS0		0x1C
#define BMX160_REG_INT_STATUS1		0x1D
#define BMX160_REG_INT_STATUS2		0x1E
#define BMX160_REG_INT_STATUS3		0x1F
#define BMX160_REG_TEMPERATURE0		0x20
#define BMX160_REG_TEMPERATURE1		0x21
#define BMX160_REG_FIFO_LENGTH0		0x22
#define BMX160_REG_FIFO_LENGTH1		0x23
#define BMX160_REG_FIFO_DATA		0x24
#define BMX160_REG_ACC_CONF		0x40
#define BMX160_REG_ACC_RANGE		0x41
#define BMX160_REG_GYR_CONF		0x42
#define BMX160_REG_GYR_RANGE		0x43
#define BMX160_REG_MAG_CONF		0x44
#define BMX160_REG_FIFO_DOWNS		0x45
#define BMX160_REG_FIFO_CONFIG0		0x46
#define BMX160_REG_FIFO_CONFIG1		0x47
#define BMX160_REG_MAG_IF0		0x4B
#define BMX160_REG_MAG_IF1		0x4C
#define BMX160_REG_MAG_IF2		0x4D
#define BMX160_REG_MAG_IF3		0x4E
#define BMX160_REG_MAG_IF4		0x4F
#define BMX160_REG_INT_EN0		0x50
#define BMX160_REG_INT_EN1		0x51
#define BMX160_REG_INT_EN2		0x52
#define BMX160_REG_INT_OUT_CTRL		0x53
#define BMX160_REG_INT_LATCH		0x54
#define BMX160_REG_INT_MAP0		0x55
#define BMX160_REG_INT_MAP1		0x56
#define BMX160_REG_INT_MAP2		0x57
#define BMX160_REG_INT_DATA0		0x58
#define BMX160_REG_INT_DATA1		0x59
#define BMX160_REG_INT_LOWHIGH0		0x5A
#define BMX160_REG_INT_LOWHIGH1		0x5B
#define BMX160_REG_INT_LOWHIGH2		0x5C
#define BMX160_REG_INT_LOWHIGH3		0x5D
#define BMX160_REG_INT_LOWHIGH4		0x5E
#define BMX160_REG_INT_MOTION0		0x5F
#define BMX160_REG_INT_MOTION1		0x60
#define BMX160_REG_INT_MOTION2		0x61
#define BMX160_REG_INT_MOTION3		0x62
#define BMX160_REG_INT_TAP0		0x63
#define BMX160_REG_INT_TAP1		0x64
#define BMX160_REG_INT_ORIENT0		0x65
#define BMX160_REG_INT_ORIENT1		0x66
#define BMX160_REG_INT_FLAT0		0x67
#define BMX160_REG_INT_FLAT1		0x68
#define BMX160_REG_FOC_CONF		0x69
#define BMX160_REG_CONF			0x6A
#define BMX160_REG_IF_CONF		0x6B
#define BMX160_REG_PMU_TRIGGER		0x6C
#define BMX160_REG_SELF_TEST		0x6D
#define BMX160_REG_NV_CONF		0x70
#define BMX160_REG_OFFSET_ACC_X		0x71
#define BMX160_REG_OFFSET_ACC_Y		0x72
#define BMX160_REG_OFFSET_ACC_Z		0x73
#define BMX160_REG_OFFSET_GYR_X		0x74
#define BMX160_REG_OFFSET_GYR_Y		0x75
#define BMX160_REG_OFFSET_GYR_Z		0x76
#define BMX160_REG_OFFSET_EN		0x77
#define BMX160_REG_STEP_CNT0		0x78
#define BMX160_REG_STEP_CNT1		0x79
#define BMX160_REG_STEP_CONF0		0x7A
#define BMX160_REG_STEP_CONF1		0x7B
#define BMX160_REG_CMD			0x7E

/* This is not a real register; reading it activates SPI on the BMX160 */
#define BMX160_SPI_START		0x7F

#define BMX160_REG_COUNT		0x80

/* Indicates a read operation; bit 7 is clear on write s*/
#define BMX160_REG_READ			BIT(7)
#define BMX160_REG_MASK			0x7f

/* bitfields */

/* BMX160_REG_ERR */
#define BMX160_ERR_FATAL		BIT(0)
#define BMX160_ERR_CODE			BIT(1)
#define BMX160_ERR_CODE_MASK		(0xf << 1)
#define BMX160_ERR_I2C_FAIL		BIT(5)
#define BMX160_ERR_DROP_CMD		BIT(6)
#define BMX160_ERR_MAG_DRDY		BIT(7)

/* BMX160_REG_PMU_STATUS */
#define BMX160_PMU_STATUS_MAG_MASK	0x3
#define BMX160_PMU_STATUS_MAG_POS	0
#define BMX160_PMU_STATUS_GYR_POS	2
#define BMX160_PMU_STATUS_GYR_MASK	(0x3 << 2)
#define BMX160_PMU_STATUS_ACC_POS	4
#define BMX160_PMU_STATUS_ACC_MASK	(0x3 << 4)

#define BMX160_PMU_SUSPEND		0
#define BMX160_PMU_NORMAL		1
#define BMX160_PMU_LOW_POWER		2
#define BMX160_PMU_FAST_START		3

/* BMX160_REG_STATUS */
#define BMX160_STATUS_GYR_SELFTEST	BIT(1)
#define BMX160_STATUS_MAG_MAN_OP	BIT(2)
#define BMX160_STATUS_FOC_RDY		BIT(3)
#define BMX160_STATUS_NVM_RDY		BIT(4)
#define BMX160_STATUS_MAG_DRDY		BIT(5)
#define BMX160_STATUS_GYR_DRDY		BIT(6)
#define BMX160_STATUS_ACC_DRDY		BIT(7)

/* BMX160_REG_INT_STATUS0 */
#define BMX160_INT_STATUS0_STEP		BIT(0)
#define BMX160_INT_STATUS0_SIGMOT	BIT(1)
#define BMX160_INT_STATUS0_ANYM		BIT(2)
#define BMX160_INT_STATUS0_PMU_TRIG	BIT(3)
#define BMX160_INT_STATUS0_D_TAP	BIT(4)
#define BMX160_INT_STATUS0_S_TAP	BIT(5)
#define BMX160_INT_STATUS0_ORIENT	BIT(6)
#define BMX160_INT_STATUS0_FLAT		BIT(7)

/* BMX160_REG_INT_STATUS1 */
#define BMX160_INT_STATUS1_HIGHG	BIT(2)
#define BMX160_INT_STATUS1_LOWG		BIT(3)
#define BMX160_INT_STATUS1_DRDY		BIT(4)
#define BMX160_INT_STATUS1_FFULL	BIT(5)
#define BMX160_INT_STATUS1_FWM		BIT(6)
#define BMX160_INT_STATUS1_NOMO		BIT(7)

/* BMX160_REG_INT_STATUS2 */
#define BMX160_INT_STATUS2_ANYM_FIRST_X BIT(0)
#define BMX160_INT_STATUS2_ANYM_FIRST_Y BIT(1)
#define BMX160_INT_STATUS2_ANYM_FIRST_Z BIT(2)
#define BMX160_INT_STATUS2_ANYM_SIGN	BIT(3)
#define BMX160_INT_STATUS2_TAP_FIRST_X	BIT(4)
#define BMX160_INT_STATUS2_TAP_FIRST_Y	BIT(5)
#define BMX160_INT_STATUS2_TAP_FIRST_Z	BIT(6)
#define BMX160_INT_STATUS2_TAP_SIGN	BIT(7)

/* BMX160_REG_INT_STATUS3 */
#define BMX160_INT_STATUS3_HIGH_FIRST_X BIT(0)
#define BMX160_INT_STATUS3_HIGH_FIRST_Y BIT(1)
#define BMX160_INT_STATUS3_HIGH_FIRST_Z BIT(2)
#define BMX160_INT_STATUS3_HIGH_SIGN	BIT(3)
#define BMX160_INT_STATUS3_ORIENT_1_0	BIT(4)
#define BMX160_INT_STATUS3_ORIENT_2	BIT(6)
#define BMX160_INT_STATUS3_FLAT		BIT(7)

/* BMX160_REG_ACC_CONF */
#define BMX160_ACC_CONF_ODR_POS		0
#define BMX160_ACC_CONF_ODR_MASK	0xF
#define BMX160_ACC_CONF_BWP_POS		4
#define BMX160_ACC_CONF_BWP_MASK	(0x7 << 4)
#define BMX160_ACC_CONF_US_POS		7
#define BMX160_ACC_CONF_US_MASK		BIT(7)

/* BMX160_REG_GYRO_CONF */
#define BMX160_GYR_CONF_ODR_POS	0
#define BMX160_GYR_CONF_ODR_MASK	0xF
#define BMX160_GYR_CONF_BWP_POS	4
#define BMX160_GYR_CONF_BWP_MASK	(0x3 << 4)

/* BMX160_REG_OFFSET_EN */
#define BMX160_GYR_OFS_EN_POS		7
#define BMX160_ACC_OFS_EN_POS		6
#define BMX160_GYR_MSB_OFS_Z_POS	4
#define BMX160_GYR_MSB_OFS_Z_MASK	(BIT(4) | BIT(5))
#define BMX160_GYR_MSB_OFS_Y_POS	2
#define BMX160_GYR_MSB_OFS_Y_MASK	(BIT(2) | BIT(3))
#define BMX160_GYR_MSB_OFS_X_POS	0
#define BMX160_GYR_MSB_OFS_X_MASK	(BIT(0) | BIT(1))

/* BMX160_REG_CMD */
#define BMX160_CMD_START_FOC		3
#define BMX160_CMD_PMU_ACC		0x10
#define BMX160_CMD_PMU_GYR		0x14
#define BMX160_CMD_PMU_MAG		0x18
#define BMX160_CMD_SOFT_RESET		0xB6

#define BMX160_CMD_PMU_BIT		0x10
#define BMX160_CMD_PMU_MASK		0x0c
#define BMX160_CMD_PMU_SHIFT		2
#define BMX160_CMD_PMU_VAL_MASK		0x3

/* BMX160_REG_FOC_CONF */
#define BMX160_FOC_ACC_Z_POS		0
#define BMX160_FOC_ACC_Y_POS		2
#define BMX160_FOC_ACC_X_POS		4
#define BMX160_FOC_GYR_EN_POS		6

/* BMX160_REG_INT_MOTION0 */
#define BMX160_ANYM_DUR_POS		0
#define BMX160_ANYM_DUR_MASK		0x3

/* BMX160_REG_INT_EN0 */
#define BMX160_INT_FLAT_EN		BIT(7)
#define BMX160_INT_ORIENT_EN		BIT(6)
#define BMX160_INT_S_TAP_EN		BIT(5)
#define BMX160_INT_D_TAP_EN		BIT(4)
#define BMX160_INT_ANYM_Z_EN		BIT(2)
#define BMX160_INT_ANYM_Y_EN		BIT(1)
#define BMX160_INT_ANYM_X_EN		BIT(0)
#define BMX160_INT_ANYM_MASK		(BIT(0) | BIT(1) | BIT(2))

/* BMX160_REG_INT_EN1 */
#define BMX160_INT_FWM_EN		BIT(6)
#define BMX160_INT_FFULL_EN		BIT(5)
#define BMX160_INT_DRDY_EN		BIT(4)
#define BMX160_INT_LOWG_EN		BIT(3)
#define BMX160_INT_HIGHG_Z_EN		BIT(2)
#define BMX160_INT_HIGHG_Y_EN		BIT(1)
#define BMX160_INT_HIGHG_X_EN		BIT(0)
#define BMX160_INT_HIGHG_MASK		(BIT(0) | BIT(1) | BIT(2))

/* BMX160_REG_INT_EN2 */
#define BMX160_INT_STEP_DET_EN		BIT(3)
#define BMX160_INT_STEP_NOMO_Z_EN	BIT(2)
#define BMX160_INT_STEP_NOMO_Y_EN	BIT(1)
#define BMX160_INT_STEP_NOMO_X_EN	BIT(0)
#define BMX160_INT_STEP_NOMO_MASK	(BIT(0) | BIT(1) | BIT(2))

/* BMX160_REG_INT_OUT_CTRL */
#define BMX160_INT2_OUT_EN		BIT(7)
#define BMX160_INT2_OD			BIT(6)
#define BMX160_INT2_LVL			BIT(5)
#define BMX160_INT2_EDGE_CTRL		BIT(4)
#define BMX160_INT1_OUT_EN		BIT(3)
#define BMX160_INT1_OD			BIT(2)
#define BMX160_INT1_LVL			BIT(1)
#define BMX160_INT1_EDGE_CTRL		BIT(0)

/* other */
#define BMX160_CHIP_ID			0xD8
#define BMX160_TEMP_OFFSET		23

/* allowed ODR values */
enum bmx160_odr {
	BMX160_ODR_25_32 = 1,
	BMX160_ODR_25_16,
	BMX160_ODR_25_8,
	BMX160_ODR_25_4,
	BMX160_ODR_25_2,
	BMX160_ODR_25,
	BMX160_ODR_50,
	BMX160_ODR_100,
	BMX160_ODR_200,
	BMX160_ODR_400,
	BMX160_ODR_800,
	BMX160_ODR_1600,
	BMX160_ODR_3200,
};

/* Range values for accelerometer */
#define BMX160_ACC_RANGE_2G		0x3
#define BMX160_ACC_RANGE_4G		0x5
#define BMX160_ACC_RANGE_8G		0x8
#define BMX160_ACC_RANGE_16G		0xC

/* Range values for gyro */
#define BMX160_GYR_RANGE_2000DPS	0
#define BMX160_GYR_RANGE_1000DPS	1
#define BMX160_GYR_RANGE_500DPS		2
#define BMX160_GYR_RANGE_250DPS		3
#define BMX160_GYR_RANGE_125DPS		4

#define BMX160_ACC_SCALE(range_g)	((2 * range_g * SENSOR_G) / 65536LL)
#define BMX160_GYR_SCALE(range_dps)\
				((2 * range_dps * SENSOR_PI) / 180LL / 65536LL)

/* default settings, based on menuconfig options */

/* make sure at least one sensor is active */
#if defined(CONFIG_BMX160_ACCEL_PMU_SUSPEND) &&\
		defined(CONFIG_BMX160_GYRO_PMU_SUSPEND)
#error "Error: You need to activate at least one sensor!"
#endif

#if defined(CONFIG_BMX160_ACCEL_PMU_RUNTIME) ||\
		defined(CONFIG_BMX160_ACCEL_PMU_NORMAL)
#	define BMX160_DEFAULT_PMU_ACC		BMX160_PMU_NORMAL
#elif defined(CONFIG_BMX160_ACCEL_PMU_SUSPEND)
#	define BMX160_DEFAULT_PMU_ACC		BMX160_PMU_SUSPEND
#else
#	define BMX160_DEFAULT_PMU_ACC		BMX160_PMU_LOW_POWER
#endif

#if defined(CONFIG_BMX160_GYRO_PMU_RUNTIME) ||\
		defined(CONFIG_BMX160_GYRO_PMU_NORMAL)
#	define BMX160_DEFAULT_PMU_GYR		BMX160_PMU_NORMAL
#elif defined(CONFIG_BMX160_GYRO_PMU_SUSPEND)
#	define BMX160_DEFAULT_PMU_GYR		BMX160_PMU_SUSPEND
#else
#	define BMX160_DEFAULT_PMU_GYR		BMX160_PMU_FAST_START
#endif

#if defined(CONFIG_BMX160_ACCEL_RANGE_RUNTIME) ||\
		defined(CONFIG_BMX160_ACCEL_RANGE_2G)
#	define BMX160_DEFAULT_RANGE_ACC		BMX160_ACC_RANGE_2G
#elif defined(CONFIG_BMX160_ACCEL_RANGE_4G)
#	define BMX160_DEFAULT_RANGE_ACC		BMX160_ACC_RANGE_4G
#elif defined(CONFIG_BMX160_ACCEL_RANGE_8G)
#	define BMX160_DEFAULT_RANGE_ACC		BMX160_ACC_RANGE_8G
#else
#	define BMX160_DEFAULT_RANGE_ACC		BMX160_ACC_RANGE_16G
#endif

#if defined(CONFIG_BMX160_GYRO_RANGE_RUNTIME) ||\
		defined(CONFIG_BMX160_GYRO_RANGE_2000DPS)
#	define BMX160_DEFAULT_RANGE_GYR		BMX160_GYR_RANGE_2000DPS
#elif defined(CONFIG_BMX160_GYRO_RANGE_1000DPS)
#	define BMX160_DEFAULT_RANGE_GYR		BMX160_GYR_RANGE_1000DPS
#elif defined(CONFIG_BMX160_GYRO_RANGE_500DPS)
#	define BMX160_DEFAULT_RANGE_GYR		BMX160_GYR_RANGE_500DPS
#elif defined(CONFIG_BMX160_GYRO_RANGE_250DPS)
#	define BMX160_DEFAULT_RANGE_GYR		BMX160_GYR_RANGE_250DPS
#else
#	define BMX160_DEFAULT_RANGE_GYR		BMX160_GYR_RANGE_125DPS
#endif

#if defined(CONFIG_BMX160_ACCEL_ODR_RUNTIME) ||\
		defined(CONFIG_BMX160_ACCEL_ODR_100)
#	define BMX160_DEFAULT_ODR_ACC		8
#elif defined(CONFIG_BMX160_ACCEL_ODR_25_32)
#	define BMX160_DEFAULT_ODR_ACC		1
#elif defined(CONFIG_BMX160_ACCEL_ODR_25_16)
#	define BMX160_DEFAULT_ODR_ACC		2
#elif defined(CONFIG_BMX160_ACCEL_ODR_25_8)
#	define BMX160_DEFAULT_ODR_ACC		3
#elif defined(CONFIG_BMX160_ACCEL_ODR_25_4)
#	define BMX160_DEFAULT_ODR_ACC		4
#elif defined(CONFIG_BMX160_ACCEL_ODR_25_2)
#	define BMX160_DEFAULT_ODR_ACC		5
#elif defined(CONFIG_BMX160_ACCEL_ODR_25)
#	define BMX160_DEFAULT_ODR_ACC		6
#elif defined(CONFIG_BMX160_ACCEL_ODR_50)
#	define BMX160_DEFAULT_ODR_ACC		7
#elif defined(CONFIG_BMX160_ACCEL_ODR_200)
#	define BMX160_DEFAULT_ODR_ACC		9
#elif defined(CONFIG_BMX160_ACCEL_ODR_400)
#	define BMX160_DEFAULT_ODR_ACC		10
#elif defined(CONFIG_BMX160_ACCEL_ODR_800)
#	define BMX160_DEFAULT_ODR_ACC		11
#else
#	define BMX160_DEFAULT_ODR_ACC		12
#endif

#if defined(CONFIG_BMX160_GYRO_ODR_RUNTIME) ||\
		defined(CONFIG_BMX160_GYRO_ODR_100)
#	define BMX160_DEFAULT_ODR_GYR		8
#elif defined(CONFIG_BMX160_GYRO_ODR_25)
#	define BMX160_DEFAULT_ODR_GYR		6
#elif defined(CONFIG_BMX160_GYRO_ODR_50)
#	define BMX160_DEFAULT_ODR_GYR		7
#elif defined(CONFIG_BMX160_GYRO_ODR_200)
#	define BMX160_DEFAULT_ODR_GYR		9
#elif defined(CONFIG_BMX160_GYRO_ODR_400)
#	define BMX160_DEFAULT_ODR_GYR		10
#elif defined(CONFIG_BMX160_GYRO_ODR_800)
#	define BMX160_DEFAULT_ODR_GYR		11
#elif defined(CONFIG_BMX160_GYRO_ODR_1600)
#	define BMX160_DEFAULT_ODR_GYR		12
#else
#	define BMX160_DEFAULT_ODR_GYR		13
#endif

/* end of default settings */

struct bmx160_range {
	uint16_t range;
	uint8_t reg_val;
};

#define BMX160_BUS_SPI		DT_ANY_INST_ON_BUS_STATUS_OKAY(spi)
#define BMX160_BUS_I2C		DT_ANY_INST_ON_BUS_STATUS_OKAY(i2c)

union bmx160_bus {
#if BMX160_BUS_SPI
	struct spi_dt_spec spi;
#endif
//#if BMX160_BUS_I2C
	struct i2c_dt_spec i2c;
//#endif
};

typedef bool (*bmx160_bus_ready_fn)(const struct device *dev);
typedef int (*bmx160_reg_read_fn)(const struct device *dev,
				  uint8_t reg_addr, void *data, uint8_t len);
typedef int (*bmx160_reg_write_fn)(const struct device *dev,
				   uint8_t reg_addr, void *data, uint8_t len);

struct bmx160_bus_io {
	bmx160_bus_ready_fn ready;
	bmx160_reg_read_fn read;
	bmx160_reg_write_fn write;
};

struct bmx160_cfg {
	union bmx160_bus bus;
	const struct bmx160_bus_io *bus_io;
#if defined(CONFIG_BMX160_TRIGGER)
	struct gpio_dt_spec interrupt;
#endif
};

union bmx160_pmu_status {
	uint8_t raw;
	struct {
		uint8_t mag : 2;
		uint8_t gyr : 2;
		uint8_t acc : 2;
		uint8_t res : 2;
	};
};

#define BMX160_AXES			3

#if !defined(CONFIG_BMX160_GYRO_PMU_SUSPEND) && \
		!defined(CONFIG_BMX160_ACCEL_PMU_SUSPEND)
#	define BMX160_SAMPLE_SIZE	(2 * BMX160_AXES * sizeof(uint16_t))
#else
#	define BMX160_SAMPLE_SIZE	(BMX160_AXES * sizeof(uint16_t))
#endif

#if defined(CONFIG_BMX160_GYRO_PMU_SUSPEND)
#	define BMX160_SAMPLE_BURST_READ_ADDR	BMX160_REG_DATA_ACC_X
#	define BMX160_DATA_READY_BIT_MASK	(1 << 7)
#else
#	define BMX160_SAMPLE_BURST_READ_ADDR	BMX160_REG_DATA_GYR_X
#	define BMX160_DATA_READY_BIT_MASK	(1 << 6)
#endif

#define BMX160_BUF_SIZE			(BMX160_SAMPLE_SIZE)

/* Each sample has X, Y and Z */
union bmx160_sample {
	uint8_t raw[BMX160_BUF_SIZE];
	struct {
#if !defined(CONFIG_BMX160_GYRO_PMU_SUSPEND)
		uint16_t gyr[BMX160_AXES];
#endif
#if !defined(CONFIG_BMX160_ACCEL_PMU_SUSPEND)
		uint16_t acc[BMX160_AXES];
#endif
	} __packed;
};

struct bmx160_scale {
	uint16_t acc; /* micro m/s^2/lsb */
	uint16_t gyr; /* micro radians/s/lsb */
};

struct bmx160_data {
	const struct device *bus;
#if defined(CONFIG_BMX160_TRIGGER)
	const struct device *dev;
	const struct device *gpio;
	struct gpio_callback gpio_cb;
#endif
	union bmx160_pmu_status pmu_sts;
	union bmx160_sample sample;
	struct bmx160_scale scale;

#ifdef CONFIG_BMX160_TRIGGER_OWN_THREAD
	struct k_sem sem;
#endif

#ifdef CONFIG_BMX160_TRIGGER_GLOBAL_THREAD
	struct k_work work;
#endif

#ifdef CONFIG_BMX160_TRIGGER
#if !defined(CONFIG_BMX160_ACCEL_PMU_SUSPEND)
	sensor_trigger_handler_t handler_drdy_acc;
	sensor_trigger_handler_t handler_anymotion;
#endif
#if !defined(CONFIG_BMX160_GYRO_PMU_SUSPEND)
	sensor_trigger_handler_t handler_drdy_gyr;
#endif
#endif /* CONFIG_BMX160_TRIGGER */
};

static inline struct bmx160_data *to_data(const struct device *dev)
{
	return dev->data;
}

static inline const struct bmx160_cfg *to_config(const struct device *dev)
{
	return dev->config;
}

int bmx160_read(const struct device *dev, uint8_t reg_addr,
		void *data, uint8_t len);
int bmx160_byte_read(const struct device *dev, uint8_t reg_addr,
		     uint8_t *byte);
int bmx160_byte_write(const struct device *dev, uint8_t reg_addr,
		      uint8_t byte);
int bmx160_word_write(const struct device *dev, uint8_t reg_addr,
		      uint16_t word);
int bmx160_reg_field_update(const struct device *dev, uint8_t reg_addr,
			    uint8_t pos, uint8_t mask, uint8_t val);
static inline int bmx160_reg_update(const struct device *dev,
				    uint8_t reg_addr,
				    uint8_t mask, uint8_t val)
{
	return bmx160_reg_field_update(dev, reg_addr, 0, mask, val);
}
int bmx160_trigger_mode_init(const struct device *dev);
int bmx160_trigger_set(const struct device *dev,
		       const struct sensor_trigger *trig,
		       sensor_trigger_handler_t handler);
int bmx160_acc_slope_config(const struct device *dev,
			    enum sensor_attribute attr,
			    const struct sensor_value *val);
int32_t bmx160_acc_reg_val_to_range(uint8_t reg_val);
int32_t bmx160_gyr_reg_val_to_range(uint8_t reg_val);

#endif /* ZEPHYR_DRIVERS_SENSOR_BMX160_BMX160_H_ */
