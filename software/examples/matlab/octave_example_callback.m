function octave_example_callback()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Barometer Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    b = javaObject("com.tinkerforge.BrickletBarometerV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register air pressure callback to function cb_air_pressure
    b.addAirPressureCallback(@cb_air_pressure);

    % Set period for air pressure callback to 1s (1000ms) without a threshold
    b.setAirPressureCallbackConfiguration(1000, false, "x", 0, 0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for air pressure callback
function cb_air_pressure(e)
    fprintf("Air Pressure: %g hPa\n", e.airPressure/1000.0);
end
