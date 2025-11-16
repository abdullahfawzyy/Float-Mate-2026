#include <Arduino.h>
#include <Wire.h>
#include <MS5837.h>

// Create sensor object
MS5837 sensor;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println("Starting Bar30 (MS5837) test...");

    // Start I2C for ESP32
    // SDA = 21, SCL = 22  (DEFAULT ESP32 PINS)
    Wire.begin(21, 22); 

    if (!sensor.init()) {
        Serial.println("ERROR: Could not initialize the MS5837 sensor!");
        while (1) delay(10);
    }

    // Tell library we are using Bar30 (30 bar model)
    sensor.setModel(MS5837::MS5837_30BA);

    // Freshwater density = 997 kg/m^3, seawater ~1029
    sensor.setFluidDensity(997);

    Serial.println("MS5837 sensor initialized successfully.");
}

void loop() {

    sensor.read();   // Read sensor latest values

    Serial.print("Pressure (mbar): ");
    Serial.print(sensor.pressure());
    Serial.print("\t Temperature (C): ");
    Serial.print(sensor.temperature());
    Serial.print("\t Depth (m): ");
    Serial.println(sensor.depth());

    delay(500);
}
