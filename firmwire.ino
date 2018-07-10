/* *************************************************************
   This script will act as the vacuum robot's firmware
   to rotate and/or move forward/backward.
   -------------------------------------------------------------
   To-Do List
   ★ Make sense of compass module readings
   ★ Wireless communication
   ★ H-bridge PWM speed control (need level converters or add-on circuits)
   ★ Testings
   ★ Robot.cpp
   ★ Convert Compass && Sensor to C++
   -------------------------------------------------------------
   Done List
   ★ Push sensor
   ★ H-bridge & motors direction control
   ★ Battery level reading is working! (error ~0.1v)
   ★ Update the pin numbers after MCU is finalized
************************************************************* */
////////////////////////////////
/* Libraries */
////////////////////////////////
#include "Compass.h"
#include "Pins.h"
#include "Learning.h"
#include "Motors.h"
#include "PushButton.h"

////////////////////////////////
/* Debug Mode */
////////////////////////////////
#define DEBUG // comment this line to disable debug (Serial Prints)

////////////////////////////////
/* Global Variables */
////////////////////////////////
uint8_t leftMotorSpeed;
uint8_t rightMotorSpeed;

int compassDirection; // 0 - 359 degrees

// Initialize Compass
// Assigning a unique ID (12345) to the compass
//Adafruit_LSM303_Accel_Unified accelometer = Adafruit_LSM303_Accel_Unified(54321);
//Adafruit_LSM303_Mag_Unified mag = Adafruit_LSM303_Mag_Unified(12345);

void setup() {
  // Set input pins
  pinMode(pinBatteryRead, INPUT);

  // Set output pins
  pinMode(pinLED, OUTPUT);
  pinMode(pinMotorA1, OUTPUT);
  pinMode(pinMotorA2, OUTPUT);
  pinMode(pinMotorB1, OUTPUT);
  pinMode(pinMotorB2, OUTPUT);
  pinMode(pinSpeedMotorA, OUTPUT);
  pinMode(pinSpeedMotorB, OUTPUT);
  setupLatch();

  compassSetup();

  // Get initial readings
  checkBattery();
    
#ifdef DEBUG
// Debug
  Serial.begin(115200);
  Serial.println("SETUP");
#endif

  // Set speed
  //setLeftMotorSpeed();
  //setRightMotorSpeed();
  // Before we can use PWM speed control:
  digitalWrite(pinSpeedMotorA, HIGH);
  digitalWrite(pinSpeedMotorB, HIGH);

  // Set LED off
  digitalWrite(pinLED, LOW);
}

void loop() {
  checkBattery();
  // Basic running test
  //testMotors();
  
  //gatherAccelometerValues();
  gatherMagnetometerValues();
}

////////////////////////////////
/* Functions */
////////////////////////////////

/* Setters */

// Updates the direction of the robot
void updateDirection() {
  compassDirection = -1;
}

/* Getters */
// Gets the direction of the robot
int getDirection() {
  return compassDirection;
}
