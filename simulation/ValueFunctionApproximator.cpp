#include "ValueFunctionApproximator.h"

double weights[NUM_FEATURES] = {0};

void squareBinBinaryAugment(const State &state, const int sideLength, double vector[], unsigned int length) {
  double xPosition = (double) state.position.x;
  double yPosition = (double) state.position.y;
  unsigned int binIndex = (int) (sideLength * yPosition + xPosition);
  bool doesIndexMatch = false;

  switch (state.angle) {
  case West:
    binIndex += sideLength * sideLength;
    break;
  case East:
    binIndex += 2 * sideLength * sideLength;
    break;
  case South:
    binIndex += 3 * sideLength * sideLength;
    break;
  }
  
  for(unsigned int i = 0; i < length; i++) {
    doesIndexMatch = i == binIndex;
    vector[i] = (doesIndexMatch) ? 1.0 : 0.0;
  }
}

void extractFeatures(const State &state, const Action action, double phi[]) {
  /*// 1 - Counterclockwise
  //-1 - Clockwise
  int leftMotorDirection = 0;
  int rightMotorDirection = 0;
  int angleDirection = 0;

  switch (action) {
    case Stay:
      break;
    case Forward:
      leftMotorDirection = -1;
      rightMotorDirection = -1;
      break;
    case Backwards:
      leftMotorDirection = 1;
      rightMotorDirection = 1;
      break;
    case Right:
      leftMotorDirection = -1;
      rightMotorDirection = 1;
      angleDirection = -1;
      break;
    case Left:
      leftMotorDirection = 1;
      rightMotorDirection = -1;
      angleDirection = 1;
      break;
  }
  */
  State newState = getStep(state, action);
  squareBinBinaryAugment(newState, 5, phi, NUM_FEATURES);
  //phi[100] = double(leftMotorDirection);
  //phi[101] = double(rightMotorDirection);
  //phi[100] = double(angleDirection && (state.angle == North));
  //phi[101] = double(angleDirection && (state.angle == West));
  //phi[102] = double(angleDirection && (state.angle == South));
  //phi[103] = double(angleDirection && (state.angle == East));
}

double value(const State &state, const Action action) {
  double phi[NUM_FEATURES];
  extractFeatures(state, action, phi);
  //TODO(Rebeca): This is a cough out; fix this.
  double value = 0.0;
  bool isPhiEmpty = true;
  for(unsigned int i = 0; i < NUM_FEATURES; i++) {
    if(phi[i] != 0.0) {
      isPhiEmpty = false;
    }
    value += weights[i] * phi[i];
  }
  return isPhiEmpty ? -100 : value;
}

// Note: may need to add bins back if make state space larger
void squareBin(const State &state, const unsigned int sideLength, double vector[], unsigned int length) {
  double xPosition = (double) state.position.x;
  double yPosition = (double) state.position.y;
  unsigned int binIndex = (int) (sideLength * yPosition + xPosition);

  bool doesIndexMatch = false;
  for (int i = 0; i < length; i++) {
    doesIndexMatch = i == binIndex;
    vector[i] = (doesIndexMatch) ? 1.0: 0.0;
  }
}