#include <Arduino.h>
#include "Learning.h"
#include "Pins.h"

const int timeDelay = 200;
State currentState = {0, 0, North};

void logState() {
  Serial.print("(X Position, Y Position): (");
  Serial.print(currentState.xPosition);
  Serial.print(", ");
  Serial.print(currentState.yPosition);
  Serial.println(")");
  
  Serial.print("Angle: ");
  Serial.println(currentState.angle);
}

// Adjust the robot's state
// TODO(Rebecca): States will need to be revisited. 
// Assuming angles are 90 degree only changes
void apply(Action action) {
  int x, y;
  switch (action) {
    case Stay:
      stay();
    break;
    case Forward:
      moveForward();
      (x, y) = calculateMovement(currentState.angle, true);
      currentState.xPosition += x;
      currentState.yPosition += y;
    break;
    case Backward:
      moveBackward();
      (x, y) = calculateMovement(currentState.angle, false);
      currentState.xPosition += x;
      currentState.yPosition += y;
    break;
    case Right:
      moveCW();
      currentState.angle = calculateAngle(currentState,angle, true);
    break;
    case Left:
      moveCCW();
      currentState.angle = calculateAngle(currentState.angle, false);
    break;
  }
  delay(timeDelay); 
}

(int, int) calculateMovement(Angle angle, bool isMovingForward) {
  int x, y = 0;
  switch(angle) {
    case North:
      x = isMovingForward ? 1: -1;
    break;
    case West:
      y = isMovingForward ? 1: -1;
    break;
    case South:
      x = isMovingForward ? -1: 1;
    break;
    case East:
      y = isMovingForward ? -1: 1;
    break;
  }
  return (x, y);
}

Angle calculateAngle(Angle angle, bool isRotatingClockwise) {
  switch(angle) {
    case North:
      return isRotatingClockwise ? East : West;
    break;
    case West:
      return isRotatingClockwise ? North : South;
    break;
    case South:
      return isRotatingClockwise ? West : East;
    break;
    case East:
      return isRotatingClockwise ? South : North;
    break;
  }
}
