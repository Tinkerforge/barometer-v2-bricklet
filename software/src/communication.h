/* barometer-v2-bricklet
 * Copyright (C) 2018 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define BAROMETER_V2_THRESHOLD_OPTION_OFF 'x'
#define BAROMETER_V2_THRESHOLD_OPTION_OUTSIDE 'o'
#define BAROMETER_V2_THRESHOLD_OPTION_INSIDE 'i'
#define BAROMETER_V2_THRESHOLD_OPTION_SMALLER '<'
#define BAROMETER_V2_THRESHOLD_OPTION_GREATER '>'

#define BAROMETER_V2_DATA_RATE_OFF 0
#define BAROMETER_V2_DATA_RATE_1HZ 1
#define BAROMETER_V2_DATA_RATE_10HZ 2
#define BAROMETER_V2_DATA_RATE_25HZ 3
#define BAROMETER_V2_DATA_RATE_50HZ 4
#define BAROMETER_V2_DATA_RATE_75HZ 5

#define BAROMETER_V2_LOW_PASS_FILTER_OFF 0
#define BAROMETER_V2_LOW_PASS_FILTER_1_9TH 1
#define BAROMETER_V2_LOW_PASS_FILTER_1_20TH 2

#define BAROMETER_V2_BOOTLOADER_MODE_BOOTLOADER 0
#define BAROMETER_V2_BOOTLOADER_MODE_FIRMWARE 1
#define BAROMETER_V2_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define BAROMETER_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define BAROMETER_V2_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define BAROMETER_V2_BOOTLOADER_STATUS_OK 0
#define BAROMETER_V2_BOOTLOADER_STATUS_INVALID_MODE 1
#define BAROMETER_V2_BOOTLOADER_STATUS_NO_CHANGE 2
#define BAROMETER_V2_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define BAROMETER_V2_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define BAROMETER_V2_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define BAROMETER_V2_STATUS_LED_CONFIG_OFF 0
#define BAROMETER_V2_STATUS_LED_CONFIG_ON 1
#define BAROMETER_V2_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define BAROMETER_V2_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_GET_AIR_PRESSURE 1
#define FID_SET_AIR_PRESSURE_CALLBACK_CONFIGURATION 2
#define FID_GET_AIR_PRESSURE_CALLBACK_CONFIGURATION 3
#define FID_GET_ALTITUDE 5
#define FID_SET_ALTITUDE_CALLBACK_CONFIGURATION 6
#define FID_GET_ALTITUDE_CALLBACK_CONFIGURATION 7
#define FID_GET_TEMPERATURE 9
#define FID_SET_TEMPERATURE_CALLBACK_CONFIGURATION 10
#define FID_GET_TEMPERATURE_CALLBACK_CONFIGURATION 11
#define FID_SET_MOVING_AVERAGE_CONFIGURATION 13
#define FID_GET_MOVING_AVERAGE_CONFIGURATION 14
#define FID_SET_REFERENCE_AIR_PRESSURE 15
#define FID_GET_REFERENCE_AIR_PRESSURE 16
#define FID_SET_CALIBRATION 17
#define FID_GET_CALIBRATION 18
#define FID_SET_SENSOR_CONFIGURATION 19
#define FID_GET_SENSOR_CONFIGURATION 20

#define FID_CALLBACK_AIR_PRESSURE 4
#define FID_CALLBACK_ALTITUDE 8
#define FID_CALLBACK_TEMPERATURE 12

typedef struct {
	TFPMessageHeader header;
	uint16_t moving_average_length_air_pressure;
	uint16_t moving_average_length_temperature;
} __attribute__((__packed__)) SetMovingAverageConfiguration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetMovingAverageConfiguration;

typedef struct {
	TFPMessageHeader header;
	uint16_t moving_average_length_air_pressure;
	uint16_t moving_average_length_temperature;
} __attribute__((__packed__)) GetMovingAverageConfiguration_Response;

typedef struct {
	TFPMessageHeader header;
	int32_t air_pressure;
} __attribute__((__packed__)) SetReferenceAirPressure;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetReferenceAirPressure;

typedef struct {
	TFPMessageHeader header;
	int32_t air_pressure;
} __attribute__((__packed__)) GetReferenceAirPressure_Response;

typedef struct {
	TFPMessageHeader header;
	int32_t measured_air_pressure;
	int32_t actual_air_pressure;
} __attribute__((__packed__)) SetCalibration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetCalibration;

typedef struct {
	TFPMessageHeader header;
	int32_t measured_air_pressure;
	int32_t actual_air_pressure;
} __attribute__((__packed__)) GetCalibration_Response;

typedef struct {
	TFPMessageHeader header;
	uint8_t data_rate;
	uint8_t air_pressure_low_pass_filter;
} __attribute__((__packed__)) SetSensorConfiguration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetSensorConfiguration;

typedef struct {
	TFPMessageHeader header;
	uint8_t data_rate;
	uint8_t air_pressure_low_pass_filter;
} __attribute__((__packed__)) GetSensorConfiguration_Response;

// Function prototypes
BootloaderHandleMessageResponse set_moving_average_configuration(const SetMovingAverageConfiguration *data);
BootloaderHandleMessageResponse get_moving_average_configuration(const GetMovingAverageConfiguration *data, GetMovingAverageConfiguration_Response *response);
BootloaderHandleMessageResponse set_reference_air_pressure(const SetReferenceAirPressure *data);
BootloaderHandleMessageResponse get_reference_air_pressure(const GetReferenceAirPressure *data, GetReferenceAirPressure_Response *response);
BootloaderHandleMessageResponse set_calibration(const SetCalibration *data);
BootloaderHandleMessageResponse get_calibration(const GetCalibration *data, GetCalibration_Response *response);
BootloaderHandleMessageResponse set_sensor_configuration(const SetSensorConfiguration *data);
BootloaderHandleMessageResponse get_sensor_configuration(const GetSensorConfiguration *data, GetSensorConfiguration_Response *response);

// Callbacks
bool handle_air_pressure_callback(void);
bool handle_altitude_callback(void);
bool handle_temperature_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 3
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_air_pressure_callback, \
	handle_altitude_callback, \
	handle_temperature_callback, \

#endif
