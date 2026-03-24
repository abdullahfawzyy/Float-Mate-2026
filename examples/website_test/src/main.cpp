#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoOTA.h>

// WIFI
const char* ssid = "Atalantis Float";
const char* password = "awal3alamisA";

// LED PINS
const int LED1 = 27;
const int LED2 = 26;
const int LED3 = 25;

// PUMP PINS
const int PUMP1 = 13;
const int PUMP2 = 14;

// WEB SERVER
WebServer server(80);

// HTML PAGE
String getHTML() {

  String html = "<!DOCTYPE html><html><head>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body{font-family:Arial;text-align:center;background:#f0f0f0;margin-top:40px;}";
  html += ".btn{display:block;width:80%;margin:12px auto;padding:18px;font-size:22px;color:white;border:none;border-radius:10px;text-decoration:none;}";
  html += ".on{background:#4CAF50;}";
  html += ".off{background:#f44336;}";
  html += ".pump{background:#2196F3;}";
  html += "</style></head><body>";

  html += "<h1>Atalantis Float</h1>";

  // LED 1
  html += "<h3>LED 1</h3>";
  html += "<a href='/led1on' class='btn on'>LED1 ON</a>";
  html += "<a href='/led1off' class='btn off'>LED1 OFF</a>";

  // LED 2
  html += "<h3>LED 2</h3>";
  html += "<a href='/led2on' class='btn on'>LED2 ON</a>";
  html += "<a href='/led2off' class='btn off'>LED2 OFF</a>";

  // LED 3
  html += "<h3>LED 3</h3>";
  html += "<a href='/led3on' class='btn on'>LED3 ON</a>";
  html += "<a href='/led3off' class='btn off'>LED3 OFF</a>";

  // Pump 1
  html += "<h3>PUMP 1</h3>";
  html += "<a href='/pump1on' class='btn pump'>PUMP1 ON</a>";
  html += "<a href='/pump1off' class='btn off'>PUMP1 OFF</a>";

  // Pump 2
  html += "<h3>PUMP 2</h3>";
  html += "<a href='/pump2on' class='btn pump'>PUMP2 ON</a>";
  html += "<a href='/pump2off' class='btn off'>PUMP2 OFF</a>";

  html += "</body></html>";

  return html;
}

// ROOT
void handleRoot() {
  server.send(200,"text/html",getHTML());
}

// LED CONTROL
void led1On(){ digitalWrite(LED1,HIGH); server.send(200,"text/html",getHTML()); }
void led1Off(){ digitalWrite(LED1,LOW); server.send(200,"text/html",getHTML()); }

void led2On(){ digitalWrite(LED2,HIGH); server.send(200,"text/html",getHTML()); }
void led2Off(){ digitalWrite(LED2,LOW); server.send(200,"text/html",getHTML()); }

void led3On(){ digitalWrite(LED3,HIGH); server.send(200,"text/html",getHTML()); }
void led3Off(){ digitalWrite(LED3,LOW); server.send(200,"text/html",getHTML()); }

// PUMP CONTROL
void pump1On(){ digitalWrite(PUMP1,HIGH); server.send(200,"text/html",getHTML()); }
void pump1Off(){ digitalWrite(PUMP1,LOW); server.send(200,"text/html",getHTML()); }

void pump2On(){ digitalWrite(PUMP2,HIGH); server.send(200,"text/html",getHTML()); }
void pump2Off(){ digitalWrite(PUMP2,LOW); server.send(200,"text/html",getHTML()); }

void setup() {

  Serial.begin(115200);

  // SET PIN MODES
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);

  pinMode(PUMP1,OUTPUT);
  pinMode(PUMP2,OUTPUT);

  // DEFAULT OFF
  digitalWrite(LED1,LOW);
  digitalWrite(LED2,LOW);
  digitalWrite(LED3,LOW);

  digitalWrite(PUMP1,LOW);
  digitalWrite(PUMP2,LOW);

  // WIFI ACCESS POINT
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid,password);

  Serial.print("IP: ");
  Serial.println(WiFi.softAPIP());

  // OTA
  ArduinoOTA.setHostname("Vortex Rangers Float");
  ArduinoOTA.setPassword("admin");
  ArduinoOTA.begin();

  // WEB ROUTES
  server.on("/",handleRoot);

  server.on("/led1on",led1On);
  server.on("/led1off",led1Off);

  server.on("/led2on",led2On);
  server.on("/led2off",led2Off);

  server.on("/led3on",led3On);
  server.on("/led3off",led3Off);

  server.on("/pump1on",pump1On);
  server.on("/pump1off",pump1Off);

  server.on("/pump2on",pump2On);
  server.on("/pump2off",pump2Off);

  server.begin();

  Serial.println("Server Started");
}

void loop() {

  ArduinoOTA.handle();
  server.handleClient();

}