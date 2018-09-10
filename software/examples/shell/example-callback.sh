#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Barometer Bricklet 2.0

# Handle incoming air pressure callbacks
tinkerforge dispatch barometer-v2-bricklet $uid air-pressure &

# Set period for air pressure callback to 1s (1000ms) without a threshold
tinkerforge call barometer-v2-bricklet $uid set-air-pressure-callback-configuration 1000 false threshold-option-off 0 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
