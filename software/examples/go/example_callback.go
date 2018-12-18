package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/barometer_v2_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Barometer Bricklet 2.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	b, _ := barometer_v2_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	b.RegisterAirPressureCallback(func(airPressure int32) {
		fmt.Printf("Air Pressure: %f mbar\n", float64(airPressure)/1000.0)
	})

	// Set period for air pressure callback to 1s (1000ms) without a threshold.
	b.SetAirPressureCallbackConfiguration(1000, false, 'x', 0, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
