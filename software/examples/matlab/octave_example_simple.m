function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Barometer Bricklet 2.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    b = javaObject("com.tinkerforge.BrickletBarometerV2", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current air pressure
    airPressure = b.getAirPressure();
    fprintf("Air Pressure: %g hPa\n", airPressure/1000.0);

    % Get current altitude
    altitude = b.getAltitude();
    fprintf("Altitude: %g m\n", altitude/1000.0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end
