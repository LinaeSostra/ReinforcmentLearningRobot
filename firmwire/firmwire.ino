/* *************************************************************
   This script will act as the vacuum robot's firmware
   to rotate and/or move forward/backward.
   -------------------------------------------------------------
   To-Do List
   ★ Make sense of compass module readings
   ★ Wireless communication
   ★ H-bridge PWM speed control (need level converters or add-on circuits)
   ★ Testings
   ★ UI
   -------------------------------------------------------------
   Done List
   ★ Push sensor
   ★ H-bridge & motors direction control
   ★ Battery level reading is working! (error ~0.1v)
   ★ Update the pin numbers after MCU is finalized
   ★ Robot.cpp
   ★ Convert Compass && Sensor to C++
************************************************************* */

////////////////////////////////
/* Libraries */
////////////////////////////////
#include "Pins.h"
#include "Compass.h"
#include "Battery.h"
#include "Motors.h"
#include "PushButton.h"
#include "C:\Users\rebec\Documents\firmwire\Learning.h"

////////////////////////////////
/* Debug Mode */
////////////////////////////////
#define DEBUG // comment this line to disable debug (Serial Prints)

////////////////////////////////
/* Global Variables */
////////////////////////////////
uint8_t leftMotorSpeed;
uint8_t rightMotorSpeed;

void setup() {
  // Set input pins
  batterySetup();

  // Set output pins
  motorSetup();
  latchSetup();
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

  calibrateMagneticReadings(); 
}

void loop() {
  checkBattery();
  // Basic running test
  //testMotors();
  
  //gatherAccelometerReadings();
  //gatherMagnetometerReadings();
  //testMagneticValues();
  //getAngleDirection();
}
