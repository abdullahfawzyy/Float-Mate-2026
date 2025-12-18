#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "Vortex Rangers Float";
const char* password = "ew3aweshak";

void setup() {
  pinMode(2, OUTPUT);
  Serial.begin(115200);

  // Create the Network
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  // Setup OTA
  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle(); // Keep wireless upload alive
  
  digitalWrite(2, HIGH);
  delay(200);
  digitalWrite(2, LOW);
  delay(200);
}