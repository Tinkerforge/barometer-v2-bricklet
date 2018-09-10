<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletBarometerV2.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletBarometerV2;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Barometer Bricklet 2.0

// Callback function for air pressure callback
function cb_airPressure($air_pressure)
{
    echo "Air Pressure: " . $air_pressure/1000.0 . " mbar\n";
    echo "Enjoy the potentially good weather!\n";
}

$ipcon = new IPConnection(); // Create IP connection
$b = new BrickletBarometerV2(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register air pressure callback to function cb_airPressure
$b->registerCallback(BrickletBarometerV2::CALLBACK_AIR_PRESSURE, 'cb_airPressure');

// Configure threshold for air pressure "greater than 1025 mbar"
// with a debounce period of 1s (1000ms)
$b->setAirPressureCallbackConfiguration(1000, FALSE, '>', 1025*1000, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
