#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletBarometerV2;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Barometer Bricklet 2.0

# Callback subroutine for air pressure callback
sub cb_air_pressure
{
    my ($air_pressure) = @_;

    print "Air Pressure: " . $air_pressure/1000.0 . " hPa\n";
}

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $b = Tinkerforge::BrickletBarometerV2->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Register air pressure callback to subroutine cb_air_pressure
$b->register_callback($b->CALLBACK_AIR_PRESSURE, 'cb_air_pressure');

# Set period for air pressure callback to 1s (1000ms) without a threshold
$b->set_air_pressure_callback_configuration(1000, 0, 'x', 0, 0);

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
