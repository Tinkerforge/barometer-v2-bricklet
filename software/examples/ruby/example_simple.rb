#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_barometer_v2'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Barometer Bricklet 2.0

ipcon = IPConnection.new # Create IP connection
b = BrickletBarometerV2.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get current air pressure
air_pressure = b.get_air_pressure
puts "Air Pressure: #{air_pressure/1000.0} hPa"

# Get current altitude
altitude = b.get_altitude
puts "Altitude: #{altitude/1000.0} m"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
