/* barometer-v2-bricklet
 * Copyright (C) 2018 Ishraq Ibne Ashraf <ishraq@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/utility/callback_value.h"
#include "bricklib2/hal/system_timer/system_timer.h"
#include "bricklib2/utility/communication_callback.h"

#include "lps22hb.h"

// FIXME: use a different data types, now that callback-value supports that?
CallbackValue_int32_t callback_value_altitude;
CallbackValue_int32_t callback_value_temperature;
CallbackValue_int32_t callback_value_air_pressure;

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_GET_AIR_PRESSURE: return get_callback_value_int32_t(message, response, &callback_value_air_pressure);
		case FID_SET_AIR_PRESSURE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration_int32_t(message, &callback_value_air_pressure);
		case FID_GET_AIR_PRESSURE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration_int32_t(message, response, &callback_value_air_pressure);
		case FID_GET_ALTITUDE: return get_callback_value_int32_t(message, response, &callback_value_altitude);
		case FID_SET_ALTITUDE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration_int32_t(message, &callback_value_altitude);
		case FID_GET_ALTITUDE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration_int32_t(message, response, &callback_value_altitude);
		case FID_GET_TEMPERATURE: return get_callback_value_int32_t(message, response, &callback_value_temperature);
		case FID_SET_TEMPERATURE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration_int32_t(message, &callback_value_temperature);
		case FID_GET_TEMPERATURE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration_int32_t(message, response, &callback_value_temperature);
		case FID_SET_MOVING_AVERAGE_CONFIGURATION: return set_moving_average_configuration(message);
		case FID_GET_MOVING_AVERAGE_CONFIGURATION: return get_moving_average_configuration(message, response);
		case FID_SET_REFERENCE_AIR_PRESSURE: return set_reference_air_pressure(message);
		case FID_GET_REFERENCE_AIR_PRESSURE: return get_reference_air_pressure(message, response);
		case FID_SET_CALIBRATION: return set_calibration(message);
		case FID_GET_CALIBRATION: return get_calibration(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}

BootloaderHandleMessageResponse set_moving_average_configuration(const SetMovingAverageConfiguration *data) {
	if((data->moving_average_length_air_pressure > MOVING_AVERAGE_MAX_LENGTH) ||
	   (data->moving_average_length_altitude > MOVING_AVERAGE_MAX_LENGTH) ||
	   (data->moving_average_length_temperature > MOVING_AVERAGE_MAX_LENGTH) ||
	   (data->moving_average_length_air_pressure < 1) ||
	   (data->moving_average_length_altitude < 1) ||
	   (data->moving_average_length_temperature < 1)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	moving_average_new_length(&lps22hb.moving_average_air_pressure, data->moving_average_length_air_pressure);
	moving_average_new_length(&lps22hb.moving_average_altitude, data->moving_average_length_altitude);
	moving_average_new_length(&lps22hb.moving_average_temperature, data->moving_average_length_temperature);

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_moving_average_configuration(const GetMovingAverageConfiguration *data, GetMovingAverageConfiguration_Response *response) {
	response->header.length = sizeof(GetMovingAverageConfiguration_Response);
	response->moving_average_length_air_pressure = lps22hb.moving_average_air_pressure.length;
	response->moving_average_length_altitude = lps22hb.moving_average_altitude.length;
	response->moving_average_length_temperature = lps22hb.moving_average_temperature.length;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_reference_air_pressure(const SetReferenceAirPressure *data) {
	if(data->air_pressure < 260000 || data->air_pressure > 1260000) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	if(data->air_pressure == 0) {
		lps22hb.reference_air_pressure = lps22hb.air_pressure;
	}
	else {
		lps22hb.reference_air_pressure = data->air_pressure;
	}

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_reference_air_pressure(const GetReferenceAirPressure *data, GetReferenceAirPressure_Response *response) {
	response->header.length = sizeof(GetReferenceAirPressure_Response);
	response->air_pressure = lps22hb.reference_air_pressure;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_calibration(const SetCalibration *data) {
	if((data->measured_air_pressure < 260000 ||
	    data->measured_air_pressure > 1260000 ||
	    data->actual_air_pressure < 260000 ||
	    data->actual_air_pressure > 1260000) &&
	   (data->measured_air_pressure != 0 ||
	    data->actual_air_pressure != 0)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	// Save to RAM
	lps22hb.cal_measured_air_pressure = data->measured_air_pressure;
	lps22hb.cal_actual_air_pressure = data->actual_air_pressure;
	lps22hb.cal_offset = get_cal_offset(data->measured_air_pressure,
	                                    data->actual_air_pressure);
	lps22hb.cal_changed = true;

	// Save to flash
	eeprom_write_calibration();

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_calibration(const GetCalibration *data, GetCalibration_Response *response) {
	response->header.length = sizeof(GetCalibration_Response);
	response->measured_air_pressure = lps22hb.cal_measured_air_pressure;
	response->actual_air_pressure = lps22hb.cal_actual_air_pressure;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

bool handle_air_pressure_callback(void) {
	return handle_callback_value_callback_int32_t(&callback_value_air_pressure, FID_CALLBACK_AIR_PRESSURE);
}

bool handle_altitude_callback(void) {
	return handle_callback_value_callback_int32_t(&callback_value_altitude, FID_CALLBACK_ALTITUDE);
}

bool handle_temperature_callback(void) {
	return handle_callback_value_callback_int32_t(&callback_value_temperature, FID_CALLBACK_TEMPERATURE);
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	callback_value_init_int32_t(&callback_value_altitude, lps22hb_get_altitude);
	callback_value_init_int32_t(&callback_value_temperature, lps22hb_get_temperature);
	callback_value_init_int32_t(&callback_value_air_pressure, lps22hb_get_air_pressure);

	communication_callback_init();
}
