function matlab_example_callback()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletBarometerV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Barometer Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    b = handle(BrickletBarometerV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register air pressure callback to function cb_air_pressure
    set(b, 'AirPressureCallback', @(h, e) cb_air_pressure(e));

    % Set period for air pressure callback to 1s (1000ms) without a threshold
    b.setAirPressureCallbackConfiguration(1000, false, 'x', 0, 0);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for air pressure callback
function cb_air_pressure(e)
    fprintf('Air Pressure: %g hPa\n', e.airPressure/1000.0);
end
