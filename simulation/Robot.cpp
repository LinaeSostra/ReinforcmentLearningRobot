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
  return (rand() % (range + 1)) + minPosition;
}

// Resets to random position pointing North (in simulation ONLY!)
void resetToRandomPosition() {
  currentState.xPosition = getRandomPosition(MIN_POSITION, MAX_POSITION);
  currentState.yPosition = getRandomPosition(MIN_POSITION, MAX_POSITION);
  currentState.angle = (rand() % 4) * North;
  previousState = currentState;
}

void logState() {
  cout << "(X Position, Y Position): (" << currentState.xPosition << ", " << currentState.yPosition << "), " << "Angle: " << currentState.angle << "\n";
}

bool isOutOfBounds(const State &state) {
  int xPosition = state.xPosition;
  int yPosition = state.yPosition;
  bool xPositionOutOfBounds = xPosition < MIN_POSITION || xPosition > MAX_POSITION;
  bool yPositionOutOfBounds = yPosition < MIN_POSITION || yPosition > MAX_POSITION;
  bool outOfBounds = xPositionOutOfBounds || yPositionOutOfBounds;
  return outOfBounds;
}

State getCurrentState() {
  return currentState;
}

Position calculateMovement(Angle angle, bool isMovingForward) {
  Position pos = {0, 0};
  switch(angle) {
    case North:
      pos.y = isMovingForward ? -1: 1;
    break;
    case West:
      pos.x = isMovingForward ? -1: 1;
    break;
    case South:
      pos.y = isMovingForward ? 1: -1;
    break;
    case East:
      pos.x = isMovingForward ? 1: -1;
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

// Returns the state if action was applied to state given
State getStep(const State &state, Action action) {
  State tempState = state;
  switch(action) {
    case Forward: {
      Position pos = calculateMovement(tempState.angle, true);
      tempState.xPosition += pos.x;
      tempState.yPosition += pos.y;
    break;
    }
    case Backwards: {
      Position pos = calculateMovement(tempState.angle, false);
      tempState.xPosition += pos.x;
      tempState.yPosition += pos.y;
    break;
    }
    case Right:
      tempState.angle = calculateAngle(tempState.angle, true);
    break;
    case Left:
      tempState.angle = calculateAngle(tempState.angle, false);
    break;
  }
  
  return tempState;
}

// Adjust the robot's state
// TODO(Rebecca): States will need to be revisited. 
// Assuming angles are 90 degree only changes
void apply(Action action) {
  int x, y;
  previousState = currentState;

  // If the  new state is not out of boundaries, update currentState with new state.
  State tempState = getStep(previousState, action);
  if(!isOutOfBounds(tempState)) {
    currentState = tempState;
  }

  //TODO(Rebecca): UNDO THIS LATER!!
  //usleep(TIME_DELAY); 
}