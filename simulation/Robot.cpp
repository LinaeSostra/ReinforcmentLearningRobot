#include "Robot.h"

const unsigned int TIME_DELAY = 200;
State currentState = {START_POSITION, START_POSITION, North};
State previousState = {START_POSITION, START_POSITION, North};

// Resets position (in simulation ONLY!)
void resetPosition() {
  currentState.xPosition = START_POSITION;
  currentState.yPosition = START_POSITION;
  currentState.angle = North;
  previousState = currentState;
}

int getRandomPosition(int minPosition, int maxPosition) {
  assert(minPosition <= 0 && maxPosition > 0);
  int range = abs(minPosition) + abs(maxPosition);
  return (rand() % range) + 1 + minPosition;
}

// Resets to random position pointing North (in simulation ONLY!)
void resetToRandomPosition() {
  currentState.xPosition = getRandomPosition(MIN_POSITION, MAX_POSITION);
  currentState.yPosition = getRandomPosition(MIN_POSITION, MAX_POSITION);
  currentState.angle = North;
  previousState = currentState;
}

void logState() {
  cout << "(X Position, Y Position): (" << currentState.xPosition << ", " << currentState.yPosition << ")" << "Angle: " << currentState.angle << "\n";
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
  previousState = currentState;
  switch(action) {
    case Stay:
      // Do nothing
    break;
    case Forward: {
      Position pos = calculateMovement(currentState.angle, true);
      currentState.xPosition += pos.x;
      currentState.yPosition += pos.y;
    break;
    }
    case Backwards: {
      Position pos = calculateMovement(currentState.angle, false);
      currentState.xPosition += pos.x;
      currentState.yPosition += pos.y;
    break;
    }
    case Right:
      currentState.angle = calculateAngle(currentState.angle, true);
    break;
    case Left:
      currentState.angle = calculateAngle(currentState.angle, false);
    break;
  }
  //TODO(Rebecca): UNDO THIS LATER!!
  //usleep(TIME_DELAY); 
}