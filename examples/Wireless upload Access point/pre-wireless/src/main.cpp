#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "secret.h"

// --- CONFIGURATION ---
const char* ap_ssid = "Vortex Rangers Float";  // Name of the Network
const char* ap_password = SECRET_PASS; // Password to Join

void setup() {
  Serial.begin(115200);
  Serial.println("Booting...");

  // 1. Create Access Point (The ESP32 becomes the Router)
  WiFi.mode(WIFI_AP); // AP Mode
  WiFi.softAP(ap_ssid, ap_password);

  Serial.println("\nAccess Point Created!");
  Serial.print("Network Name: ");
  Serial.println(ap_ssid);
  
  // 2. Print the IP Address (It is usually 192.168.4.1)
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // 3. Setup OTA
  ArduinoOTA.setHostname("MyESP32_ROV");
  
  // Optional: Add a second password specifically for the Upload itself
  // ArduinoOTA.setPassword("admin"); 

  ArduinoOTA.begin();
}

void loop() {
  // CRITICAL: Keep listening for uploads
  ArduinoOTA.handle(); 
  
  // Simple Blink to show it's running
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 1000) {
    lastBlink = millis();
    digitalWrite(2, !digitalRead(2)); // Toggle Built-in LED
  }
}