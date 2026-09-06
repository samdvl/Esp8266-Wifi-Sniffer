# ESP8266 Wi-Fi Sniffer

A portable Wi-Fi device detector built on the **TTGO ESP8266 0.91" OLED** board.
It scans nearby Wi-Fi devices passively, displays live counts on the OLED screen,
and alerts the user with a buzzer when new devices are detected.

<p align="center">
  <img src="https://camo.githubusercontent.com/.../k718CvT.jpg" width="300"/>
</p>

## ✨ Features

- 📡 Passive scanning of nearby Wi-Fi **access points and clients**
- 🖥️ Live display on TTGO 0.91" OLED: AP and client counts
- 🔊 Buzzer alert on new device detection
- 📍 MAC address of the client with the strongest signal
- 🧹 Automatic cleanup of stale MAC addresses from memory (configurable via `PURGETIME`)
- 🔋 Runs on a single **18650 lithium cell** in a custom 3D-printed case

## 💡 Use cases

Originally developed during the COVID-19 pandemic as a **contact-tracing aid**:
detecting how many Wi-Fi devices (and therefore people) were present in a room,
helping to prevent overcrowding and virus spread.

It can also be used for:
- Occupancy counting in rooms and public spaces
- Wi-Fi site surveys and discovery
- Educational projects on the ESP8266 promiscuous/sniffer mode

> ⚠️ **Ethical notice:** this tool only collects publicly broadcast MAC addresses.
> Use it responsibly and in compliance with local privacy regulations (e.g. GDPR in the EU).

## 🧰 Hardware

| Component | Notes |
|---|---|
| TTGO ESP8266 0.91" OLED board | Main controller + display |
| Passive buzzer | Audio alert (tones defined in `Notes.h`) |
| 18650 lithium battery | Power supply |

📦 **Case STL files** (board + 18650 holder): [Thingiverse #4361100](https://www.thingiverse.com/thing:4361100)

## 🔧 Build & Flash

1. Open `TTGO-OLED091-WIFI-DETECTOR.ino` in the **Arduino IDE**
2. Install the required libraries via *Library Manager* (see [Dependencies](#dependencies))
3. Select your board and flash
4. Power the device via battery or USB

### Dependencies

<!-- TODO: list the libraries here, e.g. -->
- ESP8266WiFi (Arduino core)
- SSD1306 / U8g2 (OLED driver)

## 📁 Project Structure

| File | Purpose |
|---|---|
| `TTGO-OLED091-WIFI-DETECTOR.ino` | Main sketch — setup & scan loop |
| `functions.h` | Scan, display and alert logic |
| `structures.h` | Data structures for APs/clients |
| `Notes.h` | Buzzer tones |

## 🙏 Credits

This project builds upon the excellent work of:

- **Ray Burnette** — [ESP8266 Mini Sniff](https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a)
- **Andreas Spiess** — [Wi-Fi Sniffer as a Human Detector](https://github.com/SensorsIot/Wi-Fi-Sniffer-as-a-Human-detector)

## 📄 License

See [LICENSE](LICENSE).
   - ESP8266 boards
   - U8g2lib ( https://github.com/olikraus/u8g2 )
