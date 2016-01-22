#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

/* Set these to your desired credentials. */
const char *ssid = "taranis01";
const char *password = "11223344";

WiFiUDP g_udp;

const int PACKAGE_SIZE = 32;
int cnt = 0;

const int g_port = 8888;
IPAddress ip;

void setup()
{
  WiFi.softAP(ssid, password);
  Serial.begin(57600, SERIAL_8N1);

  // start UDP server
  g_udp.begin(g_port);

  ip = WiFi.softAPIP();
  ip[3] = 255;

  // start new package
  g_udp.beginPacket(ip, g_port);
}

void loop()
{
  // has data - add to packet
  if (Serial.available()) {
    g_udp.write(Serial.read());
    cnt ++;
  }
  
  if (cnt >= PACKAGE_SIZE) {
    // transmit package
    g_udp.endPacket();
    cnt = 0;

    // start new package
    g_udp.beginPacket(ip, g_port);
  }
}

