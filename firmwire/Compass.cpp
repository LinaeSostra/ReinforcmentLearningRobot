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

const double error = 5.0;

double xMagOffsetMin = 300.0;
double xMagOffsetMax = 321.0;
double yMagOffsetMin = -98.0;
double yMagOffsetMax = -77.0;

double xMagOffset = 310.5;
double yMagOffset = -87.5;

static double xAccel = 0.0;
static double yAccel = 0.0;
static double zAccel = 0.0;

static double xMag = 0.0;
static double yMag = 0.0;
static double zMag = 0.0;

void compassSetup() {
  // Enable auto-gain
  magnetometer.enableAutoRange(true);
  //magnetometer.setMagGain(LSM303_MAGGAIN_8_1);

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

void testMagneticValues() {
  // Display the results (magnetic vector values are in micro-Tesla (uT))
  Serial.print("\nX: "); Serial.print(xMag); Serial.print("  ");
  Serial.print("Y: "); Serial.print(yMag); Serial.print("  ");
  Serial.print("Z: "); Serial.print(zMag); Serial.print("  ");Serial.println("uT");

  delay(500); // Delay for next sample 
}

void printMagneticValues() {
  // Display what the x and y min,max, and current magenetic values are
  Serial.print("\nX Max: "); Serial.print(xMagOffsetMax); Serial.print(", X Min: "); Serial.print(xMagOffsetMin); Serial.print(", X: "); Serial.println(xMag);
  Serial.print("\nY Max: "); Serial.print(yMagOffsetMax); Serial.print(", Y Min: "); Serial.print(yMagOffsetMin); Serial.print(", Y: "); Serial.println(yMag);
}

void updateMagnetometerOffsets() {
  if( (xMagOffsetMin > xMag || xMagOffsetMin == 0) && abs(xMag) < 1000.0) {
    xMagOffsetMin = xMag;
  }
  if( (xMagOffsetMax < xMag || xMagOffsetMax == 0) && abs(xMag) < 1000.0) {
    xMagOffsetMax = xMag;
  }
  if( (yMagOffsetMin > yMag || yMagOffsetMin == 0.0) && abs(yMag) < 250.0) {
    yMagOffsetMin = yMag;
  }
  if( (yMagOffsetMax < yMag || yMagOffsetMax == 0.0) && abs(yMag) < 250.0) {
    yMagOffsetMax = yMag;
  }
}

bool checkCompletedCalibration() {
  double xDiff = abs(xMag - xMagOffsetMin);
  double yDiff = abs(yMag - yMagOffsetMin);
  return ((xDiff < error) && (yDiff < error));
}

void getAngleDirection() {
  /* Get a new sensor event */ 
  sensors_event_t event; 
  magnetometer.getEvent(&event);
  
  float Pi = 3.14159;
  float declinationAngle = 282.5/1000;
  
  // Calculate the angle of the vector y,x
  float heading = atan2((event.magnetic.y+yMagOffset), (event.magnetic.x-xMagOffset));
  //heading += declinationAngle;
  
  // Normalize to 0-360
  if (heading < 0) {
    heading += 2*Pi;
  }
  float headingDegrees = heading * 180 / Pi;
  
  // Normalize to 0-360

  Serial.print("Compass Heading Degrees: ");
  Serial.println(headingDegrees);
  delay(500);
}

bool hasPassedYMin() {
  return abs(yMag - yMagOffsetMin) < error;
}

bool hasPassedXMin() {
  return abs(xMag - xMagOffsetMin) < error;
}

// Spins the robot to calibrate the max/min magnetic readings for location, and stop the robot at min mag x & y values
void calibrateMagneticReadings() {
  bool hasSeenMinY = false;
  bool hasSeenMinX = false;
  bool hasFinishedCalibration = false;
   
  while(!hasFinishedCalibration) {
    moveCCW();
    delay(250);
    stay();
    delay(250);

    gatherMagnetometerReadings();
    // If ran for the first time since bootup, set the offsets to initial readings, and start from there
    bool ifOffsetsNotCalibrated = xMagOffsetMin == 0.0 && yMagOffsetMin == 0.0 && xMagOffsetMax == 0.0 && yMagOffsetMax == 0.0;
    if(ifOffsetsNotCalibrated) {
      if(abs(xMag) < 1000.0) {
        xMagOffsetMin = xMag;
        xMagOffsetMax = xMag;
      }
      if(abs(yMag) < 250.0) {
        yMagOffsetMin = yMag;
        yMagOffsetMax = yMag;
      }
    }
    
    printMagneticValues();

    hasFinishedCalibration = checkCompletedCalibration() && !ifOffsetsNotCalibrated;
    updateMagnetometerOffsets();
  }
  stay();
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
