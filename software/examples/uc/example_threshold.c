#include "bindings/hal_common.h"
#include "bindings/bricklet_barometer_v2.h"

#define UID "XYZ" // Change XYZ to the UID of your Barometer Bricklet 2.0

void check(int rc, const char* msg);

// Callback function for air pressure callback
void air_pressure_handler(TF_BarometerV2 *device, int32_t air_pressure, void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Air Pressure: %d 1/%d hPa\n", air_pressure, 1000.0);
	tf_hal_printf("Enjoy the potentially good weather!\n");
}

TF_BarometerV2 b;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_barometer_v2_create(&b, UID, hal), "create device object");

	// Register air pressure callback to function air_pressure_handler
	tf_barometer_v2_register_air_pressure_callback(&b,
	                                               air_pressure_handler,
	                                               NULL);

	// Configure threshold for air pressure "greater than 1025 hPa"
	// with a debounce period of 1s (1000ms)
	tf_barometer_v2_set_air_pressure_callback_configuration(&b, 1000, false, '>', 1025*1000, 0);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
