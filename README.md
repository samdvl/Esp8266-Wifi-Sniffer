# DevicesScannerEsp8266
This simple software contols the esp8266 TTGO 0.91 oled board.
It shows the number of discovered devices, access points and clients, on the screen and alerts the user with a buzzer.
Addittionally it display the mac address of the client with the strongest signal.

This project is based on the great work of both Ray Burnette: https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a and Andreas Spiess https://github.com/SensorsIot/Wi-Fi-Sniffer-as-a-Human-detector

I also designed a case that contains the ttgo board and a 18650 battery to make this device extremely portable.
You can find the stl files on thingiverse: https://www.thingiverse.com/thing:4361100

# Dependencies
You can install them with the Library Manager in Arduino IDE:

   - ESP8266 boards
   - U8g2lib ( https://github.com/olikraus/u8g2 )
