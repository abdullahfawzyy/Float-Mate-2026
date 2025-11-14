#include "WiFi.h"
//This code is used to find the mac address of an ESP 
void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_MODE_STA);
  //In case you got an all 00 MAC address uncomment the following line 
  //delay(1000);
  Serial.print("MAC Address: ");
  Serial.println(WiFi.macAddress());
}

void loop() {

}