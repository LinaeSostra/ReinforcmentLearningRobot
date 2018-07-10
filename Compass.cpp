#include <Arduino.h>
#include "Compass.h"
#include "src/Adafruit_Sensor.h"
#include "src/Adafruit_LSM303_U.h"

/* Compass */

// Assigning a unique ID (12345) to the compass
Adafruit_LSM303_Accel_Unified accelometer = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

double xMagOffsetMin = 0.0;
double xMagOffsetMax = 0.0;
double yMagOffsetMin = 0.0;
double yMagOffsetMax = 0.0;

static double xAccel = 0.0;
static double yAccel = 0.0;
static double zAccel = 0.0;

static double xMag = 0.0;
static double yMag = 0.0;
static double zMag = 0.0;

void compassSetup() {
  // Enable auto-gain
  mag.enableAutoRange(true);

  // Initialize the sensor
  if(!accelometer.begin() || !mag.begin()) {
    // There was a problem detecting the ADXL345 ... check your connections
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
}

void gatherAccelometerValues() {
  // Get a new sensor event
  sensors_event_t event;
  accelometer.getEvent(&event);

  // Save the results (acceleration is measured in m/s^2)
  xAccel = event.acceleration.x;
  yAccel = event.acceleration.y;
  zAccel = event.acceleration.z;
}

void testAccelometerValues() {
  // Display the results (acceleration is measured in m/s^2)
  Serial.print("\nX: "); Serial.print(xAccel); Serial.print("  ");
  Serial.print("Y: "); Serial.print(yAccel); Serial.print("  ");
  Serial.print("Z: "); Serial.print(zAccel); Serial.print("  ");Serial.println("m/s^2 ");

  delay(500); // Delay for next sample
}

void gatherMagnetometerValues() {
  // Get a new sensor event;
  sensors_event_t event;
  mag.getEvent(&event);

  // Save the results (magnetic vector values are in micro-Tesla (uT))
  xMag = event.magnetic.x;
  yMag = event.magnetic.y;
  zMag = event.magnetic.z;
}

void testMageneticValues() {
  // Display the results (magnetic vector values are in micro-Tesla (uT))
  Serial.print("\nX: "); Serial.print(xMag); Serial.print("  ");
  Serial.print("Y: "); Serial.print(yMag); Serial.print("  ");
  Serial.print("Z: "); Serial.print(zMag); Serial.print("  ");Serial.println("uT");

  delay(500); // Delay for next sample 
}
