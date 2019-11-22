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
		Console.WriteLine("Air Pressure: " + airPressure/1000.0 + " hPa");
		Console.WriteLine("Enjoy the potentially good weather!");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletBarometerV2 b = new BrickletBarometerV2(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register air pressure callback to function AirPressureCB
		b.AirPressureCallback += AirPressureCB;

		// Configure threshold for air pressure "greater than 1025 hPa"
		// with a debounce period of 1s (1000ms)
		b.SetAirPressureCallbackConfiguration(1000, false, '>', 1025*1000, 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
