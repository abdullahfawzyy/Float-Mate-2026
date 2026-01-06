#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <WebServer.h>
#include <secret.h>

const char* ssid = "Vortex Rangers Float";
const char* password = WIFI_PASSWORD;

WebServer server(80);

// --- PUMP 1 (Kept same) ---
const int IN1 = 19;
const int IN2 = 18;
const int PWM1_PIN = 23;

// --- PUMP 2 (CHANGED TO SAFE PINS) ---
const int IN3 = 27; // Was 17
const int IN4 = 26; // Was 16
const int PWM2_PIN = 4;

// PWM Properties
const int freq = 5000;
const int resolution = 8;
const int PWM1_CH = 0;
const int PWM2_CH = 1;

// HTML Page
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { font-family: Arial; text-align: center; margin-top: 50px; background-color: #f2f2f2; }
    h1 { color: #333; }
    .button { display: block; width: 200px; background-color: #4CAF50; border: none; color: white; padding: 20px;
              text-align: center; text-decoration: none; font-size: 20px; margin: 20px auto; cursor: pointer; border-radius: 10px; }
    .button-out { background-color: #008CBA; } 
    .button-stop { background-color: #f44336; }
    .button:active { background-color: #3e8e41; transform: translateY(2px); }
  </style>
</head>
<body>
  <h1>Vortex Rangers Control</h1>
  <a href="/in"><button class="button">PUMP IN (Pump 1)</button></a>
  <a href="/out"><button class="button button-out">PUMP OUT (Pump 2)</button></a>
  <a href="/stop"><button class="button button-stop">STOP ALL</button></a>
</body>
</html>
)rawliteral";

void stopAll() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(PWM1_CH, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  ledcWrite(PWM2_CH, 0);
}

void handleRoot() {
  server.send(200, "text/html", index_html);
}

void handlePumpIn() {
  stopAll(); 
  // Turn Pump 1 ON
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  ledcWrite(PWM1_CH, 255);
  
  server.sendHeader("Location", "/");
  server.send(303);
}

void handlePumpOut() {
  stopAll();
  // Turn Pump 2 ON
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  ledcWrite(PWM2_CH, 255);

  server.sendHeader("Location", "/");
  server.send(303);
}

void handleStop() {
  stopAll();
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  Serial.begin(115200);

  // Setup Pins (Including PWM pins as output for safety)
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(PWM1_PIN, OUTPUT);
  pinMode(PWM2_PIN, OUTPUT);

  // Setup PWM
  ledcSetup(PWM1_CH, freq, resolution);
  ledcSetup(PWM2_CH, freq, resolution);
  ledcAttachPin(PWM1_PIN, PWM1_CH);
  ledcAttachPin(PWM2_PIN, PWM2_CH);

  stopAll();

  // Setup WiFi
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  // Setup OTA
  ArduinoOTA.setHostname("Vortex Rangers float");
  ArduinoOTA.begin();

  // Setup Web Server
  server.on("/", handleRoot);
  server.on("/in", handlePumpIn);
  server.on("/out", handlePumpOut);
  server.on("/stop", handleStop);

  server.begin();
  Serial.println("System Ready. Connect to 'Vortex Rangers Float'");
}

void loop() {
  ArduinoOTA.handle();
  server.handleClient();
}