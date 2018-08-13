#include <Arduino.h>
#include "Motors.h"
#include "Pins.h"

/* Motion */

uint8_t motorSpeedA = 0; // 0-255, value for PWM speed control
uint8_t motorSpeedB = 255; // 0-255, value for PWM speed control

void motorSetup() {
  pinMode(pinMotorA1, OUTPUT);
  pinMode(pinMotorA2, OUTPUT);
  pinMode(pinMotorB1, OUTPUT);
  pinMode(pinMotorB2, OUTPUT);
  pinMode(pinSpeedMotorA, OUTPUT);
  pinMode(pinSpeedMotorB, OUTPUT);
}

// Returns the speed of the left motor
uint8_t getLeftMotorSpeed() {
  return motorSpeedB; // get PWM speed
}

// Returns the speed of the right motor
uint8_t getRightMotorSpeed() {
  return motorSpeedA; // get PWM speed
}

void testMotors() {
  moveCW(); // Rotate in Clockwise
  delay(5000); // Wait 5 seconds
  moveCCW(); // Rotate in Counter-Clockwise
  delay(5000); // Wait 5 seconds
  moveForward(); // Move forward
  delay(5000); // Wait 5 seconds
  moveBackward(); // Move backward
  delay(5000); // Wait 5 seconds
}

void stay() { 
  digitalWrite(pinMotorA1, LOW);
  digitalWrite(pinMotorA2, LOW);
  digitalWrite(pinMotorB1, LOW);
  digitalWrite(pinMotorB2, LOW);
}

void moveCW() {
  digitalWrite(pinMotorA1, LOW);
  digitalWrite(pinMotorA2, HIGH);
  digitalWrite(pinMotorB1, LOW);
  digitalWrite(pinMotorB2, HIGH);
}

void moveCCW() {
  digitalWrite(pinMotorA1, HIGH);
  digitalWrite(pinMotorA2, LOW);
  digitalWrite(pinMotorB1, HIGH);
  digitalWrite(pinMotorB2, LOW);
}

void moveForward() {
  digitalWrite(pinMotorA1, HIGH);
  digitalWrite(pinMotorA2, LOW);
  digitalWrite(pinMotorB1, LOW);
  digitalWrite(pinMotorB2, HIGH);
}

void moveBackward() {
  digitalWrite(pinMotorA1, LOW);
  digitalWrite(pinMotorA2, HIGH);
  digitalWrite(pinMotorB1, HIGH);
  digitalWrite(pinMotorB2, LOW);
}

// Set motor L speed
void setLeftMotorSpeed() {
  analogWrite(pinSpeedMotorB, motorSpeedB);
}
// Set motor R speed
void setRightMotorSpeed() {
  analogWrite(pinSpeedMotorA, motorSpeedA);
}
