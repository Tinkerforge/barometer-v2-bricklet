import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletBarometerV2;

public class ExampleThreshold {
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

		// Add air pressure listener
		b.addAirPressureListener(new BrickletBarometerV2.AirPressureListener() {
			public void airPressure(int airPressure) {
				System.out.println("Air Pressure: " + airPressure/1000.0 + " hPa");
				System.out.println("Enjoy the potentially good weather!");
			}
		});

		// Configure threshold for air pressure "greater than 1025 hPa"
		// with a debounce period of 1s (1000ms)
		b.setAirPressureCallbackConfiguration(1000, false, '>', 1025*1000, 0);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
