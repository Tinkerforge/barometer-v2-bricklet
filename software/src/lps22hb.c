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

#include "lps22hb.h"

#include "configs/config_lps22hb.h"

#include "bricklib2/logging/logging.h"
#include "bricklib2/bootloader/bootloader.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/os/coop_task.h"

LPS22HB_t lps22hb;
static CoopTask lps22hb_task;

typedef struct {
	int32_t air_pressure; // mbar/1000
	int32_t factor; // altitude difference in mm per mbar/1000 air pressure difference
} AltitudeFactor;

static const AltitudeFactor altitude_factors[] = {
	[0] = {1225005, 14},
	[1] = {1118311, 13},
	[2] = {1012049, 12},
	[3] = {909702, 11},
	[4] = {808871, 10},
	[5] = {710051, 9},
	[6] = {614001, 8},
	[7] = {520296, 7}
};

static const uint8_t odr_msk[] = {
	0, // Off
	LPS22HB_REG_CTRL_REG1_MSK_ODR_0, // 1Hz
	LPS22HB_REG_CTRL_REG1_MSK_ODR_1, // 10Hz
	LPS22HB_REG_CTRL_REG1_MSK_ODR_1 | LPS22HB_REG_CTRL_REG1_MSK_ODR_0, // 25Hz
	LPS22HB_REG_CTRL_REG1_MSK_ODR_2, // 50Hz
	LPS22HB_REG_CTRL_REG1_MSK_ODR_2 | LPS22HB_REG_CTRL_REG1_MSK_ODR_0, // 75Hz
};

static const uint8_t lpfp_msk[] = {
	0, // Off
	LPS22HB_REG_CTRL_REG1_MSK_EN_LPFP, // 1/9th
	LPS22HB_REG_CTRL_REG1_MSK_EN_LPFP | LPS22HB_REG_CTRL_REG1_MSK_LPFP_CFG, // 1/20th
};

void eeprom_write_calibration(void) {
	uint32_t page[EEPROM_PAGE_SIZE/sizeof(uint32_t)];

	page[CALIBRATION_MAGIC_POS] = CALIBRATION_MAGIC;
	page[CALIBRATION_MEASURED_AIR_PRESSURE_POS] = lps22hb.measured_air_pressure;
	page[CALIBRATION_ACTUAL_AIR_PRESSURE_POS] = lps22hb.actual_air_pressure;

	if(!bootloader_write_eeprom_page(CALIBRATION_PAGE, page)) {
		// TODO: Error handling?
		return;
	}
}

void eeprom_read_calibration(void) {
	uint32_t page[EEPROM_PAGE_SIZE/sizeof(uint32_t)];

	bootloader_read_eeprom_page(CALIBRATION_PAGE, page);

	// The magic number is not where it is supposed to be.
	// This is either our first startup or something went wrong.
	// We initialize the calibration data with sane default values.
	if(page[0] != CALIBRATION_MAGIC) {
		lps22hb.measured_air_pressure = 0;
		lps22hb.actual_air_pressure = 0;

		eeprom_write_calibration();

		return;
	}

	lps22hb.measured_air_pressure = page[CALIBRATION_MEASURED_AIR_PRESSURE_POS];
	lps22hb.actual_air_pressure = page[CALIBRATION_ACTUAL_AIR_PRESSURE_POS];
}

int16_t lps22hb_get_cal_offset(int32_t measured_air_pressure,
                               int32_t actual_air_pressure) {
	// Offset = 16 (16*256 = 4096) implies pressure difference of 1 mbar (4096 counts = 1 mbar)
	// Offset = (((measured - actual) / 0.1) * 1.6) / 1000
	return ((measured_air_pressure - actual_air_pressure) * 10 * 16) / 10000;
}

void lps22hb_init(void) {
	memset(&lps22hb, 0, sizeof(lps22hb));

	lps22hb.reference_air_pressure = DEFAULT_REFERENCE_AIR_PRESSURE;

	eeprom_read_calibration();

	lps22hb.data_rate = 4; // 50Hz
	lps22hb.air_pressure_low_pass_filter = 1; // 1/9th
	lps22hb.reconfigure = true;

	moving_average_init(&lps22hb.moving_average_air_pressure, 0, MOVING_AVERAGE_DEFAULT_LENGTH);
	moving_average_init(&lps22hb.moving_average_temperature, 0, MOVING_AVERAGE_DEFAULT_LENGTH);

	const XMC_GPIO_CONFIG_t int_pin_config = {
		.mode             = XMC_GPIO_MODE_INPUT_PULL_UP,
		.input_hysteresis = XMC_GPIO_INPUT_HYSTERESIS_STANDARD
	};

	XMC_GPIO_Init(LPS22HB_INT_PIN, &int_pin_config);

	coop_task_init(&lps22hb_task, lps22hb_tick_task);

	lps22hb_init_spi();
}

void lps22hb_init_spi(void) {
	// Initialise SPI FIFO
	lps22hb.spi_fifo.baudrate = LPS22HB_SPI_BAUDRATE;
	lps22hb.spi_fifo.channel = LPS22HB_USIC_SPI;

	lps22hb.spi_fifo.rx_fifo_size = LPS22HB_RX_FIFO_SIZE;
	lps22hb.spi_fifo.rx_fifo_pointer = LPS22HB_RX_FIFO_DATA_POINTER;
	lps22hb.spi_fifo.tx_fifo_size = LPS22HB_TX_FIFO_SIZE;
	lps22hb.spi_fifo.tx_fifo_pointer = LPS22HB_TX_FIFO_DATA_POINTER;

	lps22hb.spi_fifo.clock_passive_level = LPS22HB_CLOCK_PASSIVE_LEVEL;
	lps22hb.spi_fifo.clock_output = LPS22HB_CLOCK_OUTPUT;
	lps22hb.spi_fifo.slave = LPS22HB_SLAVE;

	lps22hb.spi_fifo.sclk_port = LPS22HB_SCLK_PORT;
	lps22hb.spi_fifo.sclk_pin = LPS22HB_SCLK_PIN;
	lps22hb.spi_fifo.sclk_pin_mode = LPS22HB_SCLK_PIN_MODE;

	lps22hb.spi_fifo.select_port = LPS22HB_SELECT_PORT;
	lps22hb.spi_fifo.select_pin = LPS22HB_SELECT_PIN;
	lps22hb.spi_fifo.select_pin_mode = LPS22HB_SELECT_PIN_MODE;

	lps22hb.spi_fifo.mosi_port = LPS22HB_MOSI_PORT;
	lps22hb.spi_fifo.mosi_pin = LPS22HB_MOSI_PIN;
	lps22hb.spi_fifo.mosi_pin_mode = LPS22HB_MOSI_PIN_MODE;

	lps22hb.spi_fifo.miso_port = LPS22HB_MISO_PORT;
	lps22hb.spi_fifo.miso_pin = LPS22HB_MISO_PIN;
	lps22hb.spi_fifo.miso_input = LPS22HB_MISO_INPUT;
	lps22hb.spi_fifo.miso_source = LPS22HB_MISO_SOURCE;

	spi_fifo_init(&lps22hb.spi_fifo);

	lps22hb.reconfigure = true;
}

void lps22hb_tick(void) {
	coop_task_tick(&lps22hb_task);
}

// NOTE: assumes SPI FIFO is idle/ready
static bool lps22hb_transceive_task(uint8_t *buffer, const uint8_t length) {
	SPIFifo *spi_fifo = &lps22hb.spi_fifo;

	spi_fifo_transceive(spi_fifo, length, buffer);

	while (true) {
		SPIFifoState state = spi_fifo_next_state(spi_fifo);

		if (state & SPI_FIFO_STATE_ERROR) {
			goto error;
		}

		if (state == SPI_FIFO_STATE_TRANSCEIVE_READY) {
			break;
		}

		coop_task_yield();
	}

	if (spi_fifo_read_fifo(spi_fifo, buffer, length) != length) {
		goto error;
	}

	coop_task_yield();

	return true;

error:
	coop_task_yield();
	lps22hb_init_spi();

	return false;
}

void lps22hb_tick_task(void) {
	static bool reset_moving_averages = true;
	static uint8_t drop_next_reading = 0;
	static uint8_t altitude_factors_count = sizeof(altitude_factors) / sizeof(altitude_factors[0]);
	uint8_t buffer[6];

	while (true) {
		if (lps22hb.reconfigure || lps22hb.calibration_changed) {
			// Reset of the sensor and clear its memory
			buffer[0] = LPS22HB_GET_WRITE_ADDR(LPS22HB_REG_ADDR_CTRL_REG2);
			buffer[1] = LPS22HB_REG_CTRL_REG2_MSK_BOOT | LPS22HB_REG_CTRL_REG2_MSK_SWRESET;

			if (!lps22hb_transceive_task(buffer, 2)) {
				continue;
			}

			// Wait for reset to complete
			while (true) {
				buffer[0] = LPS22HB_GET_READ_ADDR(LPS22HB_REG_ADDR_CTRL_REG2);
				buffer[1] = 0;

				if (!lps22hb_transceive_task(buffer, 2)) {
					continue;
				}

				if ((buffer[1] & (LPS22HB_REG_CTRL_REG2_MSK_BOOT | LPS22HB_REG_CTRL_REG2_MSK_SWRESET)) == 0) {
					break;
				}

				coop_task_sleep_ms(1);
			}

			// Configure interrupt pin as active-low open-drain for the the data-ready signal
			buffer[0] = LPS22HB_GET_WRITE_ADDR(LPS22HB_REG_ADDR_CTRL_REG3);
			buffer[1] = LPS22HB_REG_CTRL_REG3_MSK_INT_H_L | LPS22HB_REG_CTRL_REG3_MSK_PP_OD | LPS22HB_REG_CTRL_REG3_MSK_DRDY;

			if (!lps22hb_transceive_task(buffer, 2)) {
				continue;
			}

			// Apply calibration
			int16_t cal_offset = lps22hb_get_cal_offset(lps22hb.measured_air_pressure,
			                                            lps22hb.actual_air_pressure);

			buffer[0] = LPS22HB_GET_WRITE_ADDR(LPS22HB_REG_ADDR_RPDS_L);
			buffer[1] = (uint8_t)(cal_offset & 0x00FF); // LSB
			buffer[2] = (uint8_t)((cal_offset & 0xFF00) >> 8); // MSB

			if (!lps22hb_transceive_task(buffer, 3)) {
				continue;
			}

			if (lps22hb.calibration_changed) {
				lps22hb.calibration_changed = false;
				reset_moving_averages = true;
			}

			// Set data-rate, low-pass-filter and enable block-data-update
			buffer[0] = LPS22HB_GET_WRITE_ADDR(LPS22HB_REG_ADDR_CTRL_REG1);
			buffer[1] = odr_msk[lps22hb.data_rate] | lpfp_msk[lps22hb.air_pressure_low_pass_filter];

			if (!lps22hb_transceive_task(buffer, 2)) {
				continue;
			}

			// Reset low-pass filter to avoid transition phase
			buffer[0] = LPS22HB_GET_READ_ADDR(LPS22HB_REG_ADDR_LPFP_RES);
			buffer[1] = 0;

			if (!lps22hb_transceive_task(buffer, 2)) {
				continue;
			}

			// FIXME: The low-pass filter reset doesn't seem to work correctly
			//        at 75Hz data rate. Work around this by droping the next
			//        30 reading to ignore the transitiopn phase
			if (lps22hb.data_rate == 5) { // 75Hz
				drop_next_reading = 30;
			}

			lps22hb.reconfigure = false;
		}

		if (XMC_GPIO_GetInput(LPS22HB_INT_PIN) == 0) {
			buffer[0] = LPS22HB_GET_READ_ADDR(LPS22HB_REG_ADDR_PRESS_OUT_XL);
			buffer[1] = 0;
			buffer[2] = 0;
			buffer[3] = 0;
			buffer[4] = 0;
			buffer[5] = 0;

			if (!lps22hb_transceive_task(buffer, 6)) {
				continue;
			}

			if (drop_next_reading > 0) {
				--drop_next_reading;
			} else {
				// Divide by 4096 to get mbar and multiple by 1000 to get mbar/1000.
				// reduce the factor from 1000 / 4096 to 125 / 512 to avoid int32_t overflow
				int32_t air_pressure = (((int32_t)(((uint32_t)buffer[3] << 24) | ((uint32_t)buffer[2] << 16) | ((uint32_t)buffer[1] << 8)) >> 8) * 125) / 512;
				int16_t temperature = (int16_t)(((uint16_t)buffer[5] << 8) | (uint16_t)buffer[4]);

				if (reset_moving_averages) {
					// If this is the first real measurement we reinitialize the moving average.
					// Otherwise it would slowly ramp up from 0 to the real value for the user.
					moving_average_init(&lps22hb.moving_average_air_pressure, air_pressure,
					                    lps22hb.moving_average_air_pressure.length);

					moving_average_init(&lps22hb.moving_average_temperature, temperature,
					                    lps22hb.moving_average_temperature.length);

					reset_moving_averages = false;
				}

				// Put air pressure and temperature measurements through moving average filter.
				lps22hb.air_pressure = moving_average_handle_value(&lps22hb.moving_average_air_pressure, air_pressure);
				lps22hb.temperature = moving_average_handle_value(&lps22hb.moving_average_temperature, temperature);

				// Calculate altitude from the current air pressure
				uint8_t upper = altitude_factors_count - 1;
				uint8_t lower;

				while (upper > 0 && lps22hb.air_pressure > altitude_factors[upper].air_pressure) {
					upper--;
				}

				int32_t reference_delta = lps22hb.reference_air_pressure - lps22hb.air_pressure; // mbar/1000

				if (upper < altitude_factors_count - 1) {
					lower = upper + 1;

					int32_t total_delta = altitude_factors[upper].air_pressure - altitude_factors[lower].air_pressure;
					int32_t upper_delta = altitude_factors[upper].air_pressure - lps22hb.air_pressure;
					int32_t lower_delta = lps22hb.air_pressure - altitude_factors[lower].air_pressure;
					int32_t factor = altitude_factors[upper].factor * lower_delta +
					                 altitude_factors[lower].factor * upper_delta;

					lps22hb.altitude = ((int64_t)reference_delta * (int64_t)factor) / total_delta;
				} else {
					lps22hb.altitude = reference_delta * altitude_factors[upper].factor;
				}
			}
		}

		coop_task_yield();
	}
}

int32_t lps22hb_get_air_pressure(void) {
	return lps22hb.air_pressure;
}

int32_t lps22hb_get_altitude(void) {
	return lps22hb.altitude;
}

int32_t lps22hb_get_temperature(void) {
	return lps22hb.temperature;
}
