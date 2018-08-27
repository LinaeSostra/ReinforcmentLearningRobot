#include "Robot.h"

const unsigned int TIME_DELAY = 200;
State currentState = {START_LOCATION, North};
State previousState = {START_LOCATION, North};

// Resets position (in simulation ONLY!)
void resetPosition() {
  currentState.position = START_LOCATION;
  currentState.angle = North;
  previousState = currentState;
}

Position getRandomPosition() {
  assert(MIN_POSITION <= 0 && MAX_POSITION > 0);
  int range = abs(MIN_POSITION) + abs(MAX_POSITION);
  Position randomPosition = {(rand() % (range + 1)) + MIN_POSITION, (rand() % (range + 1)) + MIN_POSITION};
  return randomPosition;
}

// Resets to random position pointing North (in simulation ONLY!)
void resetToRandomPosition() {
  currentState.position = getRandomPosition();
  currentState.angle = (rand() % 4) * North;
  previousState = currentState;
}

void logState() {
  cout << "(X Position, Y Position): (" << currentState.position.x << ", " << currentState.position.y << "), " << "Angle: " << currentState.angle << "\n";
}

bool isOutOfBounds(const State &state) {
  int xPosition = state.position.x;
  int yPosition = state.position.y;
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
      tempState.position += pos;
    break;
    }
    case Backwards: {
      Position pos = calculateMovement(tempState.angle, false);
      tempState.position += pos;
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
  previousState = currentState;

  // If the  new state is not out of boundaries, update currentState with new state.
  State tempState = getStep(previousState, action);
  if(!isOutOfBounds(tempState)) {
    currentState = tempState;
  }

  //TODO(Rebecca): UNDO THIS LATER!!
  //usleep(TIME_DELAY); 
}