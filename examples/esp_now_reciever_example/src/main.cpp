#include <WiFi.h>
#include <esp_now.h>

#define LED_PIN 2

void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  int state = *incomingData;

  digitalWrite(LED_PIN, state);

  Serial.print("Received ");
  Serial.println(state);

  Serial.print("From MAC: ");
  for (int i = 0; i < 6; i++) {
    Serial.printf("%02X:", mac[i]);
  }
  Serial.println();
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed!");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  Serial.println("Receiver Ready");
}

void loop() {
}
