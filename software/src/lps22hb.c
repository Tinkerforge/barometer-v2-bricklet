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

LPS22HB_t lps22hb;

const AltitudeFactor altitude_factors[] = {
	[0] = {5017600, 14},
	[1] = {4579328, 13},
	[2] = {4145152, 12},
	[3] = {3723264, 11},
	[4] = {3309568, 10},
	[5] = {2908160, 9},
	[6] = {2514944, 8},
	[7] = {2129920, 7}
};

void eeprom_write_calibration(void) {
	logd("[+] B2: eeprom_write_calibration()\n\r");

	uint32_t page[EEPROM_PAGE_SIZE/sizeof(uint32_t)];

	page[CALIBRATION_MAGIC_POS] = CALIBRATION_MAGIC;
	page[CALIBRATION_OFFSET_POS] = lps22hb.calibration_offset;

	if(!bootloader_write_eeprom_page(CALIBRATION_PAGE, page)) {
		// TODO: Error handling?
		return;
	}
}

void eeprom_read_calibration(void) {
	logd("[+] B2: eeprom_read_calibration()\n\r");

	uint32_t page[EEPROM_PAGE_SIZE/sizeof(uint32_t)];

	bootloader_read_eeprom_page(CALIBRATION_PAGE, page);

	// The magic number is not where it is supposed to be.
	// This is either our first startup or something went wrong.
	// We initialize the calibration data with sane default values.
	if(page[0] != CALIBRATION_MAGIC) {
		lps22hb.calibration_offset = 0;
		eeprom_write_calibration();

		return;
	}

	lps22hb.calibration_offset = page[CALIBRATION_OFFSET_POS];
}

void lps22hb_init(void) {
	logd("[+] B2: lps22hb_init()\n\r");

	lps22hb.altitude = 0;
	lps22hb.temperature = 0;
	lps22hb.air_pressure = 0;
	lps22hb.calibration_offset = 0;
	lps22hb.reference_air_pressure = (int32_t)DEFAULT_REFERENCE_AIR_PRESSURE;

	// Load settings from flash
	eeprom_read_calibration();

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

	// Configure the sensor

	// Boot and software reset of the sensor
	lps22hb.spi_fifo_buf[0] = GET_WRITE_ADDR(LPS22HB_REG_ADDR_CTRL_REG2);
	lps22hb.spi_fifo_buf[1] = LPS22HB_REG_CTRL_REG2_MSK_BOOT | LPS22HB_REG_CTRL_REG2_MSK_SWRESET;

	spi_fifo_transceive(&lps22hb.spi_fifo, 2, &lps22hb.spi_fifo_buf[0]);
	system_timer_sleep_ms(8);
	spi_fifo_next_state(&lps22hb.spi_fifo);

	// Output registers not updated until they are read, must read register PRESS_OUT_H last
	lps22hb.spi_fifo_buf[0] = GET_WRITE_ADDR(LPS22HB_REG_ADDR_CTRL_REG1);
	lps22hb.spi_fifo_buf[1] = LPS22HB_REG_CTRL_REG1_MSK_BDU;

	spi_fifo_transceive(&lps22hb.spi_fifo, 2, &lps22hb.spi_fifo_buf[0]);
	system_timer_sleep_ms(4);
	spi_fifo_next_state(&lps22hb.spi_fifo);

	// Apply calibration
	lps22hb.spi_fifo_buf[0] = GET_WRITE_ADDR(LPS22HB_REG_ADDR_RPDS_L);
	lps22hb.spi_fifo_buf[1] = (uint8_t)(lps22hb.calibration_offset & 0x00FF); // LSB
	lps22hb.spi_fifo_buf[2] = (uint8_t)(((lps22hb.calibration_offset & 0xFF00) >> 8)); // MSB

	spi_fifo_transceive(&lps22hb.spi_fifo, 3, &lps22hb.spi_fifo_buf[0]);
	system_timer_sleep_ms(4);
	spi_fifo_next_state(&lps22hb.spi_fifo);

	// Start initial conversion
	lps22hb.spi_fifo_buf[0] = GET_WRITE_ADDR(LPS22HB_REG_ADDR_CTRL_REG2);
	lps22hb.spi_fifo_buf[1] = (LPS22HB_REG_CTRL_REG2_MSK_ONE_SHOT | LPS22HB_REG_CTRL_REG2_MSK_IF_ADD_INC);

	XMC_USIC_CH_RXFIFO_Flush(lps22hb.spi_fifo.channel);
	spi_fifo_transceive(&lps22hb.spi_fifo, 2, &lps22hb.spi_fifo_buf[0]);

	lps22hb.sm = SM_INIT;

	moving_average_init(&lps22hb.moving_average_altitude, 0, MOVING_AVERAGE_DEFAULT_LENGTH);
	moving_average_init(&lps22hb.moving_average_temperature, 0, MOVING_AVERAGE_DEFAULT_LENGTH);
	moving_average_init(&lps22hb.moving_average_air_pressure, 0, MOVING_AVERAGE_DEFAULT_LENGTH);
}

void lps22hb_tick(void) {
	static bool first_value = true;
	SPIFifoState fs = spi_fifo_next_state(&lps22hb.spi_fifo);

	if(fs & SPI_FIFO_STATE_ERROR) {
		lps22hb_init();

		return;
	}

	if(fs == SPI_FIFO_STATE_TRANSCEIVE_READY) {
		if(lps22hb.sm == SM_INIT) {
			lps22hb.spi_fifo_buf[0] = GET_READ_ADDR(LPS22HB_REG_ADDR_STATUS);
			lps22hb.spi_fifo_buf[1] = 0x00;

			XMC_USIC_CH_RXFIFO_Flush(lps22hb.spi_fifo.channel);
			spi_fifo_transceive(&lps22hb.spi_fifo, 2, &lps22hb.spi_fifo_buf[0]);

			lps22hb.sm = SM_CHECK_STATUS;
		}
		else if(lps22hb.sm == SM_CHECK_STATUS) {
			spi_fifo_read_fifo(&lps22hb.spi_fifo, &lps22hb.spi_fifo_buf[0], 2);

			if ((lps22hb.spi_fifo_buf[1] & LPS22HB_REG_STATUS_MSK_P_DA)) {
				lps22hb.spi_fifo_buf[0] = GET_READ_ADDR(LPS22HB_REG_ADDR_PRESS_OUT_XL);
				lps22hb.spi_fifo_buf[1] = 0x00;
				lps22hb.spi_fifo_buf[2] = 0x00;
				lps22hb.spi_fifo_buf[3] = 0x00;
				lps22hb.spi_fifo_buf[4] = 0x00;
				lps22hb.spi_fifo_buf[5] = 0x00;

				XMC_USIC_CH_RXFIFO_Flush(lps22hb.spi_fifo.channel);
				spi_fifo_transceive(&lps22hb.spi_fifo, 6, &lps22hb.spi_fifo_buf[0]);

				lps22hb.sm = SM_READ_SENSOR_DATA;
			}
			else {
				lps22hb.spi_fifo_buf[0] = GET_READ_ADDR(LPS22HB_REG_ADDR_STATUS);
				lps22hb.spi_fifo_buf[1] = 0x00;

				XMC_USIC_CH_RXFIFO_Flush(lps22hb.spi_fifo.channel);
				spi_fifo_transceive(&lps22hb.spi_fifo, 2, &lps22hb.spi_fifo_buf[0]);
			}
		}
		else if(lps22hb.sm == SM_READ_SENSOR_DATA) {
			// Read and process the data
			spi_fifo_read_fifo(&lps22hb.spi_fifo, &lps22hb.spi_fifo_buf[0], 6);

			uint8_t upper = 7;
			uint8_t lower = 0;
			int32_t delta = 0;
			int64_t factor = 0;
			int32_t total_delta = 0;
			int32_t upper_delta = 0;
			int32_t lower_delta = 0;

			int32_t altitude = 0;
			int32_t temperature = ((lps22hb.spi_fifo_buf[5] << 8) | lps22hb.spi_fifo_buf[4]);
			int32_t air_pressure = \
				((lps22hb.spi_fifo_buf[3] << 16) | (lps22hb.spi_fifo_buf[2] << 8) | lps22hb.spi_fifo_buf[1]);

			if((lps22hb.spi_fifo_buf[3] & 0x80)) {
				// Negative number, apply two's complement
				air_pressure &= ~(1 << 23); // Clear indicator bit
				air_pressure = (~(air_pressure)) + 1;
				air_pressure |= 0xFF000000;
			}

			if((lps22hb.spi_fifo_buf[5] & 0x80)) {
				// Negative number, apply two's complement
				temperature &= ~(1 << 15); // Clear indicator bit
				temperature = (~(temperature)) + 1;
				temperature |= 0xFFFF0000;
			}

			// Calculate altitude from the current air pressure
			while(upper > 0 && (air_pressure > altitude_factors[upper].air_pressure)) {
				upper--;
			}

			delta = lps22hb.reference_air_pressure - air_pressure;

			if(upper < 7) {
				lower = upper + 1;

				total_delta = altitude_factors[upper].air_pressure - altitude_factors[lower].air_pressure;
				upper_delta = altitude_factors[upper].air_pressure - air_pressure;
				lower_delta = air_pressure - altitude_factors[lower].air_pressure;

				factor = ((altitude_factors[upper].factor * lower_delta) +
						  (altitude_factors[lower].factor * upper_delta)) / total_delta;

				altitude = (int32_t)(((int64_t)delta * (int64_t)factor) >> 2); // In mm
			}
			else {
				lower = upper;
				altitude = (int32_t)((delta * altitude_factors[upper].factor) >> 2); // In mm
			}

			if(first_value) {
				// If this is the first real measurement we reinitialize the moving average.
				// Otherwise it would slowly ramp up from 0 to the real value for the user.
				moving_average_init(&lps22hb.moving_average_altitude,
				                    altitude,
				                    lps22hb.moving_average_altitude.length);

				moving_average_init(&lps22hb.moving_average_temperature,
				                    temperature,
				                    lps22hb.moving_average_temperature.length);

				moving_average_init(&lps22hb.moving_average_air_pressure,
				                    air_pressure,
				                    lps22hb.moving_average_air_pressure.length);

				lps22hb.altitude = altitude;
				lps22hb.temperature = temperature;
				lps22hb.air_pressure = air_pressure;

				first_value = false;
			}
			else {
				// Put temperature and humidity measurements through moving average filter.
				lps22hb.altitude = moving_average_handle_value(&lps22hb.moving_average_altitude, altitude);
				lps22hb.temperature = moving_average_handle_value(&lps22hb.moving_average_temperature, temperature);
				lps22hb.air_pressure = moving_average_handle_value(&lps22hb.moving_average_air_pressure, air_pressure);
			}

			// Start new conversion cycle
			lps22hb.spi_fifo_buf[0] = GET_WRITE_ADDR(LPS22HB_REG_ADDR_CTRL_REG2);
			lps22hb.spi_fifo_buf[1] = (LPS22HB_REG_CTRL_REG2_MSK_ONE_SHOT | LPS22HB_REG_CTRL_REG2_MSK_IF_ADD_INC);

			XMC_USIC_CH_RXFIFO_Flush(lps22hb.spi_fifo.channel);
			spi_fifo_transceive(&lps22hb.spi_fifo, 2, &lps22hb.spi_fifo_buf[0]);

			lps22hb.sm = SM_CHECK_STATUS;
		}
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
