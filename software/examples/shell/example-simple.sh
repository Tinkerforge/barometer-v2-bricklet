#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Barometer Bricklet 2.0

# Get current air pressure
tinkerforge call barometer-v2-bricklet $uid get-air-pressure

# Get current altitude
tinkerforge call barometer-v2-bricklet $uid get-altitude
