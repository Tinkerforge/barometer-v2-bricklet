// This example is not self-contained.
// It requres usage of the example driver specific to your platform.
// See the HAL documentation.

#include "bindings/hal_common.h"
#include "bindings/bricklet_barometer_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Barometer Bricklet 2.0

void check(int rc, const char* msg);

void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);


// Callback function for air pressure callback
static void air_pressure_handler(TF_BarometerV2 *device, int32_t air_pressure,
                                 void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Air Pressure: %d 1/%d hPa\n", air_pressure, 1000);
}

static TF_BarometerV2 b;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_barometer_v2_create(&b, UID, hal), "create device object");

	// Register air pressure callback to function air_pressure_handler
	tf_barometer_v2_register_air_pressure_callback(&b,
	                                               air_pressure_handler,
	                                               NULL);

	// Set period for air pressure callback to 1s (1000ms) without a threshold
	tf_barometer_v2_set_air_pressure_callback_configuration(&b, 1000, false, 'x', 0, 0);
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
