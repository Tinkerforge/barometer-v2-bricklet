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
#define CALIBRATION_MEASURED_AIR_PRESSURE_POS 1
#define CALIBRATION_ACTUAL_AIR_PRESSURE_POS 2

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

#define LPS22HB_REG_INTERRUPT_CFG_MSK_PHE       (1 << 0)
#define LPS22HB_REG_INTERRUPT_CFG_MSK_PLE       (1 << 1)
#define LPS22HB_REG_INTERRUPT_CFG_MSK_LIR       (1 << 2)
#define LPS22HB_REG_INTERRUPT_CFG_MSK_DIFF_EN   (1 << 3)
#define LPS22HB_REG_INTERRUPT_CFG_MSK_RESET_AZ  (1 << 4)
#define LPS22HB_REG_INTERRUPT_CFG_MSK_AUTOZERO  (1 << 5)
#define LPS22HB_REG_INTERRUPT_CFG_MSK_RESET_ARP (1 << 6)
#define LPS22HB_REG_INTERRUPT_CFG_MSK_AUTORIFP  (1 << 7)

#define LPS22HB_REG_CTRL_REG1_MSK_SIM           (1 << 0)
#define LPS22HB_REG_CTRL_REG1_MSK_BDU           (1 << 1)
#define LPS22HB_REG_CTRL_REG1_MSK_LPFP_CFG      (1 << 2)
#define LPS22HB_REG_CTRL_REG1_MSK_EN_LPFP       (1 << 3)
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_0         (1 << 4)
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_1         (1 << 5)
#define LPS22HB_REG_CTRL_REG1_MSK_ODR_2         (1 << 6)

#define LPS22HB_REG_CTRL_REG2_MSK_ONE_SHOT      (1 << 0)
#define LPS22HB_REG_CTRL_REG2_MSK_SWRESET       (1 << 2)
#define LPS22HB_REG_CTRL_REG2_MSK_I2C_DIS       (1 << 3)
#define LPS22HB_REG_CTRL_REG2_MSK_IF_ADD_INC    (1 << 4)
#define LPS22HB_REG_CTRL_REG2_MSK_STOP_ON_FTH   (1 << 5)
#define LPS22HB_REG_CTRL_REG2_MSK_FIFO_EN       (1 << 6)
#define LPS22HB_REG_CTRL_REG2_MSK_BOOT          (1 << 7)

#define LPS22HB_REG_CTRL_REG3_MSK_INT_S1        (1 << 0)
#define LPS22HB_REG_CTRL_REG3_MSK_INT_S2        (1 << 1)
#define LPS22HB_REG_CTRL_REG3_MSK_DRDY          (1 << 2)
#define LPS22HB_REG_CTRL_REG3_MSK_F_OVR         (1 << 3)
#define LPS22HB_REG_CTRL_REG3_MSK_F_FTH         (1 << 4)
#define LPS22HB_REG_CTRL_REG3_MSK_F_FSS5        (1 << 5)
#define LPS22HB_REG_CTRL_REG3_MSK_PP_OD         (1 << 6)
#define LPS22HB_REG_CTRL_REG3_MSK_INT_H_L       (1 << 7)

#define LPS22HB_REG_STATUS_MSK_P_DA 0x01
#define LPS22HB_REG_STATUS_MSK_T_DA 0x02
#define LPS22HB_REG_STATUS_MSK_P_OR 0x10
#define LPS22HB_REG_STATUS_MSK_T_OR 0x20

#define LPS22HB_GET_READ_ADDR(addr) ((addr) + 0x80)
#define LPS22HB_GET_WRITE_ADDR(addr) (addr)

#define DEFAULT_REFERENCE_AIR_PRESSURE 1013250 // (1013.25 * 1000) mbar

typedef struct {
	int32_t altitude; // mm
	int32_t temperature; // °C/100
	int32_t air_pressure; // mbar/1000
	int32_t reference_air_pressure; // mbar/1000
	int32_t measured_air_pressure; // mbar/1000
	int32_t actual_air_pressure; // mbar/1000
	uint8_t data_rate; // enum
	uint8_t air_pressure_low_pass_filter; // enum
	bool reconfigure;
	bool calibration_changed;
	SPIFifo spi_fifo;
	MovingAverage moving_average_air_pressure;
	MovingAverage moving_average_temperature;
} LPS22HB_t;

extern LPS22HB_t lps22hb;

void lps22hb_init(void);
void lps22hb_init_spi(void);
void lps22hb_tick(void);
void lps22hb_tick_task(void);

int32_t lps22hb_get_air_pressure(void);
int32_t lps22hb_get_altitude(void);
int32_t lps22hb_get_temperature(void);

void eeprom_read_calibration(void);
void eeprom_write_calibration(void);
int16_t lps22hb_get_cal_offset(int32_t measured_air_pressure,
                               int32_t actual_air_pressure);

#endif
