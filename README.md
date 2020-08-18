# DevicesScannerEsp8266
This simple software controls the esp8266 TTGO 0.91 oled board.
It shows the number of discovered access points and clients, and alerts the user with a sound.
Additionally it shows the mac address of the client with the strongest signal.

![Front of the board](https://i.imgur.com/87fopMA.jpg)

This project is based on the great work of Ray Burnette: https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a and Andreas Spiess https://github.com/SensorsIot/Wi-Fi-Sniffer-as-a-Human-detector

I designed a case that contains the TTGO board and a 18650 lithium battery to make this device extremely portable.
You can find the stl files on thingiverse: https://www.thingiverse.com/thing:4361100

# Dependencies
You can install them with the Library Manager in Arduino IDE:

   - ESP8266 boards
   - U8g2lib ( https://github.com/olikraus/u8g2 )
