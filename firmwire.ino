/* *************************************************************
   This script will act as the vacuum robot's firmware
   to rotate and/or move forward/backward.
   -------------------------------------------------------------
   To-Do List
   ★ Make sense of compass module readings
   ★ Wireless communication
   ★ H-bridge PWM speed control (need level converters or add-on circuits)
   ★ Testings
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
#include "src/Adafruit_Sensor.h"
#include "src/Adafruit_LSM303_U.h"

////////////////////////////////
/* Debug Mode */
////////////////////////////////
#define DEBUG // comment this line to disable debug (Serial Prints)

////////////////////////////////
/* Pins */
////////////////////////////////
// 16 D0  - Non-interruptable
const int pinBatteryRead = A0;      // A0
const int pinMotorA1 = 0;           // D3
const int pinMotorA2 = 2;           // D4
const int pinMotorB1 = 14;          // D5
const int pinMotorB2 = 12;          // D6
const int pinPushSensor = 13;           // D7
// 15 D8
const int pinSpeedMotorA = 1;       // Tx
const int pinSpeedMotorB = 3;       // Rx
// Note: There is something weird about this output 9 on this particular microcontroller.
// 9 SD2
const int pinLED = 10; // SD3


////////////////////////////////
/* Global Constants */
////////////////////////////////

////////////////////////////////
/* Global Variables */
////////////////////////////////
uint8_t leftMotorSpeed;
uint8_t rightMotorSpeed;
int compassDirection; // 0 - 359 degrees
bool isSensorPushed;

uint8_t motorSpeedA = 0; // 0-255, value for PWM speed control
uint8_t motorSpeedB = 255; // 0-255, value for PWM speed control

// Initialize Compass
// Assigning a unique ID (12345) to the compass
Adafruit_LSM303_Accel_Unified accelometer = Adafruit_LSM303_Accel_Unified(54321);

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
  pinMode(pinPushSensor, INPUT_PULLUP);

  // Attach Interrupts
  attachInterrupt(digitalPinToInterrupt(pinPushSensor), latchTriggered, CHANGE);

  // Initialize the sensor
  if(!accelometer.begin()) {
    // There was a problem detecting the ADXL345 ... check your connections
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }

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
  
  gatherAccelometerValues();
}

////////////////////////////////
/* Functions */
////////////////////////////////

/* Setters */

// Interrupt Fcn: When the push sensor changes state, update isSensorPushed boolean
void latchTriggered() {
#ifdef DEBUG
  Serial.print("Is Sensor Pushed: "); Serial.println(getSensorPushed());
#endif
  isSensorPushed = !isSensorPushed;
}

// Updates the direction of the robot
void updateDirection() {
  compassDirection = -1;
}
