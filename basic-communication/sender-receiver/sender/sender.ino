#include <WiFi.h>
#include <esp_now.h>

#define BUTTON_PIN 0

uint8_t receiverMAC[] = {0x24, 0x6F, 0x28, 0xAA, 0xBB, 0xCC};

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);

  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW Init Failed");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  int state = digitalRead(BUTTON_PIN);

  esp_now_send(receiverMAC, (uint8_t *)&state, sizeof(state));

  delay(200);
}
