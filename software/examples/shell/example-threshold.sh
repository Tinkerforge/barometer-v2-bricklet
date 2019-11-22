#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Barometer Bricklet 2.0

# Handle incoming air pressure callbacks
tinkerforge dispatch barometer-v2-bricklet $uid air-pressure\
 --execute "echo Air Pressure: {air_pressure}/1000 hPa. Enjoy the potentially good weather!" &

# Configure threshold for air pressure "greater than 1025 hPa"
# with a debounce period of 1s (1000ms)
tinkerforge call barometer-v2-bricklet $uid set-air-pressure-callback-configuration 1000 false threshold-option-greater 1025000 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
