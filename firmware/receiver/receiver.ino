#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "taranis01";
const char *password = "11223344";

WiFiUDP g_udp;

const int g_port = 8888;
const int BUFF_SIZE = 512;
byte packetBuffer[BUFF_SIZE]; //buffer to hold incoming and outgoing packets

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void ledOFF() {
  digitalWrite(BUILTIN_LED, HIGH);
}

void ledON() {
  digitalWrite(BUILTIN_LED, LOW);
}

void toggleLED() {
  digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED));
}

void startWiFi() {
  ledON();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    toggleLED();
  }

  // start UDP server
  g_udp.begin(g_port);

  ledOFF();

  Serial.begin(57600, SERIAL_8N1);
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT); //Debug LED
  startWiFi();
}

void loop() {
  int noBytes = g_udp.parsePacket();
  if ( noBytes ) {
    int cnt = g_udp.read(packetBuffer, BUFF_SIZE); // read the packet into the buffer
    Serial.write(packetBuffer, cnt);
  }
}
