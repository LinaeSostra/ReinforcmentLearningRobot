#include <Arduino.h>
#include "Robot.h"
//#include "Motors.h"
//#include "Pins.h"

const int TIME_DELAY = 200;
State currentState = {START_POSITION, START_POSITION, North};

// Resets position (in simulation ONLY!)
void resetPosition() {
  currentState.xPosition = START_POSITION;
  currentState.yPosition = START_POSITION;
  currentState.angle = North;
}

// Resets to random position pointing North (in simulation ONLY!)
void resetToRandomPosition() {
  currentState.xPosition = random(MIN_POSITION, MAX_POSITION);
  currentState.yPosition = random(MIN_POSITION, MAX_POSITION);
  currentState.angle = North;
}

void logState() {
  Serial.print("(X Position, Y Position): (");
  Serial.print(currentState.xPosition);
  Serial.print(", ");
  Serial.print(currentState.yPosition);
  Serial.println(")");
  
  Serial.print("Angle: ");
  Serial.println(currentState.angle);
}
struct Position {
  int x;
  int y;
};

State getCurrentState() {
  return currentState;
}

Position calculateMovement(Angle angle, bool isMovingForward) {
  Position pos = {0, 0};
  switch(angle) {
    case North:
      pos.x = isMovingForward ? 1: -1;
    break;
    case West:
      pos.y = isMovingForward ? 1: -1;
    break;
    case South:
      pos.x = isMovingForward ? -1: 1;
    break;
    case East:
      pos.y = isMovingForward ? -1: 1;
    break;
  }
  return pos;
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

// Adjust the robot's state
// TODO(Rebecca): States will need to be revisited. 
// Assuming angles are 90 degree only changes
void apply(Action action) {
  int x, y;
  switch(action) {
    case Stay:
      stay();
    break;
    case Forward: {
      moveForward();
      Position pos = calculateMovement(currentState.angle, true);
      currentState.xPosition += pos.x;
      currentState.yPosition += pos.y;
    break;
    }
    case Backwards: {
      moveBackward();
      Position pos = calculateMovement(currentState.angle, false);
      currentState.xPosition += pos.x;
      currentState.yPosition += pos.y;
    break;
    }
    case Right:
      moveCW();
      currentState.angle = calculateAngle(currentState.angle, true);
    break;
    case Left:
      moveCCW();
      currentState.angle = calculateAngle(currentState.angle, false);
    break;
  }
  delay(TIME_DELAY); 
}