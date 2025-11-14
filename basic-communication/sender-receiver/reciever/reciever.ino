#include <WiFi.h>
#include <esp_now.h>

#define LED_PIN 2

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  int state = *incomingData;
  digitalWrite(LED_PIN, state);

  Serial.print("Received state: ");
  Serial.println(state);
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
}