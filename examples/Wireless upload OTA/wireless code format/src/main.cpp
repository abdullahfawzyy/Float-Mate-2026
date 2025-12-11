#include <Arduino.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

const char* ssid = "Abdullah";
const char* password = "helloworld";

#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  // 1. Connect to Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    ESP.restart();
  }

  // 2. Setup OTA (Must include this in every new code!)
  ArduinoOTA.setHostname("MyESP32");
  ArduinoOTA.begin();
}

void loop() {
  // CRITICAL LINE: Without this, you cannot upload wirelessly again!
  ArduinoOTA.handle(); 

  // Blink Logic (Using millis so we don't block OTA)
  static unsigned long previousMillis = 0;
  const long interval = 1000; 

  if (millis() - previousMillis >= interval) {
    previousMillis = millis();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }
}