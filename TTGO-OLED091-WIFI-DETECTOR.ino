/*
  Copyright 2020 Simone Svanetti 

  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
  FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  This software is based on the work of Ray Burnette: https://www.hackster.io/rayburne/esp8266-mini-sniff-f6b93a and the work of Andreas Spiess https://github.com/SensorsIot/Wi-Fi-Sniffer-as-a-Human-detector
*/
#include <ESP8266WiFi.h>
#include "./functions.h"
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

//Pinout of the ttgo oled 0.91
#define OLED_SDA 2
#define OLED_SCL 14
#define OLED_RST 4
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, OLED_SCL, OLED_SDA , OLED_RST);
//Buzzer pin number
#define BUZZ 13
//Internal settings
#define disable 0
#define enable  1
//Scanned devices
#define MAXDEVICES 60
#define JBUFFER 15+ (MAXDEVICES * 40)
#define PURGETIME 350000

unsigned int channel = 1;

int clients_known_count_old = 0;
int aps_known_count_old = 0;
unsigned long sendEntry, deleteEntry;
char jsonString[JBUFFER];

String device[MAXDEVICES];
int nbrDevices = 0;
int usedChannels[15];

void setup() {
  //Initialize lcd screen
  Wire.begin( OLED_SDA, OLED_SCL);
  u8g2.begin();
  u8g2.setFont(u8g2_font_7x13B_mf);
  u8g2.setCursor(0, 14);
  u8g2.print("##WIFI DETECTOR##");
  u8g2.setCursor(0, 30);
  u8g2.print("Setup...");
  u8g2.sendBuffer(); 
  //Buzzer
  pinMode(BUZZ, OUTPUT);
  //Play setup intro
  tone(BUZZ, 750);
  delay(150);
  tone(BUZZ, 1800);
  delay(200);
  tone(BUZZ, 850);
  delay(150);
  noTone(BUZZ);
  //Serial setup
  Serial.begin(57600);
  Serial.printf("\n\nSDK version:%s\n\r", system_get_sdk_version());
  wifi_set_opmode(STATION_MODE);            // Promiscuous works only with station mode
  wifi_set_channel(channel);
  wifi_promiscuous_enable(disable);
  wifi_set_promiscuous_rx_cb(promisc_cb);   // Set up promiscuous callback
  wifi_promiscuous_enable(enable);
  u8g2.setCursor(0, 15);
  u8g2.print("Setup done!");
  u8g2.sendBuffer(); 
}

void loop() {
  channel = 1;
  wifi_set_channel(channel);
  while (true) {
    //scanning loop variables
    nothing_new++;                          // Array is not finite, check bounds and adjust if required
    if (nothing_new > 200) {
      nothing_new = 0;
      channel++;
      if (channel == 15) break;             // Only scan channels 1 to 14
      wifi_set_channel(channel);
    }
    delay(1);  // critical processing timeslice for NONOS SDK! No delay(0) yield()

    //Show results and notify user
    if (clients_known_count > clients_known_count_old) {
      clients_known_count_old = clients_known_count;
      showDevices();
      tone(BUZZ, 2200, 200);
      delay(25);
    } else if (clients_known_count < clients_known_count_old){
      clients_known_count_old = clients_known_count;
      showDevices();
      tone(BUZZ, 450, 200);
      delay(25);
    }
    if (aps_known_count > aps_known_count_old) {
      aps_known_count_old = aps_known_count;
      showDevices();
    } else if (aps_known_count < aps_known_count_old) {
      //the aps known are less
      aps_known_count_old = aps_known_count;
      showDevices();
    }
  }
  purgeDevice();
}

void purgeDevice() {
  for (int u = 0; u < clients_known_count; u++) {
    if ((millis() - clients_known[u].lastDiscoveredTime) > PURGETIME) {
      Serial.print("purge Client" );
      Serial.println(u);
      for (int i = u; i < clients_known_count; i++){
        memcpy(&clients_known[i], &clients_known[i + 1], sizeof(clients_known[i]));
      }
      clients_known_count--;
      break;
    }
  }
  for (int u = 0; u < aps_known_count; u++) {
    if ((millis() - aps_known[u].lastDiscoveredTime) > PURGETIME) {
      Serial.print("purge Beacon" );
      Serial.println(u);
      for (int i = u; i < aps_known_count; i++) memcpy(&aps_known[i], &aps_known[i + 1], sizeof(aps_known[i]));
      aps_known_count--;
      break;
    }
  }
}

void showDevices() {
  Serial.println("");
  Serial.println("");
  Serial.println("-------------------Device DB-------------------");
  Serial.printf("%4d Devices + Clients.\n",aps_known_count + clients_known_count); // show count
  //Print counters on lcd
  u8g2.clearBuffer();  
  u8g2.setCursor(0, 14);
  u8g2.print("AP: ");
  u8g2.setCursor(20, 14);
  u8g2.print(aps_known_count);
  u8g2.setCursor(40, 14);
  u8g2.print("CL: ");
  u8g2.setCursor(60, 14);
  u8g2.print(clients_known_count);
  //Show Beacons
  for (int u = 0; u < aps_known_count; u++) {
    Serial.printf( "%4d ",u); // Show beacon number
    Serial.print("B ");
    Serial.print(formatMac1(aps_known[u].bssid));
    Serial.print(" RSSI ");
    Serial.print(aps_known[u].rssi);
    Serial.print(" channel ");
    Serial.println(aps_known[u].channel);
  }
  
  //Find strongest client signal while printing in serial console
  int maxClientIndex = 0;
  int maxClientRssi = -200;
  //Show Clients
  for (int u = 0; u < clients_known_count; u++) {
    //Check for max rssi
    if (maxClientRssi < clients_known[u].rssi){
      maxClientRssi = clients_known[u].rssi;
      maxClientIndex = u;
    }
    Serial.printf("%4d ",u); // Show client number
    Serial.print("C ");
    Serial.print(formatMac1(clients_known[u].station));
    Serial.print(" RSSI ");
    Serial.print(clients_known[u].rssi);
    Serial.print(" channel ");
    Serial.println(clients_known[u].channel);
  }
  //Add max rssi
  u8g2.setCursor(80, 14);
  u8g2.print("RS: ");
  u8g2.setCursor(100, 14);
  u8g2.print(maxClientRssi);
  //Add strongest mac address
  u8g2.setCursor(1, 30);
  u8g2.print(formatMac1(clients_known[maxClientIndex].station));
  //Send data to oled
  u8g2.sendBuffer();
}
