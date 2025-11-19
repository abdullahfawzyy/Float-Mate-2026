#include <WiFi.h>
#include <esp_now.h>
#include <Wire.h>
#include "MS5837.h"
#include "RTClib.h"
#include <ArduinoJson.h>

MS5837 sensor;
RTC_DS3231 rtc;

// Receiver MAC address
uint8_t receiverAddress[] = {0xE8, 0xDB, 0x84, 0x3C, 0x49, 0x94};

char jsonBuffer[256];

// ------------------------
// ESP-NOW SEND CALLBACK
// ------------------------
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  // BAR30
  if (!sensor.init()) {
    Serial.println("MS5837 init failed!");
    while (1);
  }
  sensor.setFluidDensity(997);

  // RTC
  if (!rtc.begin()) {
    Serial.println("RTC init failed!");
    while (1);
  }

  // ESP-NOW
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  // Add receiver
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);
}

void loop() {
  sensor.read();
  DateTime now = rtc.now();

  JsonDocument doc;
  doc["time"] = now.timestamp(DateTime::TIMESTAMP_TIME);
  doc["pressure_mbar"] = sensor.pressure();
  doc["temperature_c"] = sensor.temperature();
  doc["depth_m"] = sensor.depth();
  doc["altitude_m"] = sensor.altitude();

  size_t len = serializeJson(doc, jsonBuffer);

  esp_now_send(receiverAddress, (uint8_t *)jsonBuffer, len);

  Serial.print("Sent JSON: ");
  Serial.println(jsonBuffer);

  delay(3000);
}
 