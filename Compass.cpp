#include <Arduino.h>
#include "Compass.h"
#include "Motors.h"
#include "src/Adafruit_Sensor.h"
#include "src/Adafruit_LSM303_U.h"

/* Compass */

int compassDirection; // 0 - 359 degrees

// Assigning a unique ID (12345) to the compass
Adafruit_LSM303_Accel_Unified accelometer = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Mag_Unified magnetometer = Adafruit_LSM303_Mag_Unified(12345);

const double error = 1e-2;

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
  magnetometer.enableAutoRange(true);

  // Initialize the sensor
  if(!accelometer.begin() || !magnetometer.begin()) {
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

void gatherMagnetometerReadings() {
  // Get a new sensor event;
  sensors_event_t event;
  magnetometer.getEvent(&event);

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

void updateMagnetometerOffsets() {
  if( xMagOffsetMin > xMag ) {
    xMagOffsetMin = xMag;
  }
  if( xMagOffsetMax < xMag ) {
    xMagOffsetMax = xMag;
  }
  if( yMagOffsetMin > yMag ) {
    yMagOffsetMin = yMag;
  }
  if( yMagOffsetMax < yMag ) {
    yMagOffsetMax = yMag;
  }
}

bool checkCompletedCalibration() {
  return ((abs(xMag - xMagOffsetMin) < error) && (abs(yMag - yMagOffsetMin) < error));
}

// Spins the robot to calibrate the max/min magnetic readings for location, and stop the robot at min mag x & y values
void calibrateMagneticReadings() {
  // If ran for the first time since bootup, set the offsets to initial readings, and start from there
  bool ifOffsetsNotCalibrated = xMagOffsetMin == 0.0 || yMagOffsetMin == 0.0 || xMagOffsetMax == 0.0 || yMagOffsetMax == 0.0;
  if(ifOffsetsNotCalibrated) {
    gatherMagnetometerReadings();
  
    xMagOffsetMin = xMag;
    xMagOffsetMax = xMag;
    yMagOffsetMin = yMag;
    yMagOffsetMax = yMag;
  }
  bool hasFinishedCalibration = false;
  while(!hasFinishedCalibration) {
    moveCCW();
    delay(10);
    gatherMagnetometerReadings();
    hasFinishedCalibration = checkCompletedCalibration();
    updateMagnetometerOffsets();
  }
}

// Updates the direction of the robot
void updateDirection() {
  compassDirection = -1;
}

/* Getters */
// Gets the direction of the robot
int getDirection() {
  return compassDirection;
}
