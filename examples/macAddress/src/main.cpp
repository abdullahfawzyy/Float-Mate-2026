#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(500);  // Small delay to let Serial start
  WiFi.mode(WIFI_STA);
  // Print MAC address
  WiFi.begin();
  String macAddr = WiFi.macAddress();
  Serial.print("ESP32 MAC Address: ");
  Serial.println(macAddr);
}

void loop() {
  // Nothing needed here
}