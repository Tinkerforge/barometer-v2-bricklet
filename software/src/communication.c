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

#define CALLBACK_VALUE_TYPE CALLBACK_VALUE_TYPE_INT32

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/utility/callback_value.h"

#include "lps22hb.h"

CallbackValue callback_value_altitude;
CallbackValue callback_value_temperature;
CallbackValue callback_value_air_pressure;

BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_GET_AIR_PRESSURE: return get_callback_value(message, response, &callback_value_air_pressure);
		case FID_SET_AIR_PRESSURE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration(message, &callback_value_air_pressure);
		case FID_GET_AIR_PRESSURE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration(message, response, &callback_value_air_pressure);
		case FID_GET_ALTITUDE: return get_callback_value(message, response, &callback_value_altitude);
		case FID_SET_ALTITUDE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration(message, &callback_value_altitude);
		case FID_GET_ALTITUDE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration(message, response, &callback_value_altitude);
		case FID_GET_TEMPERATURE: return get_callback_value(message, response, &callback_value_temperature);
		case FID_SET_TEMPERATURE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration(message, &callback_value_temperature);
		case FID_GET_TEMPERATURE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration(message, response, &callback_value_temperature);
		case FID_SET_MOVING_AVERAGE_CONFIGURATION: return set_moving_average_configuration(message);
		case FID_GET_MOVING_AVERAGE_CONFIGURATION: return get_moving_average_configuration(message, response);
		case FID_SET_REFERENCE_AIR_PRESSURE: return set_reference_air_pressure(message);
		case FID_GET_REFERENCE_AIR_PRESSURE: return get_reference_air_pressure(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse set_moving_average_configuration(const SetMovingAverageConfiguration *data) {

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_moving_average_configuration(const GetMovingAverageConfiguration *data, GetMovingAverageConfiguration_Response *response) {
	response->header.length = sizeof(GetMovingAverageConfiguration_Response);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}

BootloaderHandleMessageResponse set_reference_air_pressure(const SetReferenceAirPressure *data) {

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_reference_air_pressure(const GetReferenceAirPressure *data, GetReferenceAirPressure_Response *response) {
	response->header.length = sizeof(GetReferenceAirPressure_Response);

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}




bool handle_air_pressure_callback(void) {
	return handle_callback_value_callback(&callback_value_air_pressure, FID_CALLBACK_AIR_PRESSURE);
}

bool handle_altitude_callback(void) {
	return handle_callback_value_callback(&callback_value_altitude, FID_CALLBACK_ALTITUDE);
}

bool handle_temperature_callback(void) {
	return handle_callback_value_callback(&callback_value_temperature, FID_CALLBACK_TEMPERATURE);
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	// TODO: Add proper functions
	callback_value_init(&callback_value_air_pressure, lps22hb_get_air_pressure);
	callback_value_init(&callback_value_altitude, lps22hb_get_altitude);
	callback_value_init(&callback_value_temperature, lps22hb_get_temperature);

	communication_callback_init();
}
