import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletBarometerV2;

public class ExampleSimple {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Barometer Bricklet 2.0
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletBarometerV2 b = new BrickletBarometerV2(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Get current air pressure
		int airPressure = b.getAirPressure(); // Can throw com.tinkerforge.TimeoutException
		System.out.println("Air Pressure: " + airPressure/1000.0 + " mbar");

		// Get current altitude
		int altitude = b.getAltitude(); // Can throw com.tinkerforge.TimeoutException
		System.out.println("Altitude: " + altitude/1000.0 + " m");

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
