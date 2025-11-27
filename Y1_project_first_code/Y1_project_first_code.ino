#define MQ135_PIN 32  // ADC1 channel 4
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1023.6)
Adafruit_BME280 bme; // I2C

void setup() {
  Serial.begin(115200);
   if (!bme.begin(0x76)) { // Check I2C address
   Serial.println("Could not find a valid BME280 sensor, check wiring!");
   while (1);
 }
  delay(2000);
  analogReadResolution(12); // ESP32 ADC = 12-bit (0–4095)
  Serial.print("Sensor ID: ");
Serial.println(bme.sensorID(), 16);
}

void loop() {
  int rawValue = analogRead(MQ135_PIN);
  Serial.print("Raw MQ135 Value: ");
  Serial.println(rawValue);
  delay(1000);
 Serial.print("Temperature = ");
 Serial.print(bme.readTemperature());
 Serial.println(" °C");
 Serial.print("Humidity = ");
 Serial.print(bme.readHumidity());
 Serial.println(" %");
 Serial.print("Pressure = ");
 Serial.print(bme.readPressure() / 100.0F);
 Serial.println(" hPa");
 Serial.print("Altitude = ");
 Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
 Serial.println(" m");
 delay(2000);
}