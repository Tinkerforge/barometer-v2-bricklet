/* load-cell-v2-bricklet
 * Copyright (C) 2018 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * lps22hb.h: LPS22HB air pressure sensor driver
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef LPS22HB_H
#define LPS22HB_H

#include "bricklib2/hal/spi_fifo/spi_fifo.h"
#include "bricklib2/utility/moving_average.h"

#define CALIBRATION_PAGE 1
#define CALIBRATION_MAGIC 0x12345678
#define CALIBRATION_MAGIC_POS 0
#define CALIBRATION_OFFSET_POS 1

#define LPS22HB_REG_ADDR_INTERRUPT_CFG 0x0B
#define LPS22HB_REG_ADDR_THS_P_L 0x0C
#define LPS22HB_REG_ADDR_THS_P_H 0x0D
#define LPS22HB_REG_ADDR_WHO_AM_I 0x0F
#define LPS22HB_REG_ADDR_CTRL_REG1 0x10
#define LPS22HB_REG_ADDR_CTRL_REG2 0x11
#define LPS22HB_REG_ADDR_CTRL_REG3 0x12
#define LPS22HB_REG_ADDR_FIFO_CTRL 0x14
#define LPS22HB_REG_ADDR_REF_P_XL 0x15
#define LPS22HB_REG_ADDR_REF_P_L 0x16
#define LPS22HB_REG_ADDR_REF_P_H 0x17
#define LPS22HB_REG_ADDR_RPDS_L 0x18
#define LPS22HB_REG_ADDR_RPDS_H 0x19
#define LPS22HB_REG_ADDR_RES_CONF 0x1A
#define LPS22HB_REG_ADDR_INT_SOURCE 0x25
#define LPS22HB_REG_ADDR_FIFO_STATUS 0x26
#define LPS22HB_REG_ADDR_STATUS 0x27
#define LPS22HB_REG_ADDR_PRESS_OUT_XL 0x28
#define LPS22HB_REG_ADDR_PRESS_OUT_L 0x29
#define LPS22HB_REG_ADDR_PRESS_OUT_H 0x2A
#define LPS22HB_REG_ADDR_TEMP_OUT_L 0x2B
#define LPS22HB_REG_ADDR_TEMP_OUT_H 0x2C
#define LPS22HB_REG_ADDR_LPFP_RES 0x33

#define LPS22HB_REG_CTRL_REG1_MSK_SIM 0x01
#define LPS22HB_REG_CTRL_REG1_MSK_BDU 0x02
#define LPS22HB_REG_CTRL_REG1_MSK_LPFP_CFG 0x01
#define LPS22HB_REG_CTRL_REG1_MSK_EN_LPFP 0x01
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_PD_ONE_SHOT 0x00
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_1HZ 0x010
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_10HZ 0x020
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_25HZ 0x30
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_50HZ 0x40
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_75HZ 0x50

#define LPS22HB_REG_CTRL_REG2_MSK_ONE_SHOT 0x01
#define LPS22HB_REG_CTRL_REG2_MSK_SWRESET 0x04
#define LPS22HB_REG_CTRL_REG2_MSK_I2C_DIS 0x08
#define LPS22HB_REG_CTRL_REG2_MSK_IF_ADD_INC 0x10
#define LPS22HB_REG_CTRL_REG2_MSK_STOP_ON_FTH 0x20
#define LPS22HB_REG_CTRL_REG2_MSK_FIFO_EN 0x30
#define LPS22HB_REG_CTRL_REG2_MSK_BOOT 0x40

#define LPS22HB_REG_STATUS_MSK_P_DA 0x01
#define LPS22HB_REG_STATUS_MSK_T_DA 0x02
#define LPS22HB_REG_STATUS_MSK_P_OR 0x10
#define LPS22HB_REG_STATUS_MSK_T_OR 0x20

#define GET_READ_ADDR(addr) ((addr) + 0x80)
#define GET_WRITE_ADDR(addr) (addr)

#define DEFAULT_REFERENCE_AIR_PRESSURE 4150272 // 1013.25 mbar * 4096

typedef struct {
	int64_t air_pressure;
	int64_t factor;
} AltitudeFactor;

typedef enum {
	SM_INIT = 0,
	SM_CHECK_STATUS,
	SM_READ_SENSOR_DATA
} LPS22HBSM_t;

typedef struct {
	LPS22HBSM_t sm;
	SPIFifo spi_fifo;
	int32_t altitude;
	int32_t temperature;
	int32_t air_pressure;
	uint8_t spi_fifo_buf[16];
	int32_t reference_air_pressure;
	int32_t calibration_offset;
	MovingAverage moving_average_altitude;
	MovingAverage moving_average_temperature;
	MovingAverage moving_average_air_pressure;
} LPS22HB_t;

extern LPS22HB_t lps22hb;

void lps22hb_init(void);
void lps22hb_tick(void);

int32_t lps22hb_get_air_pressure(void);
int32_t lps22hb_get_altitude(void);
int32_t lps22hb_get_temperature(void);

void eeprom_read_calibration(void);
void eeprom_write_calibration(void);

#endif
