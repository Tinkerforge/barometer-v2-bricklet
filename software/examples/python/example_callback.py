#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Barometer Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_barometer_v2 import BrickletBarometerV2

# Callback function for air pressure callback
def cb_air_pressure(air_pressure):
    print("Air Pressure: " + str(air_pressure/1000.0) + " hPa")

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    b = BrickletBarometerV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Register air pressure callback to function cb_air_pressure
    b.register_callback(b.CALLBACK_AIR_PRESSURE, cb_air_pressure)

    # Set period for air pressure callback to 1s (1000ms) without a threshold
    b.set_air_pressure_callback_configuration(1000, False, "x", 0, 0)

    input("Press key to exit\n") # Use raw_input() in Python 2
    ipcon.disconnect()
