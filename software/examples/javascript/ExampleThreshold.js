var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Barometer Bricklet 2.0

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var b = new Tinkerforge.BrickletBarometerV2(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Configure threshold for air pressure "greater than 1025 mbar"
        // with a debounce period of 1s (1000ms)
        b.setAirPressureCallbackConfiguration(1000, false, '>', 1025*1000, 0);
    }
);

// Register air pressure callback
b.on(Tinkerforge.BrickletBarometerV2.CALLBACK_AIR_PRESSURE,
    // Callback function for air pressure callback
    function (airPressure) {
        console.log('Air Pressure: ' + airPressure/1000.0 + ' mbar');
        console.log('Enjoy the potentially good weather!');
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
