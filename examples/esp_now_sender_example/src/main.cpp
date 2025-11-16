#include <WiFi.h>
#include <esp_now.h>

#define BUTTON_PIN 0

// MAC address of the receiver ESP32
uint8_t receiverMAC[] = {0xE8, 0xDB, 0x84, 0x3C, 0x49, 0x94};

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Use internal pull-up

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
  int buttonState = digitalRead(BUTTON_PIN);
  int ledState = buttonState == LOW ? 1 : 0; // Pressed = 1, Not pressed = 0

  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *)&ledState, sizeof(ledState));

  if (result == ESP_OK) {
    Serial.println("Sent successfully");
  } else {
    Serial.println("Error sending");
  }

  delay(200); // debounce & limit sending rate
}
