# Esp8266 Wifi Sniffer
This software is developed for the esp8266 TTGO 0.91 oled board.
The display shows the number of discovered access points and clients, and alerts the user with a sound.
You can also see the mac address of the client with the strongest signal.
Old mac addresses are removed from memory, the time interval is defined in the PURGETIME constant.

This device could be used for contact tracing, and help prevent the spread of COVID-19.

![Front of the board](https://i.imgur.com/k718CvT.jpg)

This project is based on the great work of Ray Burnette: https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a and Andreas Spiess https://github.com/SensorsIot/Wi-Fi-Sniffer-as-a-Human-detector

I designed a case to contain the board and a 18650 lithium battery.
You can find the stl files on thingiverse: https://www.thingiverse.com/thing:4361100

# Dependencies
You can install them with the Library Manager in Arduino IDE:

   - ESP8266 boards
   - U8g2lib ( https://github.com/olikraus/u8g2 )
