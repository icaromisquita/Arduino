# Arduino
My bachelor final project using a Arduino MEGA 2560 - Made in 2017

The function of this program is to obtain and save data from the LM35 (temperature), DHT 11 (humidity), and the LDR (brightness) sensors and save them to an SD card.

     The circuit
   LM35 sensors connected to analog ports A0 to A6
 * * Powered by the VIN port

   LDR sensor connected to ports A12
   DHT11 sensors connected to digital ports 2 to 6

    SD card
 * Port 50 MISO pin
 * Port 51 MOSI pin
 * Port 52 SCK pin
 * Port 53 CS pin
 * Powered by port 5V
   All connected to ground pin GND

There is a image describing the wiring of the project.

The comments on the code are all in Brazilian Portuguese.
