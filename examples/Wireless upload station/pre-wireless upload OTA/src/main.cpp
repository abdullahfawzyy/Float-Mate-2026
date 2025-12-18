#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
//Note: if you failed to upload multiple times what for the connecting message in the serial monitor and hold press the boot button
const char* ssid = "Abdullah";
const char* password = "helloworld";

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  // 1. Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // 2. Setup OTA
  ArduinoOTA.setHostname("MyESP32");
  ArduinoOTA.begin();

  // 3. Print IP Address (IMPORTANT)
  //reset the serial monitor to copy the IP address and will be used in the next code 
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle(); // Critical: keeps listening for updates
}