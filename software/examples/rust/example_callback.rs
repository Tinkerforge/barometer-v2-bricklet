use std::{error::Error, io, thread};
use tinkerforge::{barometer_v2_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Barometer Bricklet 2.0.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let b = BarometerV2Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    // Create receiver for air pressure events.
    let air_pressure_receiver = b.get_air_pressure_receiver();

    // Spawn thread to handle received events. This thread ends when the `b` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for air_pressure in air_pressure_receiver {
            println!("Air Pressure: {} mbar", air_pressure as f32 / 1000.0);
        }
    });

    // Set period for air pressure callback to 1s (1000ms) without a threshold.
    b.set_air_pressure_callback_configuration(1000, false, 'x', 0, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
