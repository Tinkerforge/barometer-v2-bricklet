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

# Register air pressure callback
b.register_callback(BrickletBarometerV2::CALLBACK_AIR_PRESSURE) do |air_pressure|
  puts "Air Pressure: #{air_pressure/1000.0} mbar"
  puts 'Enjoy the potentially good weather!'
end

# Configure threshold for air pressure "greater than 1025 mbar"
# with a debounce period of 1s (1000ms)
b.set_air_pressure_callback_configuration 1000, false, '>', 1025*1000, 0

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
