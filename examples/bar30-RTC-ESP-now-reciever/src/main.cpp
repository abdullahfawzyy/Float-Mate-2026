#include <WiFi.h>
#include <esp_now.h>
#include <ArduinoJson.h>

// ------------------------
// ESP-NOW RECEIVE CALLBACK
// ------------------------
void onDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  Serial.print("Received JSON: ");
  Serial.write(incomingData, len);
  Serial.println();

  JsonDocument doc;
  DeserializationError error = deserializeJson(doc, incomingData, len);

  if (error) {
    Serial.print("JSON Parse Error: ");
    Serial.println(error.c_str());
    return;
  }

  const char* time = doc["time"];
  float pressure = doc["pressure_mbar"];
  float temp = doc["temperature_c"];
  float depth = doc["depth_m"];
  float altitude = doc["altitude_m"];

  Serial.println("--- Parsed Data ---");
  Serial.print("Time: ");     Serial.println(time);
  Serial.print("Pressure: "); Serial.println(pressure);
  Serial.print("Temp: ");     Serial.println(temp);
  Serial.print("Depth: ");    Serial.println(depth);
  Serial.print("Altitude: "); Serial.println(altitude);
  Serial.println("-------------------");
}

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed!");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);

  Serial.println("Receiver Ready.");
}

void loop() {}
