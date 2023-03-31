#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

void setup() {
  Serial.begin(9600);
  if(!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor!");
    while(1);
  }
}

void loop() {
  sensors_event_t event;
  accel.getEvent(&event);
  Serial.print("X: ");
  Serial.print(event.acceleration.x);
  Serial.print(" Y: ");
  Serial.print(event.acceleration.y);
  Serial.print(" Z: ");
  Serial.println(event.acceleration.z);

   delay(120);

}
