/* Getters */

// Returns the speed of the left motor
uint8_t getLeftMotorSpeed() {
  leftMotorSpeed = motorSpeedB; // get PWM speed
  return leftMotorSpeed;
}

// Returns the speed of the right motor
uint8_t getRightMotorSpeed() {
  rightMotorSpeed = motorSpeedA; // get PWM speed
  return rightMotorSpeed;
}

// Returns whether the latch cas been triggered
boolean getSensorPushed() {
  return isSensorPushed;
}

// Gets the direction of the robot
int getDirection() {
  return compassDirection;
}

