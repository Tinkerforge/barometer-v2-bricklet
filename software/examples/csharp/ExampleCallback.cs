using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Barometer Bricklet 2.0

	// Callback function for air pressure callback
	static void AirPressureCB(BrickletBarometerV2 sender, int airPressure)
	{
		Console.WriteLine("Air Pressure: " + airPressure/1000.0 + " mbar");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletBarometerV2 b = new BrickletBarometerV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register air pressure callback to function AirPressureCB
		b.AirPressureCallback += AirPressureCB;

		// Set period for air pressure callback to 1s (1000ms) without a threshold
		b.SetAirPressureCallbackConfiguration(1000, false, 'x', 0, 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
