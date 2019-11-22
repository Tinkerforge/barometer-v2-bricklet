<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletBarometerV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletBarometerV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Barometer Bricklet 2.0

$ipcon = new IPConnection(); // Create IP connection
$b = new BrickletBarometerV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Get current air pressure
$air_pressure = $b->getAirPressure();
echo "Air Pressure: " . $air_pressure/1000.0 . " hPa\n";

// Get current altitude
$altitude = $b->getAltitude();
echo "Altitude: " . $altitude/1000.0 . " m\n";

echo "Press key to exit\n";
fgetc(fopen('php://stdin', 'r'));
$ipcon->disconnect();

?>
