#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

// sometimes the serial monitor wont give you the max address so press the 
//EN button in the ESP 
void setup() {
  Serial.begin(115200);
  delay(500);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();       // ensure WiFi is not connected yet
  delay(100);

  Serial.print("ESP32 MAC Address (sta): ");
  uint8_t mac[6];
  if (esp_wifi_get_mac(WIFI_IF_STA, mac) == ESP_OK) {
    char macStr[18];
    sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X",
                     mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
    Serial.println(macStr);
  } else {
    Serial.println("Failed to read MAC address");
  }
}

void loop() {
  // nothing needed
}
