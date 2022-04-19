// This example is not self-contained.
// It requres usage of the example driver specific to your platform.
// See the HAL documentation.

#include "bindings/hal_common.h"
#include "bindings/bricklet_barometer_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Barometer Bricklet 2.0

void check(int rc, const char* msg);

void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);


static TF_BarometerV2 b;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_barometer_v2_create(&b, UID, hal), "create device object");

	// Get current air pressure
	int32_t air_pressure;
	check(tf_barometer_v2_get_air_pressure(&b, &air_pressure), "get air pressure");

	tf_hal_printf("Air Pressure: %d 1/%d hPa\n", air_pressure, 1000);

	// Get current altitude
	int32_t altitude;
	check(tf_barometer_v2_get_altitude(&b, &altitude), "get altitude");

	tf_hal_printf("Altitude: %d 1/%d m\n", altitude, 1000);
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
