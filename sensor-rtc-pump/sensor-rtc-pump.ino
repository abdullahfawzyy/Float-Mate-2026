#include <MS5837.h>

#include <Wire.h>
#include "MS5837.h"
#include "RTClib.h"

MS5837 sensor;
RTC_DS3231 rtc;

const int IN1 = 18;
const int IN2 = 19;
const int ENA = 23;

const int freq = 5000;    
const int resolution = 8;  
int pwmChannel;             

void pumpOn(int speed) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  ledcWrite(pwmChannel, speed); 
  Serial.println("Pump: ON");
}

void pumpOff() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  ledcWrite(pwmChannel, 0);    
  Serial.println("Pump: OFF");
}

void readProfile() {
  sensor.read();
  DateTime now = rtc.now();

  Serial.print("Time: ");
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.println(now.second());

  Serial.print("Pressure: ");
  Serial.print(sensor.pressure()); 
  Serial.println(" mbar");

  Serial.print("Temperature: ");
  Serial.print(sensor.temperature()); 
  Serial.println(" deg C");

  Serial.print("Depth: ");
  Serial.print(sensor.depth()); 
  Serial.println(" m");

  Serial.print("Altitude: ");
  Serial.print(sensor.altitude()); 
  Serial.println(" m above mean sea level");

  pumpOn(200);
  delay(1000);
  pumpOff();

  Serial.println("-------------------------");
}

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!sensor.init()) {
    Serial.println("Pressure Sensor init failed!");
    while (1);
  }
  sensor.setFluidDensity(997);

  if (!rtc.begin()) {
    Serial.println("RTC init failed!");
    while (1);
  }
  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pwmChannel = ledcAttach(ENA, freq, resolution);
  pumpOff();
}

void loop() {
  readProfile();
  delay(3000);
}

