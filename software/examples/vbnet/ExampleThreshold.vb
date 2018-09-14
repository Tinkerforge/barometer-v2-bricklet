Imports System
Imports Tinkerforge

Module ExampleThreshold
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Barometer Bricklet 2.0

    ' Callback subroutine for air pressure callback
    Sub AirPressureCB(ByVal sender As BrickletBarometerV2, ByVal airPressure As Integer)
        Console.WriteLine("Air Pressure: " + (airPressure/1000.0).ToString() + " mbar")
        Console.WriteLine("Enjoy the potentially good weather!")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim b As New BrickletBarometerV2(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register air pressure callback to subroutine AirPressureCB
        AddHandler b.AirPressureCallback, AddressOf AirPressureCB

        ' Configure threshold for air pressure "greater than 1025 mbar"
        ' with a debounce period of 1s (1000ms)
        b.SetAirPressureCallbackConfiguration(1000, False, ">"C, 1025*1000, 0)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
