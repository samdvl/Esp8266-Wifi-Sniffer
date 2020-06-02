# DevicesScannerEsp8266
This simple software controls the esp8266 TTGO 0.91 oled board.
It shows the number of discovered devices, access points and clients, on the screen and alerts the user with a buzzer.
Additionally it shows the mac address of the client with the strongest signal.

![Front of the board](https://i.imgur.com/87fopMA.jpg)

This board has a 390k resistor between 3.3v and Vdd of the oled lcd, that prevents the boot from flash once powered on and requires you to press the reset button.
To solve this issue you can simply remove it and solder a bridge instead.
It’s located on the back side, above the D6 print there are two capacitors and the following component is the 390k resistor.

![Back of the board](https://i.postimg.cc/MTfM9qKF/external-content-duckduckgo-com.jpg)

This project is based on the great work of Ray Burnette: https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a and Andreas Spiess https://github.com/SensorsIot/Wi-Fi-Sniffer-as-a-Human-detector

I designed a case that contains the TTGO board and a 18650 lithium battery to make this device extremely portable.
You can find the stl files on thingiverse: https://www.thingiverse.com/thing:4361100

# Dependencies
You can install them with the Library Manager in Arduino IDE:

   - ESP8266 boards
   - U8g2lib ( https://github.com/olikraus/u8g2 )
