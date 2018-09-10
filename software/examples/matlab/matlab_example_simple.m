function matlab_example_simple()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletBarometerV2;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Barometer Bricklet 2.0

    ipcon = IPConnection(); % Create IP connection
    b = handle(BrickletBarometerV2(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current air pressure
    airPressure = b.getAirPressure();
    fprintf('Air Pressure: %g mbar\n', airPressure/1000.0);

    % Get current altitude
    altitude = b.getAltitude();
    fprintf('Altitude: %g m\n', altitude/1000.0);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end
