#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

const char *ssid = "taranis01";
const char *password = "11223344";

WiFiUDP g_udp;

const int g_port = 8888;
byte packetBuffer[512]; //buffer to hold incoming and outgoing packets

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}


void setup() {
  Serial.begin(57600, SERIAL_8N1);
  WiFi.begin(ssid, password);

//  Serial.print("[Connecting]");
//  Serial.print(ssid);
  int tries=0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    tries++;
    if (tries > 30){
      break;
    }
  }
//  Serial.println();  
//
//  printWifiStatus();
//
//  Serial.println("Connected to wifi");
//  Serial.print("Udp server started at port ");
//  Serial.println(g_port);

  // start UDP server
  g_udp.begin(g_port);
}

void loop() {
  int noBytes = g_udp.parsePacket();
  if ( noBytes ) {
    g_udp.read(packetBuffer,noBytes); // read the packet into the buffer

    Serial.write(packetBuffer, noBytes);
  }
}
