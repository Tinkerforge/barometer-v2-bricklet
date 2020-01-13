#!/usr/bin/env python
# -*- coding: utf-8 -*-

HOST = "localhost"
PORT = 4223
UID = "XYZ" # Change XYZ to the UID of your Barometer Bricklet 2.0

from tinkerforge.ip_connection import IPConnection
from tinkerforge.bricklet_barometer_v2 import BrickletBarometerV2

if __name__ == "__main__":
    ipcon = IPConnection() # Create IP connection
    b = BrickletBarometerV2(UID, ipcon) # Create device object

    ipcon.connect(HOST, PORT) # Connect to brickd
    # Don't use device before ipcon is connected

    # Get current air pressure
    air_pressure = b.get_air_pressure()
    print("Air Pressure: " + str(air_pressure/1000.0) + " hPa")

    # Get current altitude
    altitude = b.get_altitude()
    print("Altitude: " + str(altitude/1000.0) + " m")

    input("Press key to exit\n") # Use raw_input() in Python 2
    ipcon.disconnect()
