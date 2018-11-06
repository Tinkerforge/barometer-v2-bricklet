use std::{error::Error, io, thread};
use tinkerforge::{barometer_v2_bricklet::*, ipconnection::IpConnection};

const HOST: &str = "127.0.0.1";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Barometer Bricklet 2.0

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection
    let barometer_v2_bricklet = BarometerV2Bricklet::new(UID, &ipcon); // Create device object

    ipcon.connect(HOST, PORT).recv()??; // Connect to brickd
                                        // Don't use device before ipcon is connected

    //Create listener for air pressure events.
    let air_pressure_listener = barometer_v2_bricklet.get_air_pressure_receiver();
    // Spawn thread to handle received events. This thread ends when the barometer_v2_bricklet
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for event in air_pressure_listener {
            println!("Air Pressure: {}{}", event as f32 / 1000.0, " mbar");
            println!("Enjoy the potentially good weather!");
        }
    });

    // Configure threshold for air pressure "greater than 1025 mbar"
    // with a debounce period of 1s (1000ms)
    barometer_v2_bricklet.set_air_pressure_callback_configuration(1000, false, '>', 1025 * 1000, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
